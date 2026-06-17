/**
 * @file leds.c
 * @brief Inicializacion y control PWM de los LEDs mediante LEDC.
 */
 
idf_component_register(
    SRCS
        "main.c"
        "leds.c"
        "adc_reader.c"
        "tasks.c"
    INCLUDE_DIRS
        "."
)