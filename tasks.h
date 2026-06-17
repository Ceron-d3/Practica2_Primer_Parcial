#ifndef TASKS_H
#define TASKS_H
#include <stdint.h>

typedef struct {
    uint8_t adc_channel;
    uint8_t led_channel;
    const char *name;
} task_params_t;

void vTaskPotLED(void *pvParameters);
void tasks_create_all(void);

#endif