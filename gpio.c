#include "gpio.h"

void gpio_set_output(PORT_Type *port, GPIO_Type *gpio, uint32_t pin) {
    if (port == PORTA) {
        SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;  // Turn on PORTA CLK
    } else if (port == PORTB) {
        SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;  // Turn on PORTB CLK
    }

    // Konfiguracja pinu jako GPIO
    port->PCR[pin] = PORT_PCR_MUX(1);  // Set MUX na GPIO
    gpio->PDDR |= (1 << pin);          // Set pin as output
}

void gpio_set_high(GPIO_Type *gpio, uint32_t pin) {
    gpio->PSOR = (1 << pin);
}

void gpio_set_low(GPIO_Type *gpio, uint32_t pin) {
    gpio->PCOR = (1 << pin);
}

void gpio_toggle(GPIO_Type *gpio, uint32_t pin) {
    gpio->PTOR = (1 << pin);
}
