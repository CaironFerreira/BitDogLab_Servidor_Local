#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "pico/cyw43_arch.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lwip/pbuf.h"
#include "lwip/tcp.h"
#include "lwip/netif.h"

#define WIFI_SSID "Maria Goreti" // Define o SSID (nome) do wifi
#define WIFI_PASSWORD "paft1500" // Define a senha da rede.

#define LED_PIN CYW43_WL_GPIO_LED_PIN
#define BUTTON_A 5

#define JOYSTICK_X_PIN 0
#define JOYSTICK_Y_PIN 1

#define ADC_MAX ((1 << 12) - 1)

static char last_direction[16] = "Norte"; 
const char* get_direction(uint adc_x_raw, uint adc_y_raw) { 
    
    if (adc_y_raw < ADC_MAX / 4 && adc_x_raw < ADC_MAX / 4) {
        return "Sudoeste"; 
    } else if (adc_y_raw < ADC_MAX / 4 && adc_x_raw > 3 * ADC_MAX / 4) {
        return "Noroeste"; 
    } else if (adc_y_raw > 3 * ADC_MAX / 4 && adc_x_raw < ADC_MAX / 4) {
        return "Sudeste"; 
    } else if (adc_y_raw > 3 * ADC_MAX / 4 && adc_x_raw > 3 * ADC_MAX / 4) {
        return "Nordeste"; 
    } else if (adc_y_raw < ADC_MAX / 3) {
        return "Oeste";
    } else if (adc_y_raw > 2 * ADC_MAX / 3) {
        return "Leste";
    } else if (adc_x_raw < ADC_MAX / 3) {
        return "Sul";
    } else if (adc_x_raw > 2 * ADC_MAX / 3) {
        return "Norte";
    } else {
        return "Centro";
    }
}

static char button_status[16] = "Solto";

void check_button_status() {
    if (!gpio_get(BUTTON_A)) { 
        strncpy(button_status, "Pressionado", sizeof(button_status) - 1);
    } else {
        strncpy(button_status, "Solto", sizeof(button_status) - 1);
    }
    button_status[sizeof(button_status) - 1] = '\0';
}

static err_t tcp_server_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
    if (!p)
    {
        tcp_close(tpcb);
        tcp_recv(tpcb, NULL);
        return ERR_OK;
    }

    char *request = (char *)malloc(p->len + 1);
    memcpy(request, p->payload, p->len);
    request[p->len] = '\0';

    adc_select_input(4);
    uint16_t raw_value = adc_read();
    const float conversion_factor = 3.3f / (1 << 12); 
    float temperature = 27.0f - ((raw_value * conversion_factor) - 0.706f) / 0.001721f;
    adc_select_input(JOYSTICK_X_PIN);
    uint adc_x_raw = adc_read();
    adc_select_input(JOYSTICK_Y_PIN);
    uint adc_y_raw = adc_read();
    const char* direction = get_direction(adc_x_raw, adc_y_raw);
    strncpy(last_direction, direction, sizeof(last_direction) - 1);
    last_direction[sizeof(last_direction) - 1] = '\0';

    check_button_status(); 
    char html[1024];

    snprintf(html, sizeof(html),
            "HTTP/1.1 200 OK\r\n" 
            "Content-Type: text/html\r\n" 
            "\r\n" 
            "<!DOCTYPE html>\n"
            "<html lang=\"pt\">\n"
            "<head>\n"
            "    <meta charset=\"UTF-8\">\n"
            "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
            "    <title>Monitoramento Inteligente</title>\n"
            "    <style>\n"
            "        * { margin: 0; padding: 0; box-sizing: border-box; font-family: 'Arial', sans-serif; }\n"
            "        body { display: flex; flex-direction: column; align-items: center; justify-content: center; min-height: 100vh; background: linear-gradient(to right, #232526, #414345); color: #fff; text-align: center; padding: 20px; }\n"
            "        header { width: 100%; padding: 15px; background: rgba(255, 255, 255, 0.1); box-shadow: 0 2px 5px rgba(0, 0, 0, 0.2); }\n"
            "        h1 { font-size: 36px; font-weight: bold; }\n"
            "        .container { width: 80%; max-width: 500px; background: rgba(255, 255, 255, 0.2); padding: 20px; border-radius: 10px; box-shadow: 0 4px 10px rgba(0, 0, 0, 0.3); margin-top: 20px; }\n"
            "        .temperature, .status { font-size: 22px; margin: 15px 0; font-weight: bold; }\n"
            "        footer { margin-top: 20px; font-size: 16px; opacity: 0.8; }\n"
            "    </style>\n"
            "</head>\n"
            "<body>\n"
            "    <header>\n"
            "        <h1>Monitoramento Inteligente</h1>\n"
            "    </header>\n"
            "    <div class=\"container\">\n"
            "        <p class=\"temperature\">Temperatura Interna: %.2f &deg;C</p>\n"
            "        <p class=\"status\">Estado do Botão: %s</p>\n"
            "        <p class=\"status\">Direção do Joystick: %s</p>\n"
            "    </div>\n"
            "    <footer>\n"
            "        <p>Atualizando automaticamente...</p>\n"
            "    </footer>\n"
            "    <script>\n"
            "        setTimeout(function() {\n"
            "            window.location = window.location.pathname;\n"
            "        }, 1000);\n"
            "    </script>\n"
            "</body>\n"
            "</html>\n",
            temperature, button_status, last_direction);


    tcp_write(tpcb, html, strlen(html), TCP_WRITE_FLAG_COPY);
    tcp_output(tpcb);

    free(request);
    pbuf_free(p);

    return ERR_OK;
}

static err_t tcp_server_accept(void *arg, struct tcp_pcb *newpcb, err_t err)
{
    tcp_recv(newpcb, tcp_server_recv);
    return ERR_OK;
}

int main()
{
    stdio_init_all();

    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    while (cyw43_arch_init())
    {
        printf("Falha ao inicializar Wi-Fi\n"); 
        sleep_ms(100);
        return -1; 
    }

    cyw43_arch_gpio_put(LED_PIN, 0);
    cyw43_arch_enable_sta_mode();

    printf("Conectando ao Wi-Fi...\n");
    while (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 20000))
    {
        printf("Falha ao conectar ao Wi-Fi\n");
        sleep_ms(100);
        return -1;
    }
    printf("Conectado ao Wi-Fi\n");

    if (netif_default)
    {
        printf("IP do dispositivo: %s\n", ipaddr_ntoa(&netif_default->ip_addr));
    }

    struct tcp_pcb *server = tcp_new();
    if (!server) 
    {
        printf("Falha ao criar servidor TCP\n");
        return -1;
    }

    if (tcp_bind(server, IP_ADDR_ANY, 80) != ERR_OK)
    {
        printf("Falha ao associar servidor TCP à porta 80\n"); 
        return -1;
    }

    server = tcp_listen(server);
    tcp_accept(server, tcp_server_accept);

    printf("Servidor ouvindo na porta 80\n");

    adc_init();
    adc_set_temp_sensor_enabled(true);

    while (true)
    {
        cyw43_arch_poll();
    }

    cyw43_arch_deinit(); 
    return 0;
}