#ifndef GAME_DRAW_H
#define GAME_DRAW_H

#include "arkanoid.h"

/**
 * @brief Functions for rendering game elements on the screen.
 */

/**
 * @brief Draws the paddle on the screen.
 *
 * @param paddle Pointer to the paddle structure containing its position.
 */
void draw_paddle(Paddle* paddle);

/**
 * @brief Draws the ball on the screen.
 *
 * @param ball Pointer to the ball structure containing its position and size.
 */
void draw_ball(Ball* ball);

/**
 * @brief Draws a single block on the screen.
 *
 * @param block Pointer to the block structure containing its position and type.
 */
void draw_block(Block* block);

/**
 * @brief Draws all active blocks on the screen.
 */
void draw_blocks(void);

/**
 * @brief Renders the entire game screen, including the paddle, ball, and blocks.
 *
 * @param paddle Pointer to the paddle structure.
 * @param ball Pointer to the ball structure.
 */
void draw_game(Paddle* paddle, Ball* ball);

/**
 * @brief Displays the "Game Over" screen.
 */
void game_over_display(void);

#endif // GAME_DRAW_H
