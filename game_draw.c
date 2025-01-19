#include "game_draw.h"
#include "oled.h"
#include "Fonts.h"
#include "flash.h"
#include <stdio.h>

void draw_paddle(Paddle* paddle) {
    // Draw the paddle at its current position
    draw_bitmap(paddle->x, paddle->y, paddle_bitmap, PADDLE_WIDTH, PADDLE_HEIGHT);
}

void draw_ball(Ball* ball) {
    // Draw the ball at its current position
    draw_bitmap(ball->x, ball->y, ball_bitmap, BALL_SIZE, BALL_SIZE);
}

void draw_block(Block* block) {
    // Draw a block based on its type
    switch (block->type) {
        case BLOCK_TYPE_1: 
            draw_bitmap(block->x, block->y, block_bitmap_1, BLOCK_WIDTH, BLOCK_HEIGHT); 
            break;
        case BLOCK_TYPE_2: 
            draw_bitmap(block->x, block->y, block_bitmap_2, BLOCK_WIDTH, BLOCK_HEIGHT); 
            break;
        case BLOCK_TYPE_3: 
            draw_bitmap(block->x, block->y, block_bitmap_3, BLOCK_WIDTH, BLOCK_HEIGHT); 
            break;
        case BLOCK_TYPE_4: 
            draw_bitmap(block->x, block->y, block_bitmap_4, BLOCK_WIDTH, BLOCK_HEIGHT); 
            break;
        default:
            break;
    }
}

void draw_blocks(void) {
    // Iterate through all blocks and draw only active ones
    for (int i = 0; i < NUM_BLOCKS; i++) {
        if (blocks[i].is_active) {
            draw_block(&blocks[i]);
        }
    }
}

void draw_game(Paddle* paddle, Ball* ball) {
    // Clear the OLED screen before drawing game elements
    ssd1306_clear_screen(0x00);

    // Draw the lives icon and count
    draw_bitmap(2, 0, block_bitmap_heart, 8, 8); // Heart icon
    draw_digit(12, 0, (uint8_t)get_lives());

    // Draw the score icon and current score
    draw_bitmap(64, 0, star_bitmap, 8, 8); // Star icon
    draw_number(80, 0, get_score());

    // Draw game elements: paddle, ball, and blocks
    draw_paddle(paddle);
    draw_ball(ball);
    draw_blocks();

    // Refresh the screen to apply changes
    ssd1306_refresh_gram();
}

void game_over_display(void) {
    // Clear the screen before displaying "Game Over"
    ssd1306_clear_screen(0x00);

    // Display "GAME OVER" message in the center of the screen
    ssd1306_display_string((SCREEN_WIDTH - 72) / 2, 10, "GAME OVER", 12, 1);

    // Display the final score below the message
    ssd1306_display_string(SCREEN_WIDTH - 100, 2 * SCREEN_HEIGHT / 3 - 2, "SCORE:", 10, 1);
    draw_number(SCREEN_WIDTH - 50, 2 * SCREEN_HEIGHT / 3, get_score());

    // Refresh the screen to show the "Game Over" display
    ssd1306_refresh_gram();

    // Delay for a moment before allowing further action
    for (volatile uint32_t delay = 0; delay < 10000000; delay++);
}
