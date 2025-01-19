#ifndef LIB_CONFIG_H
#define LIB_CONFIG_H

#include "MKL05Z4.h"  // Nag³ówkowy plik mikrokontrolera
#include "gpio.h"
#include "spi.h"

// Definicje pinów OLED (dostosowane do FRDM-KL05Z)
#define OLED_CS_PIN   6   // PTB6
#define OLED_DC_PIN   7   // PTB7
#define OLED_RES_PIN  8   // PTB8

// Makra do manipulacji GPIO dla OLED
#define OLED_CS_LOW()     gpio_set_low(GPIOB, OLED_CS_PIN)
#define OLED_CS_HIGH()    gpio_set_high(GPIOB, OLED_CS_PIN)

#define OLED_DC_LOW()     gpio_set_low(GPIOB, OLED_DC_PIN)
#define OLED_DC_HIGH()    gpio_set_high(GPIOB, OLED_DC_PIN)

#define OLED_RES_LOW()    gpio_set_low(GPIOB, OLED_RES_PIN)
#define OLED_RES_HIGH()   gpio_set_high(GPIOB, OLED_RES_PIN)

// Funkcja do opóŸnienia (dla kompatybilnoœci z STM32)
#define DELAY(ms) for (volatile int i = 0; i < (ms * 1000); i++)

#endif // LIB_CONFIG_H
