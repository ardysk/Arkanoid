#ifndef OLED_H
#define OLED_H

#include <stdint.h>

/**
 * @brief OLED display dimensions.
 */
#define SSD1306_WIDTH  128 ///< Width of the SSD1306 OLED display in pixels.
#define SSD1306_HEIGHT 64  ///< Height of the SSD1306 OLED display in pixels.
#define SCREEN_WIDTH 128   ///< Alias for display width.
#define SCREEN_HEIGHT 64   ///< Alias for display height.

/**
 * @brief Initializes the SSD1306 OLED display.
 */
void ssd1306_init(void);

/**
 * @brief Turns the OLED display on.
 */
void ssd1306_display_on(void);

/**
 * @brief Turns the OLED display off.
 */
void ssd1306_display_off(void);

/**
 * @brief Refreshes the graphic RAM (GRAM) on the display.
 */
void ssd1306_refresh_gram(void);

/**
 * @brief Sends a byte of data or a command to the OLED display.
 *
 * @param chData Data to send.
 * @param chCmd  Command type: 0 for command, 1 for data.
 */
void ssd1306_write_byte(uint8_t chData, uint8_t chCmd);

/**
 * @brief Clears the entire OLED screen.
 *
 * @param chFill Fill value (0x00 for black, 0xFF for white).
 */
void ssd1306_clear_screen(uint8_t chFill);

/**
 * @brief Clears a part of the OLED screen.
 *
 * @param chFill Fill value (0x00 for black, 0xFF for white).
 */
void ssd1306_clear_screen_part(uint8_t chFill);

/**
 * @brief Draws a single pixel on the OLED screen.
 *
 * @param chXpos X-coordinate of the pixel.
 * @param chYpos Y-coordinate of the pixel.
 * @param chPoint State of the pixel: 1 to turn it on, 0 to turn it off.
 */
void ssd1306_draw_point(uint8_t chXpos, uint8_t chYpos, uint8_t chPoint);

/**
 * @brief Displays a single character on the OLED screen.
 *
 * @param chXpos X-coordinate of the character.
 * @param chYpos Y-coordinate of the character.
 * @param chChr  Character to display.
 * @param chSize Font size.
 * @param chMode Display mode: 1 for normal, 0 for inverted.
 */
void ssd1306_display_char(uint8_t chXpos, uint8_t chYpos, uint8_t chChr, uint8_t chSize, uint8_t chMode);

/**
 * @brief Displays a string of characters on the OLED screen.
 *
 * @param chXpos Initial X-coordinate.
 * @param chYpos Initial Y-coordinate.
 * @param pchString Pointer to the string to display.
 * @param chSize Font size.
 * @param chMode Display mode: 1 for normal, 0 for inverted.
 */
void ssd1306_display_string(uint8_t chXpos, uint8_t chYpos, const uint8_t *pchString, uint8_t chSize, uint8_t chMode);

/**
 * @brief Draws a custom string using a specified font.
 *
 * @param x X-coordinate of the string.
 * @param y Y-coordinate of the string.
 * @param str Pointer to the string to draw.
 * @param font Pointer to the font data.
 * @param font_width Width of a single character in the font.
 * @param font_height Height of a single character in the font.
 */
void ssd1306_draw_string_custom(uint8_t x, uint8_t y, const char* str, const uint8_t font[][12], uint8_t font_width, uint8_t font_height);

/**
 * @brief Sets the contrast level of the OLED display.
 *
 * @param contrast Contrast value (0 to 255).
 */
void ssd1306_set_contrast(uint8_t contrast);

/**
 * @brief Inverts the display colors.
 *
 * @param invert 1 to invert, 0 to revert to normal.
 */
void ssd1306_set_invert(uint8_t invert);

/**
 * @brief Sets the refresh rate of the OLED display.
 *
 * @param value Refresh rate value (0x00 for minimum, 0xFF for maximum).
 */
void ssd1306_set_framerate(uint8_t value);

/**
 * @brief Sets the display orientation.
 *
 * @param rotate 0 for normal orientation, 1 for rotated orientation.
 */
void ssd1306_set_orientation(uint8_t rotate);

/**
 * @brief Sets the addressing mode of the display.
 *
 * @param mode 0x00 for horizontal, 0x01 for vertical, 0x02 for page addressing.
 */
void ssd1306_set_addressing_mode(uint8_t mode);

/**
 * @brief Draws a bitmap image on the OLED screen.
 *
 * @param x X-coordinate of the bitmap.
 * @param y Y-coordinate of the bitmap.
 * @param bitmap Pointer to the bitmap data.
 * @param width Width of the bitmap in pixels.
 * @param height Height of the bitmap in pixels.
 */
void draw_bitmap(uint8_t x, uint8_t y, const uint8_t *bitmap, uint8_t width, uint8_t height);

/**
 * @brief Clears a single pixel from the OLED screen.
 *
 * @param x X-coordinate of the pixel.
 * @param y Y-coordinate of the pixel.
 */
void clear_bitmap(uint8_t x, uint8_t y);

/**
 * @brief Gets the state of a pixel on the OLED screen.
 *
 * @param x X-coordinate of the pixel.
 * @param y Y-coordinate of the pixel.
 * @return uint8_t State of the pixel: 1 if on, 0 if off.
 */
uint8_t ssd1306_get_pixel(uint8_t x, uint8_t y);

/**
 * @brief Sets the state of a pixel on the OLED screen.
 *
 * @param x X-coordinate of the pixel.
 * @param y Y-coordinate of the pixel.
 * @param state State to set: 1 to turn on, 0 to turn off.
 */
void ssd1306_set_pixel(uint8_t x, uint8_t y, uint8_t state);

/**
 * @brief Draws a single digit on the OLED screen.
 *
 * @param x X-coordinate of the digit.
 * @param y Y-coordinate of the digit.
 * @param digit The digit to draw (0-9).
 */
void draw_digit(uint8_t x, uint8_t y, uint8_t digit);

/**
 * @brief Draws a number on the OLED screen.
 *
 * @param x X-coordinate of the number.
 * @param y Y-coordinate of the number.
 * @param score The number to draw.
 */
void draw_number(uint8_t x, uint8_t y, int score);

#endif // OLED_H
