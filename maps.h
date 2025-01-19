#ifndef MAPS_H
#define MAPS_H

/**
 * @brief Map dimensions and configuration.
 */
#define MAP_WIDTH 10      ///< Number of blocks in each row of the map.
#define MAP_HEIGHT 4      ///< Number of blocks in each column of the map.
#define NUM_MAPS 25       ///< Total number of predefined maps.

/**
 * @brief Array containing predefined maps.
 *
 * Each map is represented as a 2D array of integers where:
 * - 0 represents an empty space.
 * - Positive integers represent different block types.
 * 
 * Dimensions: [NUM_MAPS][MAP_HEIGHT][MAP_WIDTH].
 */
extern const int maps[NUM_MAPS][MAP_HEIGHT][MAP_WIDTH];

#endif // MAPS_H
