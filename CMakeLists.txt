# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
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

# == DO NOT EDIT THE FOLLOWING LINES ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# =====================================

set(PICO_BOARD pico_w CACHE STRING "Board type")

include(pico_sdk_import.cmake)

project(leituradosbotoes C CXX ASM)  

pico_sdk_init()

# Alterado o nome do executável e arquivo principal
add_executable(leituradosbotoes main.c utils/wifi-connection/wifi-connect.c utils/send-data-to-server/send-data.c)

pico_set_program_name(leituradosbotoes "leituradosbotoes")  # Atualizado
pico_set_program_version(leituradosbotoes "0.1")

pico_enable_stdio_uart(leituradosbotoes 0)  # Atualizado
pico_enable_stdio_usb(leituradosbotoes 1)   # Atualizado

target_link_libraries(leituradosbotoes      
        pico_stdlib
        pico_cyw43_arch_lwip_threadsafe_background
        )

target_include_directories(leituradosbotoes PRIVATE  # Atualizado
        ${CMAKE_CURRENT_LIST_DIR}
        )

pico_add_extra_outputs(leituradosbotoes)  # Atualizado