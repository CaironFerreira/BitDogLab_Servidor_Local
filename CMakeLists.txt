# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 1.5.1)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 1.5.1)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 1.5.1)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 1.5.1)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(picoServidorLocal C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(picoServidorLocal picoServidorLocal.c )

pico_set_program_name(picoServidorLocal "picoServidorLocal")
pico_set_program_version(picoServidorLocal "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(picoServidorLocal 0)
pico_enable_stdio_usb(picoServidorLocal 1)

# Add the standard library to the build
target_link_libraries(picoServidorLocal
        pico_stdlib # Biblioteca padrão do Pico SDK
        hardware_gpio # Biblioteca para controle de GPIO (General Purpose Input/Output)
        hardware_adc # Biblioteca para controle de ADC (Analog-to-Digital Converter)
        pico_cyw43_arch_lwip_threadsafe_background # Biblioteca para suporte à arquitetura CYW43 com lwIP em modo de thread seguro
)

# Add the standard include files to the build
target_include_directories(picoServidorLocal PRIVATE
    ${CMAKE_CURRENT_LIST_DIR} # Diretório atual da lista de arquivos CMake
    ${PICO_SDK_PATH}/lib/lwip/src/include # Diretório de inclusão principal do lwIP
    ${PICO_SDK_PATH}/lib/lwip/src/include/arch # Diretório de inclusão para a arquitetura do lwIP
    ${PICO_SDK_PATH}/lib/lwip/src/include/lwip # Diretório de inclusão para os arquivos principais do lwIP
)

target_sources(picoServidorLocal PRIVATE
    ${PICO_SDK_PATH}/lib/lwip/src/apps/http/httpd.c # Arquivo de implementação do servidor HTTP do lwIP
    ${PICO_SDK_PATH}/lib/lwip/src/apps/http/fs.c # Arquivo de implementação do sistema de arquivos do lwIP
)


# Add any user requested libraries

pico_add_extra_outputs(picoServidorLocal)
