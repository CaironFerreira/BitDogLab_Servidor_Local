#ifndef LWIPOPTS_H
#define LWIPOPTS_H

// Configuração mínima para lwIP

#define NO_SYS 1 // Define se o sistema operacional é necessário. Se 1, lwIP opera em modo "sem sistema", sem suporte a threads.
#define LWIP_SOCKET 0 // Habilita ou desabilita o suporte a sockets. Se 1, o suporte a sockets é desativado.
#define LWIP_NETCONN 0 // Habilita ou desabilita o suporte a netconn. Se 1, o suporte a netconn é desativado.
#define LWIP_TCP 1 // Habilita o suporte ao protocolo TCP. Se 1, o TCP é habilitado.
#define LWIP_UDP 1 // Habilita o suporte ao protocolo UDP. Se 1, o UDP é habilitado.
#define MEM_ALIGNMENT 4 // Define o alinhamento de memória. O valor 4 significa que os dados devem ser alinhados em endereços múltiplos de 4 bytes.
#define MEM_SIZE 4096 // Define o tamanho total da memória disponível para lwIP. Aqui, é definido como 4096 bytes.
#define MEMP_NUM_PBUF 16 // Define o número máximo de buffers de protocolo (pbufs) que podem ser alocados.
#define PBUF_POOL_SIZE 16 // Define o tamanho do pool de buffers de pbuf. O número de pbufs que podem ser alocados simultaneamente.              
#define MEMP_NUM_UDP_PCB 4 // Define o número máximo de PCB (Protocol Control Blocks) UDP que podem ser alocados.
#define MEMP_NUM_TCP_PCB 4 // Define o número máximo de PCB TCP que podem ser alocados.
#define MEMP_NUM_TCP_SEG 16 // Define o número máximo de segmentos TCP que podem ser alocados.
#define LWIP_IPV4 1 // Habilita o suporte ao protocolo IPv4. Se 1, o IPv4 é habilitado.
#define LWIP_ICMP 1 // Habilita o suporte ao protocolo ICMP (Internet Control Message Protocol). Se 1, o ICMP é habilitado.
#define LWIP_RAW 1 // Habilita o suporte a pacotes RAW. Se 1, pacotes RAW são habilitados.
#define LWIP_DHCP 1 // Habilita o suporte a DHCP (Dynamic Host Configuration Protocol). Se 1, o DHCP é habilitado.
#define LWIP_AUTOIP 1 // Habilita o suporte a AutoIP, que permite a configuração automática de endereços IP. Se 1, o AutoIP é habilitado
#define LWIP_DNS 1 // Habilita o suporte a DNS (Domain Name System). Se 1, o DNS é habilitado.
#define LWIP_HTTPD 1 // Habilita o suporte ao servidor HTTP. Se 1, o servidor HTTP é habilitado.
#define LWIP_HTTPD_SSI              1  // Habilita o suporte a Server-Side Includes (SSI) no servidor HTTP. Se 1, o SSI é habilitado.
#define LWIP_HTTPD_SUPPORT_POST     1  // Habilita o suporte a requisições POST no servidor HTTP. Se 1, o suporte a POST é habilitado.
#define LWIP_HTTPD_DYNAMIC_HEADERS 1   // Habilita o uso de cabeçalhos dinâmicos no servidor HTTP. Se 1, cabeçalhos dinâmicos são habilitados.
#define HTTPD_USE_CUSTOM_FSDATA 0 // Define se o sistema de arquivos personalizado deve ser usado. Se 1, um sistema de arquivos personalizado é usado.
#define LWIP_HTTPD_CGI 0          // Habilita o suporte a CGI (Common Gateway Interface) no servidor HTTP. Se 1, o suporte a CGI é habilitado.
#define LWIP_NETIF_HOSTNAME 1     // Habilita o suporte a nomes de host para interfaces de rede. Se 1, o suporte a nomes de host é habilitado.


#endif /* LWIPOPTS_H */
