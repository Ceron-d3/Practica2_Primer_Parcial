/**
 * @file leds.c
 * @brief Inicializacion y control PWM de los LEDs mediante LEDC.
 */
#ifndef LEDS_H
#define LEDS_H
#include <stdint.h>
#include "driver/ledc.h"

typedef ledc_channel_t led_channel_t;

void leds_init(void);
void leds_set_duty(led_channel_t channel, uint8_t duty);

#endif