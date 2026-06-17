/**
 * @file leds.c
 * @brief Inicializacion y control PWM de los LEDs mediante LEDC.
 */
#include "leds.h"
#define LED0_GPIO 25
#define LED1_GPIO 26
#define LED2_GPIO 27

#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_FREQUENCY_HZ       5000
#define LEDC_RESOLUTION         LEDC_TIMER_8_BIT

static const int led_gpios[3] = {
    LED0_GPIO,
    LED1_GPIO,
    LED2_GPIO
};

void leds_init(void) {
    ledc_timer_config_t timer_config = {
        .speed_mode       = LEDC_MODE,
        .duty_resolution  = LEDC_RESOLUTION,
        .timer_num        = LEDC_TIMER,
        .freq_hz          = LEDC_FREQUENCY_HZ,
        .clk_cfg          = LEDC_AUTO_CLK
    };

    ledc_timer_config(&timer_config);

    for (int i = 0; i < 3; i++) {
        ledc_channel_config_t channel_config = {
            .gpio_num   = led_gpios[i],
            .speed_mode = LEDC_MODE,
            .channel    = (ledc_channel_t)i,
            .intr_type  = LEDC_INTR_DISABLE,
            .timer_sel  = LEDC_TIMER,
            .duty       = 0,
            .hpoint     = 0
        };

        ledc_channel_config(&channel_config);
    }
}

void leds_set_duty(led_channel_t channel, uint8_t duty) {
    ledc_set_duty(LEDC_MODE, channel, duty);
    ledc_update_duty(LEDC_MODE, channel);
}