#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "utils/send-data-to-server/send-data.h"
#include "utils/wifi-connection/wifi-connect.h"

extern bool wifi_conectado;

float ler_temperatura_celsius() {
    adc_select_input(4);
    uint16_t raw = adc_read();
    const float conversao = 3.3f / (1 << 12);
    float voltagem = raw * conversao;
    return 27.0f - (voltagem - 0.706f) / 0.001721f;
}

int main() {
    stdio_init_all();
    sleep_ms(3000);

    printf("Iniciando sistema...\n");
    init_wifi();

    // Aguarda conexão Wi-Fi
    while (!wifi_conectado) {
        printf("Aguardando conexão Wi-Fi...\n");
        sleep_ms(1000);
    }

    printf("Wi-Fi conectado! Iniciando leitura...\n");

    // Configuração dos botões
    const uint BUTTON_A = 5;
    const uint BUTTON_B = 6;
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);
    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);

    // Configuração ADC
    adc_init();
    adc_set_temp_sensor_enabled(true);

    int total = 0;
    absolute_time_t ultimo_envio = get_absolute_time();

    while (true) {
        bool btnA = !gpio_get(BUTTON_A);
        bool btnB = !gpio_get(BUTTON_B);
        float temp = ler_temperatura_celsius();

        const char* status;

        if (btnA && !btnB) {
            total++;
            status = "Alguem entrou";
        } else if (btnB && !btnA) {
            if (total > 0) total--;
            status = "Alguem saiu";
        } else {
            status = "Ninguem entrou ou saiu";
        }

        // Enviar sempre que algum botão for pressionado OU a cada 1 segundo
        if (btnA || btnB || absolute_time_diff_us(ultimo_envio, get_absolute_time()) > 1000000) {
            create_request(status, total, temp);
            ultimo_envio = get_absolute_time();
        }

        sleep_ms(100);
    }

    return 0;
}
