#include "menu.h"
#include "oled.h"
#include "spi.h"
#include "Fonts.h"
#include "keyboard.h"
#include "scores.h"
#include "tsi.h"
#include <stdio.h>
#include <string.h>

//Menu options
const char* menu_options[] = {"Start", "Score Board", "Options", "Nickname"};
#define MENU_OPTIONS_COUNT 4 // Liczba opcji menu

//Submenu "OLED Options" options
const char* oled_options[] = {"Brigh", "Refresh R", "Mode", "Back"};
#define OLED_OPTIONS_COUNT 4 // Liczba opcji OLED

volatile uint32_t czas = 0;      // Timer in ms
volatile uint8_t sekunda = 0;    // Licznik przerwañ (do 10)
volatile uint8_t sekunda_OK = 0; // "1" oznacza, ¿e minê³a sekunda

char user_nickname[6] = "GUEST"; // Domyœlny nick u¿ytkownika

// Funkcja SysTick Handler
void SysTick_Handler(void) {
    czas++;
    sekunda++;
    if (sekunda >= 10) { // Co 10 przerwañ (1s)
        sekunda = 0;
        sekunda_OK = 1;
    }
}

// Zwraca aktualny czas w ms
uint32_t millis(void) {
    return czas;
}

// Funkcja konfiguracji SysTick
void setup_systick(void) {
    SysTick_Config(SystemCoreClock / 1000); // Przerwanie co 1 ms
}

// Funkcja oczekuj¹ca na zwolnienie klawisza
void wait_for_key_release(void) {
    while (Keyboard_ReadKey() != 0xFF); // Czekaj, a¿ ¿aden klawisz nie bêdzie wciœniêty
}

// Funkcja realizuj¹ca debouncing
void debounce_delay(void) {
    for (volatile uint32_t i = 0; i < 10000; i++); // Proste opóŸnienie
}

// Funkcja do wyœwietlania najlepszych wyników
void show_score_board(void) {
    ssd1306_clear_screen(0x00);
    ssd1306_display_string(25, 0, (const uint8_t*)"Top Scores:", 12, 1);

    const ScoreEntry* scores = get_top_scores();
    uint8_t row = 0;

    for (int i = 0; i < MAX_TOP_SCORES && scores[i].score > 0; i++) { // Wyœwietl tylko wyniki wiêksze od 0
        row++;
        ssd1306_display_string(15, 16 * row, (const uint8_t*)scores[i].nickname, 12, 1); // Wyœwietl nick
        draw_number(80, 16 * row, scores[i].score); // Wyœwietl wynik
    }

    if (row == 0) {
        ssd1306_display_string(25, 16, (const uint8_t*)"No Scores Yet", 12, 1);
    }

    ssd1306_refresh_gram();

    while (1) {
        uint8_t key = Keyboard_ReadKey();
        if (key != 0xFF && key_map[key / 3][key % 3][0] == '1') { // Wyjœcie na `1`
            wait_for_key_release();
            break;
        }
        debounce_delay();
    }
}



// Funkcja do ustawiania nicku
void enter_username(void) {
    uint8_t current_position = 0;
    uint8_t last_key = 0xFF;
    uint8_t current_char_index = 0;

    ssd1306_clear_screen(0x00);

    while (1) {
        uint8_t key = Keyboard_ReadKey();

        if (key != 0xFF && key != last_key) {
            last_key = key;

            switch (key) {
                case 1: // S3: PrzejdŸ do kolejnej pozycji
                    if (current_position < 5) {
                        current_position++;
                        user_nickname[current_position] = '_';
                    }
                    break;

                case 2: // S4: Usuñ znak
                    if (current_position > 0) {
                        user_nickname[--current_position] = '\0';
                    }
                    break;

                case 3: // S6: Litery A, B, C, D
                    current_char_index = (current_char_index + 1) % 4;
                    user_nickname[current_position] = 'A' + current_char_index;
                    break;

                case 4: // S7: Litery E, F, G, H
                    current_char_index = (current_char_index + 1) % 4;
                    user_nickname[current_position] = 'E' + current_char_index;
                    break;

                case 5: // S8: Litery I, J, K, L
                    current_char_index = (current_char_index + 1) % 4;
                    user_nickname[current_position] = 'I' + current_char_index;
                    break;

                case 6: // S10: Litery M, N, O, P
                    current_char_index = (current_char_index + 1) % 4;
                    user_nickname[current_position] = 'M' + current_char_index;
                    break;

                case 7: // S11: Litery Q, R, S, T
                    current_char_index = (current_char_index + 1) % 4;
                    user_nickname[current_position] = 'Q' + current_char_index;
                    break;
							  
								case 8: // S12: Litery U, V, W
                    current_char_index = (current_char_index + 1) % 3;
                    user_nickname[current_position] = 'U' + current_char_index;
                    break;

                case 9: // S14: Litery X, Y, Z
                    current_char_index = (current_char_index + 1) % 3;
                    user_nickname[current_position] = 'X' + current_char_index;
                    break;

                case 10: // S15: Liczby 0,1,2,3,4,
                    current_char_index = (current_char_index + 1) % 5;
                    user_nickname[current_position] = '1' + current_char_index;
                    break;

                case 11: // S16: Litery 5,6,7,8,9
                    current_char_index = (current_char_index + 1) % 5;
                    user_nickname[current_position] = '5' + current_char_index;
                    break;

                case 0: // S2: Zapisz i wyjdŸ do menu
                    user_nickname[current_position] = '\0';
                    return;
            }

            ssd1306_clear_screen(0x00);
            ssd1306_display_string(20, 0, (const uint8_t*)"Set Nickname:", 12, 1);
            ssd1306_display_string(20, 16, (const uint8_t*)user_nickname, 12, 1);
            ssd1306_refresh_gram();
        }

        if (key == 0xFF) {
            last_key = 0xFF;
        }

        debounce_delay();
    }
}

// Funkcja do ustawiania opcji OLED
void show_oled_options(void) {
    uint8_t selected_option = 0;
    uint8_t brightness = 0x80; 
    uint8_t refresh_rate = 0x80; 
    uint8_t day_mode = 1;

    char display_value[16]; 

    while (1) {
    ssd1306_clear_screen(0x00);

    for (uint8_t i = 0; i < OLED_OPTIONS_COUNT; i++) {
        ssd1306_display_string(20, i * 16, (const uint8_t*)oled_options[i], 12, 1);
    }

    switch (selected_option) {
        case 0: {
            // Wyœwietlanie jasnoœci w procentach za pomoc¹ `display_digit`
            uint8_t brightness_percentage = (brightness * 100) / 255;
            draw_digit(90, 3, brightness_percentage / 10); // Dziesi¹tki
            draw_digit(96, 3, brightness_percentage % 10); // Jednoœci
            ssd1306_display_string(108, 0, (const uint8_t*)"%", 12, 1); // Procent
            break;
        }
        case 1: {
            // Wyœwietlanie poziomu odœwie¿ania za pomoc¹ `display_digit`
            uint8_t refresh_level = refresh_rate / 64;
            ssd1306_display_string(90, 16, (const uint8_t*)"Lvl", 12, 1);
            draw_digit(114, 19, refresh_level); // Wyœwietl poziom
            break;
        }
        case 2: {
            // Wyœwietlanie trybu dnia/nocy
            const char* mode_text = day_mode ? "Day" : "Night";
            ssd1306_display_string(90, 32, (const uint8_t*)mode_text, 12, 1);
            break;
        }
    }

    draw_bitmap(0, selected_option * 16, block_bitmap_arrow, 8, 8);
    ssd1306_refresh_gram();

        uint8_t key = Keyboard_ReadKey();
        if (key != 0xFF) {
            debounce_delay();
            switch (key_map[key / 3][key % 3][0]) {
                case '1': 
                    selected_option = (selected_option + 1) % OLED_OPTIONS_COUNT;
                    wait_for_key_release();
                    break;
                case '2': 
                    wait_for_key_release();
                    switch (selected_option) {
                        case 0:
                            brightness += 0x20;
                            if (brightness == 0) brightness = 0xFF;
                            ssd1306_write_byte(0x81, 0);
                            ssd1306_write_byte(brightness, 0);
                            break;
                        case 1:
                            refresh_rate += 0x10;
                            if (refresh_rate == 0x40) refresh_rate = 0x80;
                            ssd1306_set_framerate(refresh_rate);
                            break;
                        case 2:
                            day_mode = !day_mode;
                            ssd1306_write_byte(day_mode ? 0xA6 : 0xA7, 0);
                            break;
                        case 3:
                            return;
                    }
                    break;
            }
        }
    }
}

// Wyœwietlanie g³ównego menu
void show_menu(void) {
    setup_systick();
    spi_init(SPI_MODE_0, 1000000, SPI_SIDE_MASTER);
    ssd1306_init();
    ssd1306_clear_screen(0x00);
    Keyboard_Init();
		TSI_Init();
    uint8_t selected_option = 0;

    while (1) {
        ssd1306_clear_screen(0x00);

        for (uint8_t i = 0; i < MENU_OPTIONS_COUNT; i++) {
            ssd1306_display_string(20, i * 16, (const uint8_t*)menu_options[i], 12, 1);
        }

        draw_bitmap(0, selected_option * 16, block_bitmap_arrow, 8, 8);
        ssd1306_refresh_gram();

        uint8_t key = Keyboard_ReadKey();
        if (key != 0xFF) {
            debounce_delay();
            switch (key_map[key / 3][key % 3][0]) {
                case '1': 
                    selected_option = (selected_option + 1) % MENU_OPTIONS_COUNT;
                    wait_for_key_release();
                    break;
                case '2': 
                    wait_for_key_release();
                    switch (selected_option) {
                        case 0:
														start_game(user_nickname);
                            break;
                        case 1:
                            show_score_board();
                            break;
                        case 2:
                            show_oled_options();
                            break;
                        case 3:
                            enter_username();
                            break;
                    }
                    break;
            }
        }
    }
}