#ifndef ARKANOID_H
#define ARKANOID_H

#include <stdint.h>

/** 
 * @brief Screen and game element parameters.
 */
#define SCREEN_WIDTH 128        ///< Screen width in pixels.
#define SCREEN_HEIGHT 64        ///< Screen height in pixels.
#define PADDLE_WIDTH 20         ///< Paddle width in pixels.
#define PADDLE_HEIGHT 5         ///< Paddle height in pixels.
#define BALL_SIZE 2             ///< Ball size in pixels.
#define BLOCK_WIDTH 12          ///< Block width in pixels.
#define BLOCK_HEIGHT 6          ///< Block height in pixels.
#define MAX_LIVES 3             ///< Maximum number of lives.
#define NUM_BLOCKS (MAP_WIDTH * MAP_HEIGHT) ///< Total number of blocks on the screen.

/** 
 * @brief Map parameters.
 */
#define NUM_MAPS 25             ///< Number of available maps.
#define MAP_WIDTH 10            ///< Width of the map in blocks.
#define MAP_HEIGHT 4            ///< Height of the map in blocks.

/**
 * @brief Types of blocks in the game.
 */
typedef enum {
    BLOCK_TYPE_1,               ///< Type 1 block.
    BLOCK_TYPE_2,               ///< Type 2 block.
    BLOCK_TYPE_3,               ///< Type 3 block.
    BLOCK_TYPE_4,               ///< Type 4 block.
    BLOCK_TYPE_5,               ///< Type 5 block.
    BLOCK_TYPE_6,               ///< Type 6 block.
    BLOCK_TYPE_STONE,           ///< Stone block (harder to break).
    BLOCK_TYPE_STEEL,           ///< Steel block (stronger).
    BLOCK_TYPE_WOOD,            ///< Wooden block.
    BLOCK_TYPE_SHADED           ///< Shaded block (visual effect).
} BlockType;

/**
 * @brief Structure representing the ball.
 */
typedef struct {
    uint8_t x, y;               ///< Current position of the ball.
    int8_t dx, dy;              ///< Movement direction of the ball.
} Ball;

/**
 * @brief Structure representing the paddle.
 */
typedef struct {
    uint8_t x, y;               ///< Current position of the paddle.
} Paddle;

/**
 * @brief Structure representing a block.
 */
typedef struct {
    uint8_t x, y;               ///< Position of the block.
    BlockType type;             ///< Type of the block.
    uint8_t is_active;          ///< Indicates if the block is active (1) or destroyed (0).
} Block;

/**
 * @brief Global variables.
 */
extern Block blocks[NUM_BLOCKS]; ///< Array of blocks for the current map.
extern int current_score;        ///< Current score of the player.
extern int current_map;          ///< Index of the current map.
extern int game_speed;           ///< Current game speed.
extern int lives;                ///< Number of lives remaining for the player.

/**
 * @brief Game functions.
 */

/**
 * @brief Converts a given map array to the block array.
 * 
 * @param map The 2D array representing the map layout.
 */
void convert_map(const int map[MAP_HEIGHT][MAP_WIDTH]);

/**
 * @brief Initializes the game settings.
 */
void game_init(void);

/**
 * @brief Initializes the map by resetting the blocks.
 */
void map_init(void);

/**
 * @brief Loads the next map in the sequence.
 */
void load_next_map(void);

/**
 * @brief Updates the paddle's position based on input.
 * 
 * @param paddle Pointer to the paddle structure.
 * @param touch_pos The position from the touch input (0-100 scale).
 */
void paddle_update(Paddle* paddle, uint8_t touch_pos);

/**
 * @brief Updates the ball's position and handles collisions.
 * 
 * @param ball Pointer to the ball structure.
 * @param paddle Pointer to the paddle structure.
 */
void ball_update(Ball* ball, Paddle* paddle);

/**
 * @brief Checks for a collision between the ball and a block.
 * 
 * @param ball Pointer to the ball structure.
 * @param block Pointer to the block structure.
 * @return 1 if a collision is detected, 0 otherwise.
 */
int check_collision(Ball* ball, Block* block);

/**
 * @brief Handles the collision between the ball and a block.
 * 
 * Updates the block state and adjusts the ball's direction.
 * 
 * @param ball Pointer to the ball structure.
 * @param block Pointer to the block structure.
 */
void handle_block_collision(Ball* ball, Block* block);

/**
 * @brief Resets the ball position to the initial state.
 * 
 * @param ball Pointer to the ball structure.
 * @param paddle Pointer to the paddle structure.
 */
void reset_ball(Ball* ball, Paddle* paddle);

/**
 * @brief Updates the game speed.
 */
void game_speed_update(void);

/**
 * @brief Checks if the current map is complete.
 * 
 * @return 1 if all blocks are destroyed, 0 otherwise.
 */
int check_map_complete(void);

/**
 * @brief Retrieves the player's remaining lives.
 * 
 * @return int Number of lives remaining.
 */
int get_lives(void);

/**
 * @brief Retrieves the player's current score.
 * 
 * @return int Current score.
 */
int get_score(void);

#endif // ARKANOID_H
