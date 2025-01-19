#include "oled.h"
#include "spi.h"
#include "gpio.h"
#include "Fonts.h"
#include "MKL05Z4.h"

//PINS
#define OLED_CS_PIN   5   // PTA5
#define OLED_DC_PIN   7   // PTB7
#define OLED_RES_PIN  6   // PTB6

#define SSD1306_CMD    0
#define SSD1306_DAT    1

/**
 * @brief Screen buffer
 */
static uint8_t s_chDispalyBuffer[SSD1306_WIDTH][8];

/**
 * @brief Wyœwietla wiadomoœæ startow¹ na ekranie OLED.
 * 
 * Wyœwietla du¿y napis "OLED" na œrodku ekranu, a poni¿ej mniejszy napis "LIB by ardys".
 * Po 5 sekundach ekran zostaje wyczyszczony.
 */
 
void ssd1306_display_startup_message(void) {
    // Wyczyszczenie ekranu
    ssd1306_clear_screen(0x00);

    // Wyœwietlenie du¿ego napisu "OLED"
    uint8_t x_pos = (SSD1306_WIDTH - 64) / 2; // Wyœrodkowanie 64 pikseli
    uint8_t y_pos = 0; // Góra ekranu
    const char *oled_text = "OLED";
    for (int i = 0; i < 4; i++) {
        ssd1306_display_char(x_pos, y_pos, oled_text[i], 12, 1); // U¿ycie du¿ej czcionki
        x_pos += 16; // Przesuniêcie pozycji poziomej
    }

    // Wyœwietlenie mniejszego napisu "LIB by ardys"
    x_pos = (SSD1306_WIDTH - 72) / 2; // Wyœrodkowanie
    y_pos = 32; // Dolna czêœæ ekranu
    ssd1306_display_string(x_pos, y_pos, "LIB by ardys", 12, 1);

    // Odœwie¿enie ekranu
    ssd1306_refresh_gram();

    // Odczekanie 5 sekund
    for (volatile uint32_t delay = 0; delay < 10000000; delay++);

    // Wyczyszczenie ekranu
    ssd1306_clear_screen(0x00);
    ssd1306_refresh_gram(); // Odœwie¿enie po wyczyszczeniu
}

/**
 * @brief Wysy³a pojedynczy bajt do wyœwietlacza OLED.
 * 
 * @param chData Dane do wys³ania.
 * @param chCmd Typ danych: SSD1306_CMD (komenda) lub SSD1306_DAT (dane).
 */
void ssd1306_write_byte(uint8_t chData, uint8_t chCmd) {
    if (chCmd == SSD1306_CMD) {
        gpio_set_low(GPIOB, OLED_DC_PIN); // DC = 0, wysy³anie komendy
    } else {
        gpio_set_high(GPIOB, OLED_DC_PIN); // DC = 1, wysy³anie danych
    }

    gpio_set_low(GPIOA, OLED_CS_PIN); // CS = 0, wybierz urz¹dzenie
    spi_master_write(chData);        // Wysy³anie bajtu
    gpio_set_high(GPIOA, OLED_CS_PIN); // CS = 1, odznacz urz¹dzenie
}

/**
 * @brief W³¹cza wyœwietlacz OLED.
 */
void ssd1306_display_on(void) {
    ssd1306_write_byte(0x8D, SSD1306_CMD);
    ssd1306_write_byte(0x14, SSD1306_CMD);
    ssd1306_write_byte(0xAF, SSD1306_CMD);
}

/**
 * @brief Wy³¹cza wyœwietlacz OLED.
 */
void ssd1306_display_off(void) {
    ssd1306_write_byte(0x8D, SSD1306_CMD);
    ssd1306_write_byte(0x10, SSD1306_CMD);
    ssd1306_write_byte(0xAE, SSD1306_CMD);
}


/**
 * @brief Odœwie¿a pamiêæ GRAM wyœwietlacza OLED.
 * 
 * Dane z bufora `s_chDispalyBuffer` s¹ przesy³ane do wyœwietlacza.
 */
void ssd1306_refresh_gram(void) {
    for (uint8_t i = 0; i < 8; i++) {
        ssd1306_write_byte(0xB0 + i, SSD1306_CMD);
        ssd1306_write_byte(0x00, SSD1306_CMD);
        ssd1306_write_byte(0x10, SSD1306_CMD);
        for (uint8_t j = 0; j < SSD1306_WIDTH+2; j++) {
            ssd1306_write_byte(s_chDispalyBuffer[j][i], SSD1306_DAT);
        }
    }
}

/**
 * @brief Czyœci ekran OLED.
 * 
 * @param chFill Wartoœæ wype³nienia: 0x00 (czarny) lub 0xFF (bia³y).
 */
void ssd1306_clear_screen(uint8_t chFill) {
    for (uint8_t i = 0; i < 8; i++) {
        for (uint8_t j = 0; j < SSD1306_WIDTH+2; j++) {
            s_chDispalyBuffer[j][i] = chFill;
        }
    }
}


/**
 * @brief Rysuje pojedynczy punkt na ekranie.
 * 
 * @param chXpos Pozycja X punktu.
 * @param chYpos Pozycja Y punktu.
 * @param chPoint Stan punktu: 1 (w³¹czony) lub 0 (wy³¹czony).
 */
void ssd1306_draw_point(uint8_t chXpos, uint8_t chYpos, uint8_t chPoint) {
    if (chXpos >= SSD1306_WIDTH || chYpos >= SSD1306_HEIGHT) return;

    uint8_t page = chYpos / 8;
    uint8_t bit_pos = chYpos % 8;

    if (chPoint) {
        s_chDispalyBuffer[chXpos][page] |= (1 << bit_pos);
    } else {
        s_chDispalyBuffer[chXpos][page] &= ~(1 << bit_pos);
    }
}

/**
 * @brief Wyœwietla pojedynczy znak na ekranie.
 * 
 * @param chXpos Pozycja X znaku.
 * @param chYpos Pozycja Y znaku.
 * @param chChr Znak do wyœwietlenia.
 * @param chSize Rozmiar czcionki.
 * @param chMode Tryb wyœwietlania: 1 (normalny), 0 (odwrócony).
 */
void ssd1306_display_char(uint8_t chXpos, uint8_t chYpos, uint8_t chChr, uint8_t chSize, uint8_t chMode) {
    uint8_t i, j;
    uint8_t chTemp, chYpos0 = chYpos;

    chChr -= ' ';
    for (i = 0; i < chSize; i++) {
        chTemp = c_chFont1206[chChr][i];
        for (j = 0; j < 8; j++) {
            if (chTemp & 0x80) {
                ssd1306_draw_point(chXpos, chYpos, chMode);
            } else {
                ssd1306_draw_point(chXpos, chYpos, !chMode);
            }
            chTemp <<= 1;
            chYpos++;
            if ((chYpos - chYpos0) == chSize) {
                chYpos = chYpos0;
                chXpos++;
                break;
            }
        }
    }
}

/**
 * @brief Wyœwietla ci¹g znaków na ekranie.
 * 
 * @param chXpos Pocz¹tkowa pozycja X.
 * @param chYpos Pocz¹tkowa pozycja Y.
 * @param pchString WskaŸnik na ci¹g znaków do wyœwietlenia.
 * @param chSize Rozmiar czcionki.
 * @param chMode Tryb wyœwietlania: 1 (normalny), 0 (odwrócony).
 */
void ssd1306_display_string(uint8_t chXpos, uint8_t chYpos, const uint8_t *pchString, uint8_t chSize, uint8_t chMode) {
    while (*pchString != '\0') {
        if (chXpos > (SSD1306_WIDTH - chSize / 2)) {
            chXpos = 0;
            chYpos += chSize;
            if (chYpos > (SSD1306_HEIGHT - chSize)) {
                chYpos = chXpos = 0;
                ssd1306_clear_screen(0x00);
            }
        }
        ssd1306_display_char(chXpos, chYpos, *pchString, chSize, chMode);
        chXpos += chSize / 2;
        pchString++;
    }
}

void ssd1306_draw_string_custom(uint8_t x, uint8_t y, const char* str, const uint8_t font[][12], uint8_t font_width, uint8_t font_height) {
    while (*str) {
        if (x + font_width > SCREEN_WIDTH) {
            // Nowa linia, jeœli wychodzimy poza szerokoœæ ekranu
            x = 0;
            y += font_height;
            if (y + font_height > SCREEN_HEIGHT) {
                // Jeœli wyjdziemy poza ekran, zakoñcz rysowanie
                break;
            }
        }
        draw_bitmap(x, y, font[*str - 32], font_width, font_height);
        x += font_width; // Przesuñ w poziomie o szerokoœæ czcionki
        str++;
    }
}


/**
 * @brief Inicjalizacja wyœwietlacza
 */
void ssd1306_init(void) {
    // Konfiguracja pinów i inicjalizacja
    gpio_set_output(PORTA, GPIOA, OLED_CS_PIN);
    gpio_set_output(PORTB, GPIOB, OLED_DC_PIN);
    gpio_set_output(PORTB, GPIOB, OLED_RES_PIN);

    gpio_set_low(GPIOB, OLED_RES_PIN);
    for (volatile int i = 0; i < 10000; i++);
    gpio_set_high(GPIOB, OLED_RES_PIN);

    // Podstawowe ustawienia
    ssd1306_write_byte(0xAE, SSD1306_CMD);
    ssd1306_write_byte(0x20, SSD1306_CMD);
    ssd1306_write_byte(0x10, SSD1306_CMD);
    ssd1306_write_byte(0xB0, SSD1306_CMD);
    ssd1306_write_byte(0xC8, SSD1306_CMD);
    ssd1306_write_byte(0x00, SSD1306_CMD);
    ssd1306_write_byte(0x10, SSD1306_CMD);
    ssd1306_write_byte(0x40, SSD1306_CMD);
    ssd1306_write_byte(0x81, SSD1306_CMD);
    ssd1306_write_byte(0xFF, SSD1306_CMD);
    ssd1306_write_byte(0xA1, SSD1306_CMD);
    ssd1306_write_byte(0xA6, SSD1306_CMD);
    ssd1306_write_byte(0xA8, SSD1306_CMD);
    ssd1306_write_byte(0x3F, SSD1306_CMD);
    ssd1306_write_byte(0xD3, SSD1306_CMD);
    ssd1306_write_byte(0x00, SSD1306_CMD);
    ssd1306_write_byte(0xD5, SSD1306_CMD);
    ssd1306_write_byte(0x80, SSD1306_CMD);
    ssd1306_write_byte(0xD9, SSD1306_CMD);
    ssd1306_write_byte(0xF1, SSD1306_CMD);
    ssd1306_write_byte(0xDA, SSD1306_CMD);
    ssd1306_write_byte(0x12, SSD1306_CMD);
    ssd1306_write_byte(0xDB, SSD1306_CMD);
    ssd1306_write_byte(0x40, SSD1306_CMD);
    ssd1306_write_byte(0x8D, SSD1306_CMD);
    ssd1306_write_byte(0x14, SSD1306_CMD);
    ssd1306_write_byte(0xAF, SSD1306_CMD);

    // Wyœwietlenie napisu startowego
    ssd1306_display_startup_message();

    // Wyczyszczenie ekranu
    ssd1306_clear_screen(0x00);
}


/**
 * @brief Ustawia czêstotliwoœæ odœwie¿ania wyœwietlacza
 * @param value Wartoœæ czêstotliwoœci (domyœlna: 0x80)
 */
void ssd1306_set_framerate(uint8_t value) {
    ssd1306_write_byte(0xD5, SSD1306_CMD); // Ustawienie zegara
    ssd1306_write_byte(value, SSD1306_CMD); // Czêstotliwoœæ (0x00 - minimalna, 0xFF - maksymalna)
}
/**
 * @brief Ustawia orientacjê wyœwietlania
 * @param rotate 0 - normalna orientacja, 1 - odwrócona orientacja (Wyœwietla czionki od do³u i do góry nogami)
 */
void ssd1306_set_orientation(uint8_t rotate) {
    if (rotate) {
        ssd1306_write_byte(0xA0, SSD1306_CMD); // Odwróæ orientacjê poziom¹
        ssd1306_write_byte(0xC0, SSD1306_CMD); // Odwróæ orientacjê pionow¹
    } else {
        ssd1306_write_byte(0xA1, SSD1306_CMD); // Normalna orientacja pozioma
        ssd1306_write_byte(0xC8, SSD1306_CMD); // Normalna orientacja pionowa
    }
}

/**
 * @brief Ustawia tryb adresowania wyœwietlacza
 * @param mode 0x00 - poziomy, 0x01 - pionowy, 0x02 - tryb stron
 */
void ssd1306_set_addressing_mode(uint8_t mode) {
    ssd1306_write_byte(0x20, SSD1306_CMD); // Ustawienie trybu adresowania
    ssd1306_write_byte(mode, SSD1306_CMD); // Tryb: 0x00, 0x01 lub 0x02
}

void draw_bitmap(uint8_t x, uint8_t y, const uint8_t *bitmap, uint8_t width, uint8_t height) {
    for (uint8_t i = 0; i < height; i++) {
        for (uint8_t j = 0; j < width; j++) {
            if (bitmap[i] & (1 << (7 - j % 8))) { // Sprawdzanie bitów w bajcie
                ssd1306_draw_point(x + j, y + i, 1);
            }
        }
    }
}
// Funkcja czyszcz¹ca pojedynczy punkt na ekranie
void clear_bitmap(uint8_t x, uint8_t y) {
    ssd1306_draw_point(x, y, 0);  // 0 oznacza wy³¹czenie punktu (czyszczenie)
}

/**
 * @brief Zwraca stan piksela na ekranie OLED.
 * 
 * @param x Pozycja X piksela.
 * @param y Pozycja Y piksela.
 * @return Stan piksela (1 - w³¹czony, 0 - wy³¹czony).
 */
uint8_t ssd1306_get_pixel(uint8_t x, uint8_t y) {
    if (x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT) return 0; // Poza zakresem
    uint8_t page = y / 8;  // Okreœla stronê (okno 8-pikselowe)
    uint8_t bit_pos = y % 8;  // Okreœla pozycjê bitu w obrêbie strony

    return (s_chDispalyBuffer[x][page] >> bit_pos) & 0x01;  // Zwraca stan piksela
}
/**
 * @brief Ustawia stan piksela na ekranie OLED.
 * 
 * @param x Pozycja X piksela.
 * @param y Pozycja Y piksela.
 * @param state Stan piksela (1 - w³¹czony, 0 - wy³¹czony).
 */
void ssd1306_set_pixel(uint8_t x, uint8_t y, uint8_t state) {
    if (x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT) return;  // Poza zakresem

    uint8_t page = y / 8;  // Okreœla stronê
    uint8_t bit_pos = y % 8;  // Okreœla pozycjê bitu w obrêbie strony

    if (state) {
        s_chDispalyBuffer[x][page] |= (1 << bit_pos);  // Ustawienie bitu
    } else {
        s_chDispalyBuffer[x][page] &= ~(1 << bit_pos);  // Wyczyszczenie bitu
    }

    ssd1306_refresh_gram();  // Odœwie¿enie ekranu
}
void draw_digit(uint8_t x, uint8_t y, uint8_t digit) {
    if (digit < 10) {
        draw_bitmap(x, y, font_digits[digit], 8, 8);
    }
}

void draw_number(uint8_t x, uint8_t y, int score) {
    uint8_t hundreds = (score / 100) % 10; // Oblicz setki
    uint8_t tens = (score / 10) % 10;     // Oblicz dziesi¹tki
    uint8_t ones = score % 10;            // Oblicz jednoœci

    // Wyœwietl setki, dziesi¹tki i jednoœci obok siebie
    draw_digit(x, y, hundreds);      // Setki
    draw_digit(x + 8, y, tens);      // Dziesi¹tki (przesuniête o 8 pikseli w prawo)
    draw_digit(x + 16, y, ones);     // Jednoœci (przesuniête o 16 pikseli w prawo)
}






