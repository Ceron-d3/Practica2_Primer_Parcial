/**
 * @file leds.c
 * @brief Inicializacion y control PWM de los LEDs mediante LEDC.
 */
#ifndef ADC_READER_H
#define ADC_READER_H
#include <stdint.h>

void adc_reader_init(void);
uint16_t adc_reader_get_raw(uint8_t channel);

static inline uint8_t adc_reader_to_duty(uint16_t raw) {
    return (uint8_t)((raw * 255) / 4095);
}

#endif