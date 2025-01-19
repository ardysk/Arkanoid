#ifndef MENU_H
#define MENU_H

#include <stdint.h>

/**
 * @brief SysTick handler and time functions.
 */

/**
 * @brief SysTick interrupt handler.
 *
 * Increments the global time counters.
 */
void SysTick_Handler(void);

/**
 * @brief Returns the current time in milliseconds.
 *
 * @return uint32_t Current time in milliseconds.
 */
uint32_t millis(void);

/**
 * @brief Configures the SysTick timer for 1ms interrupts.
 */
void setup_systick(void);

/**
 * @brief Waits for a key to be released.
 *
 * Blocks until no key is pressed.
 */
void wait_for_key_release(void);

/**
 * @brief Implements a simple delay for debouncing.
 */
void debounce_delay(void);

/**
 * @brief Functions related to menu rendering and interactions.
 */

/**
 * @brief Displays the score board on the OLED screen.
 */
void show_score_board(void);

/**
 * @brief Allows the user to enter a nickname.
 */
void enter_username(void);

/**
 * @brief Displays the OLED options menu.
 *
 * Options include brightness, refresh rate, and display mode.
 */
void show_oled_options(void);

/**
 * @brief Displays the main menu and handles user interactions.
 */
void show_menu(void);

#endif // MENU_H
