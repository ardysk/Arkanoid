#ifndef SCORES_H
#define SCORES_H

#include <stdint.h>

/**
 * @brief Maximum number of top scores stored.
 */
#define MAX_TOP_SCORES 3 ///< Maximum number of high scores to store.

/**
 * @brief Structure representing a score entry.
 */
typedef struct {
    char nickname[6]; ///< Player's nickname (up to 5 characters + null-terminator).
    int score;        ///< Player's score (matches the return type of `get_score()`).
} ScoreEntry;

/**
 * @brief Initializes the top scores system.
 *
 * Resets the stored scores to default values.
 */
void init_scores(void);

/**
 * @brief Updates the list of top scores.
 *
 * Adds a new score entry if it qualifies for the top scores.
 *
 * @param nickname Player's nickname.
 * @param score Player's score.
 */
void update_top_scores(const char* nickname, int score);

/**
 * @brief Retrieves the list of top scores.
 *
 * @return const ScoreEntry* Pointer to the array of top scores.
 */
const ScoreEntry* get_top_scores(void);

#endif // SCORES_H
