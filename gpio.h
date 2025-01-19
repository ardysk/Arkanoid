#ifndef GPIO_H
#define GPIO_H

#include "MKL05Z4.h"

/**
 * @brief Base addresses for GPIO registers (compliant with KL05Z documentation).
 */
#define GPIOA ((GPIO_Type *)0x400FF000u) ///< Base address for GPIOA
#define GPIOB ((GPIO_Type *)0x400FF040u) ///< Base address for GPIOB

/**
 * @brief Configures a pin as an output.
 *
 * Enables the clock for the specified port and sets the pin as an output.
 *
 * @param port Pointer to the port (PORTA, PORTB).
 * @param gpio Pointer to the GPIO register (GPIOA, GPIOB).
 * @param pin Pin number to configure as output.
 */
void gpio_set_output(PORT_Type *port, GPIO_Type *gpio, uint32_t pin);

/**
 * @brief Sets a pin to high state.
 *
 * @param gpio Pointer to the GPIO register.
 * @param pin Pin number to set high.
 */
void gpio_set_high(GPIO_Type *gpio, uint32_t pin);

/**
 * @brief Sets a pin to low state.
 *
 * @param gpio Pointer to the GPIO register.
 * @param pin Pin number to set low.
 */
void gpio_set_low(GPIO_Type *gpio, uint32_t pin);

/**
 * @brief Toggles the state of a pin.
 *
 * @param gpio Pointer to the GPIO register.
 * @param pin Pin number to toggle.
 */
void gpio_toggle(GPIO_Type *gpio, uint32_t pin);

#endif // GPIO_H
