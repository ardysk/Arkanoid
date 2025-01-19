#ifndef _USE_FONTS_H
#define _USE_FONTS_H

#include "LIB_Config.h"


/**
 * @brief Bitmap resources for graphical elements and animations.
 */
extern const uint8_t block_bitmap_arrow[];          ///< Bitmap for arrow block.
extern const uint8_t block_bitmap_heart[];          ///< Bitmap for heart block.
extern const uint8_t star_bitmap[];                 ///< Bitmap for star element.
extern const uint8_t paddle_bitmap[4];              ///< Bitmap for paddle element.
extern const uint8_t ball_bitmap[2];                ///< Bitmap for ball element.
extern const uint8_t block_bitmap[5];               ///< Base block bitmap.
extern const uint8_t block_bitmap_1[];              ///< Bitmap for block type 1.
extern const uint8_t block_bitmap_2[];              ///< Bitmap for block type 2.
extern const uint8_t block_bitmap_3[];              ///< Bitmap for block type 3.
extern const uint8_t block_bitmap_4[];              ///< Bitmap for block type 4.
extern const uint8_t block_bitmap_5[];              ///< Bitmap for block type 5.
extern const uint8_t block_bitmap_6[];              ///< Bitmap for block type 6.
extern const uint8_t block_bitmap_stone[];          ///< Bitmap for stone block.
extern const uint8_t block_bitmap_steel[];          ///< Bitmap for steel block.
extern const uint8_t block_bitmap_wood[];           ///< Bitmap for wood block.
extern const uint8_t block_bitmap_shaded[];         ///< Bitmap for shaded block.
extern const uint8_t block_animation_frame_1[];     ///< Animation frame 1 for blocks.
extern const uint8_t block_animation_frame_2[];     ///< Animation frame 2 for blocks.
extern const uint8_t block_animation_frame_3[];     ///< Animation frame 3 for blocks.
extern const uint8_t block_animation_frame_4[];     ///< Animation frame 4 for blocks.
extern const uint8_t block_animation_frame_5[];     ///< Animation frame 5 for blocks.
extern const uint8_t block_animation_frame_6[];     ///< Animation frame 6 for blocks.

/**
 * @brief Font resources for text rendering.
 */
extern const uint8_t font_digits[10][8];            ///< Bitmap for numeric digits (0-9).
extern const uint8_t c_chFont1624[4][48];           ///< Font: 16x24 size.
extern const uint8_t c_chFont1206[95][12];          ///< Font: 12x6 size.
extern const uint8_t c_chFont1608[95][16];          ///< Font: 16x8 size.
extern const uint8_t c_chFont1612[11][32];          ///< Font: 16x12 size.
extern const uint8_t c_chFont3216[11][64];          ///< Font: 32x16 size.
extern const uint8_t c_chBmp4016[96];               ///< Font: 40x16 bitmap.

extern const uint8_t c_chSingal816[16];             ///< Signal icon (8x16 size).
extern const uint8_t c_chMsg816[16];                ///< Message icon (8x16 size).
extern const uint8_t c_chBluetooth88[8];            ///< Bluetooth icon (8x8 size).
extern const uint8_t c_chBat816[16];                ///< Battery icon (8x16 size).
extern const uint8_t c_chGPRS88[8];                 ///< GPRS icon (8x8 size).
extern const uint8_t c_chAlarm88[8];                ///< Alarm icon (8x8 size).

#endif // _USE_FONTS_H

