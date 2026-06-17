/**
 * @file main.c
 * @brief Practica 2
 *
 * En esta practica se comprobo que FreeRTOS permite ejecutar tres tareas independientes
 * usando una misma funcion de tarea parametrizada mediante pvParameters. Cada tarea recibe
 * su canal ADC y canal PWM correspondiente, evitando duplicar codigo. Tambien se observo
 * que vTaskDelay permite que el planificador alterne entre tareas sin bloquear todo el sistema.
 *
 * Integrantes:
 * - Eduardo Cerón
 */

 
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
