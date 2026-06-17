/**
 * @file leds.c
 * @brief Inicializacion y control PWM de los LEDs mediante LEDC.
 */
#include "tasks.h"
#include "adc_reader.h"
#include "leds.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_heap_caps.h"

#define TASK_PERIOD_MS       50
#define TASK_LOG_EVERY_N     20

static const char *TAG = "TASKS";

static TaskHandle_t h0 = NULL;
static TaskHandle_t h1 = NULL;
static TaskHandle_t h2 = NULL;

void vTaskPotLED(void *pvParameters) {
    /* pvParameters recibe la configuracion especifica de cada canal */
    const task_params_t *cfg = (const task_params_t *)pvParameters;
    uint32_t contador = 0;

    ESP_LOGI(TAG, "[%s] Tarea iniciada ADC ch%d -> LED ch%d",
             cfg->name,
             cfg->adc_channel,
             cfg->led_channel);

    for (;;) {
        uint16_t raw = adc_reader_get_raw(cfg->adc_channel);
        uint8_t duty = adc_reader_to_duty(raw);

        leds_set_duty((led_channel_t)cfg->led_channel, duty);

        contador++;

        if (contador >= TASK_LOG_EVERY_N) {
            contador = 0;

            ESP_LOGI(TAG,
                     "[%s] raw=%4d duty=%3d heap=%lu wm=%u",
                     cfg->name,
                     raw,
                     duty,
                     (unsigned long)esp_get_free_heap_size(),
                     (unsigned int)uxTaskGetStackHighWaterMark(NULL));
        }

        vTaskDelay(pdMS_TO_TICKS(TASK_PERIOD_MS));
    }
}

/* Se crean tres tareas usando la misma funcion, pero con parametros diferentes */
void tasks_create_all(void) {
    static const task_params_t params_ch0 = {0, 0, "POT0-LED0"};
    static const task_params_t params_ch1 = {1, 1, "POT1-LED1"};
    static const task_params_t params_ch2 = {2, 2, "POT2-LED2"};

    xTaskCreate(vTaskPotLED, "PotLED_0", 2048, (void *)&params_ch0, 1, &h0);
    xTaskCreate(vTaskPotLED, "PotLED_1", 2048, (void *)&params_ch1, 2, &h1);
    xTaskCreate(vTaskPotLED, "PotLED_2", 2048, (void *)&params_ch2, 3, &h2);
}
