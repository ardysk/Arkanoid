#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

/**
 * @brief Initializes the keyboard module.
 *
 * Configures necessary peripherals for detecting key inputs.
 */
void Keyboard_Init(void);

/**
 * @brief Reads the currently pressed key.
 *
 * @return uint8_t The key code of the currently pressed key (0-15) or 0xFF if no key is pressed.
 */
uint8_t Keyboard_ReadKey(void);

/**
 * @brief Key mapping for the keyboard.
 *
 * A 4x3 matrix representing the key layout:
 * - Rows: 4 (row 0 to row 3)
 * - Columns: 3 (column 0 to column 2)
 *
 * Each entry contains a string representing the key value (e.g., "1", "2", "A").
 */
extern const char* key_map[4][3];

#endif // KEYBOARD_H
