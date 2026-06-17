#include "leds.h"
#include "adc_reader.h"
#include "tasks.h"

#include "esp_log.h"

static const char *TAG = "MAIN";

void app_main(void) {
    ESP_LOGI(TAG, "=== Practica 2: ADC + PWM + FreeRTOS ===");

    leds_init();
    adc_reader_init();
    tasks_create_all();

    ESP_LOGI(TAG, "Sistema iniciado correctamente");
}