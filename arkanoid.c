#include "arkanoid.h"
#include "maps.h"
#include <stdbool.h>
#include <stdlib.h> 

// Global variables
Block blocks[NUM_BLOCKS];
int current_score = 0;
int current_map = 0;
int game_speed = 40;
int lives = MAX_LIVES;
static bool ball_is_reset = false; // Restrict scope to this file

// Score values for block types
#define SCORE_BLOCK_TYPE_1 10
#define SCORE_BLOCK_TYPE_2 20
#define SCORE_BLOCK_TYPE_3 30
#define SCORE_BLOCK_TYPE_4 40

// Convert an integer map to a Block map
void convert_map(const int map[MAP_HEIGHT][MAP_WIDTH]) {
    const int y_offset = 10; // Offset of 10px from the top edge
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            int index = i * MAP_WIDTH + j;
            blocks[index].x = (uint8_t)(j * (BLOCK_WIDTH + 1)); // Explicit cast
            blocks[index].y = (uint8_t)(i * (BLOCK_HEIGHT + 1) + y_offset); // Explicit cast
            blocks[index].type = (BlockType)map[i][j];
            blocks[index].is_active = (map[i][j] != 0); // Bloki z typem 0 s¹ nieaktywne
        }
    }
}

// Load the next map
void load_next_map(void) {
    if (current_map >= NUM_MAPS) {
        current_map = 0; // Restart from the first map
    }
    convert_map(maps[current_map]);
    current_map++;
}

// Reset ball position
void reset_ball(Ball* ball, Paddle* paddle) {
    ball->x = paddle->x + PADDLE_WIDTH / 2 - BALL_SIZE / 2;
    ball->y = paddle->y - BALL_SIZE - 1;
    ball->dx = 0; // Stop horizontal movement
    ball->dy = 0; // Stop vertical movement
    ball_is_reset = true;
}

// Start ball movement after delay
static void start_ball_after_delay(Ball* ball) { // Restrict scope to this file
    for (volatile int i = 0; i < 2000000; i++); // Approx. 2-second delay
    ball->dx = 1; // Start moving horizontally
    ball->dy = -1; // Start moving upwards
    ball_is_reset = false;
}

// Update ball position
void ball_update(Ball* ball, Paddle* paddle) {
    const int y_offset = 10; // Offset for the top edge collision

    // If ball is reset, wait and start movement after delay
    if (ball_is_reset) {
        reset_ball(ball, paddle);
        start_ball_after_delay(ball);
        return;
    }

    ball->x += ball->dx;
    ball->y += ball->dy;

    // Handle collisions with screen edges
    if (ball->x <= 0 || ball->x + BALL_SIZE >= SCREEN_WIDTH) {
        ball->dx = -ball->dx;
    }
    if (ball->y <= y_offset) { // Use offset for the top edge
        ball->dy = -ball->dy;
    }

    // Handle collision with paddle
    if (ball->y + BALL_SIZE >= paddle->y - 1 && // 1px above paddle
        ball->x + BALL_SIZE >= paddle->x &&
        ball->x <= paddle->x + PADDLE_WIDTH) {
        ball->dy = -ball->dy; // Reverse vertical direction

        // Adjust ball direction based on collision point
        int relative_x = (ball->x + BALL_SIZE / 2) - paddle->x;
        if (relative_x < PADDLE_WIDTH / 3) {
            ball->dx = -2; // Left side of paddle
        } else if (relative_x > 2 * PADDLE_WIDTH / 3) {
            ball->dx = 2; // Right side of paddle
        } else {
            ball->dx = 1; // Middle of paddle
        }
    }

    // Handle collisions with blocks
    for (int i = 0; i < NUM_BLOCKS; i++) {
        if (blocks[i].is_active && check_collision(ball, &blocks[i])) {
            handle_block_collision(ball, &blocks[i]);
        }
    }

    // If the ball falls below the screen, reset it on the paddle
    if (ball->y > SCREEN_HEIGHT) {
        lives--;
        if (lives > 0) {
            reset_ball(ball, paddle); // Reset ball on paddle
        }
    }
}

// Advanced collision check
int check_collision(Ball* ball, Block* block) {
    if (ball->x < block->x + BLOCK_WIDTH &&
        ball->x + BALL_SIZE > block->x &&
        ball->y < block->y + BLOCK_HEIGHT &&
        ball->y + BALL_SIZE > block->y) {
        // Determine collision side
        int ball_center_x = ball->x + BALL_SIZE / 2;
        int ball_center_y = ball->y + BALL_SIZE / 2;

        int block_center_x = block->x + BLOCK_WIDTH / 2;
        int block_center_y = block->y + BLOCK_HEIGHT / 2;

        int dx = ball_center_x - block_center_x;
        int dy = ball_center_y - block_center_y;

        if (abs(dx) > abs(dy)) {
            ball->dx = (dx > 0) ? 1 : -1; // Horizontal collision
        } else {
            ball->dy = (dy > 0) ? 1 : -1; // Vertical collision
        }

        return 1;
    }
    return 0;
}

// Handle block collision
void handle_block_collision(Ball* ball, Block* block) {
    block->is_active = 0; // Deactivate block

    // Add points based on block type
    switch (block->type) {
        case BLOCK_TYPE_1: current_score += SCORE_BLOCK_TYPE_1; break;
        case BLOCK_TYPE_2: current_score += SCORE_BLOCK_TYPE_2; break;
        case BLOCK_TYPE_3: current_score += SCORE_BLOCK_TYPE_3; break;
        case BLOCK_TYPE_4: current_score += SCORE_BLOCK_TYPE_4; break;
        default: current_score += 10; break;
    }
}

// Check if all blocks are destroyed
int check_map_complete(void) {
    for (int i = 0; i < NUM_BLOCKS; i++) {
        if (blocks[i].is_active) {
            return 0;
        }
    }
    return 1;
}

// Update paddle position
void paddle_update(Paddle* paddle, uint8_t touch_pos) {
    paddle->x = touch_pos * (SCREEN_WIDTH - PADDLE_WIDTH) / 100;
}

// Get current lives
int get_lives(void) {
    return lives;
}

// Get current score
int get_score(void) {
    return current_score;
}

// Initialize game
void game_init(void) {
    current_score = 0;
    current_map = 0;
    lives = MAX_LIVES;
    load_next_map();
}
