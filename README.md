# Practica 2 - Control de brillo de LEDs con FreeRTOS

## Integrante
- Eduardo Cerón

## Descripción del proyecto

Este proyecto implementa un sistema multitarea en ESP32 usando FreeRTOS y ESP-IDF. El sistema lee tres potenciometros mediante el ADC y controla el brillo de tres LEDs mediante PWM. Cada potenciometro controla un LED de forma independiente. La practica utiliza una sola funcion de tarea llamada `vTaskPotLED()`, la cual recibe su configuracion mediante `pvParameters`. De esta forma se evita duplicar codigo y se reutiliza la misma logica para los tres canales.

## Tabla de pines

| Elemento | GPIO |
|---|---:|
| POT0 | GPIO32 |
| POT1 | GPIO33 |
| POT2 | GPIO34 |
| LED rojo | GPIO25 |
| LED verde | GPIO26 |
| LED azul | GPIO27 |

## Funcionamiento esperado

Al girar cada potenciometro, cambia el valor ADC leído por la ESP32. Ese valor se convierte a un duty cycle de 8 bits mediante la relacion:

```c
duty = raw * 255 / 4095;
