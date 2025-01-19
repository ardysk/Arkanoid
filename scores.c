#include "scores.h"
#include <string.h>

//Best scores buffer
static ScoreEntry top_scores[MAX_TOP_SCORES] = { 
    {"T", 0},
};

void update_top_scores(const char* nickname, int score) {
    if (score <= 0) {
        return; //Don't update if score is 0
    }

    for (int i = 0; i < MAX_TOP_SCORES; i++) {
        if (score > top_scores[i].score) {
            // Set lower other scores
            for (int j = MAX_TOP_SCORES - 1; j > i; j--) {
                top_scores[j] = top_scores[j - 1];
            }

            // Set new score
            strncpy(top_scores[i].nickname, nickname, sizeof(top_scores[i].nickname) - 1);
            top_scores[i].nickname[sizeof(top_scores[i].nickname) - 1] = '\0';
            top_scores[i].score = score;

            return; 
        }
    }
}




const ScoreEntry* get_top_scores(void) {
    return top_scores;
}
