/**
 * @file leds.c
 * @brief Inicializacion y control PWM de los LEDs mediante LEDC.
 */
#include "adc_reader.h"
#include "esp_adc/adc_oneshot.h"

static adc_oneshot_unit_handle_t adc1_handle;

static const adc_channel_t adc_channels[3] = {
    ADC_CHANNEL_4,   // GPIO32
    ADC_CHANNEL_5,   // GPIO33
    ADC_CHANNEL_6    // GPIO34
};

void adc_reader_init(void) {
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_1,
        .ulp_mode = ADC_ULP_MODE_DISABLE
    };

    adc_oneshot_new_unit(&init_config, &adc1_handle);

    adc_oneshot_chan_cfg_t channel_config = {
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_12
    };

    for (int i = 0; i < 3; i++) {
        adc_oneshot_config_channel(adc1_handle, adc_channels[i], &channel_config);
    }
}

uint16_t adc_reader_get_raw(uint8_t channel) {
    int raw = 0;

    if (channel > 2) {
        return 0;
    }

    adc_oneshot_read(adc1_handle, adc_channels[channel], &raw);

    return (uint16_t)raw;
}