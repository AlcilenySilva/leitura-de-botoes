#include "wifi-connect.h"
#include <stdbool.h>

bool wifi_conectado = false;

void init_wifi() {
    if (cyw43_arch_init()) {
        printf("Erro ao inicializar Wi-Fi\n");
        return;
    }

    cyw43_arch_enable_sta_mode();

    while (1) {
        printf("Conectando a %s...\n", WIFI_SSID);
        int result = cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 10000);
        
        if (result == 0) {
            printf("Conectado!\n");
            wifi_conectado = true;  
            break;
        }
        
        printf("Falha. Código: %d. Tentando novamente...\n", result);
        sleep_ms(3000);
    }

    printf("Wi-Fi conectado com sucesso!\n");
}
