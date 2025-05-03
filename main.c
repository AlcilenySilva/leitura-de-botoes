#include <stdio.h>
#include "pico/stdlib.h"
#include "utils/send-data-to-server/send-data.h"
#include "utils/wifi-connection/wifi-connect.h"

extern bool wifi_conectado;  // Acesso ao status do Wi-Fi

int main() {
    stdio_init_all();
    sleep_ms(3000);  // Aguarda a inicialização da serial

    printf("Iniciando sistema...\n");

    // Inicializa Wi-Fi
    init_wifi();

    // Aguarda conexão Wi-Fi
    while (!wifi_conectado) {
        printf("Aguardando conexão Wi-Fi...\n");
        sleep_ms(1000);
    }

    printf("Wi-Fi conectado! Iniciando leitura dos botões...\n");

    const uint BUTTON_PIN_A = 5;
    const uint BUTTON_PIN_B = 6;

    gpio_init(BUTTON_PIN_A);
    gpio_set_dir(BUTTON_PIN_A, GPIO_IN);
    gpio_pull_up(BUTTON_PIN_A); // Usa resistor de pull-up interno

    gpio_init(BUTTON_PIN_B);
    gpio_set_dir(BUTTON_PIN_B, GPIO_IN);
    gpio_pull_up(BUTTON_PIN_B); // Usa resistor de pull-up interno

    while (true) {
        // Mostra o estado atual dos botões (debug)
        printf("A: %d | B: %d\n", gpio_get(BUTTON_PIN_A), gpio_get(BUTTON_PIN_B));

        if (!gpio_get(BUTTON_PIN_A)) {
            printf("Botão A pressionado\n");
            create_request("botaoA");
            sleep_ms(500); // Debounce simples
        }

        if (!gpio_get(BUTTON_PIN_B)) {
            printf("Botão B pressionado\n");
            create_request("botaoB");
            sleep_ms(500); // Debounce simples
        }

        sleep_ms(100);
    }

    return 0;
}
