#include "game.h"
#include "oled.h"
#include "game_draw.h"
#include "arkanoid.h"
#include "maps.h"
#include "tsi.h"
#include "spi.h"
#include "scores.h"

void start_game(const char* nickname) {
		//Inits
    game_init();
    Paddle paddle = { (SCREEN_WIDTH - PADDLE_WIDTH) / 2, SCREEN_HEIGHT - PADDLE_HEIGHT - 5 };
    Ball ball = { (SCREEN_WIDTH / 2) - BALL_SIZE, SCREEN_HEIGHT - PADDLE_HEIGHT - BALL_SIZE - 5, 1, -1 };

    draw_game(&paddle, &ball);

    while (1) {
        // Get touchpad
        uint8_t touch_pos = TSI_ReadSlider();

        if (touch_pos != 0) {
            paddle_update(&paddle, touch_pos);
        }

        ball_update(&ball, &paddle);

        if (check_map_complete()) {
            load_next_map();
        }

        if (ball.y > SCREEN_HEIGHT) {
            lives--; //game over  
            if (lives <= 0) {
                update_top_scores(nickname, get_score());
                game_over_display();
                break;
            }
            reset_ball(&ball, &paddle);
        }

        draw_game(&paddle, &ball);
        for (volatile int i = 0; i < game_speed * 1000; i++); //DELAY for diffrent game speed
    }
}
