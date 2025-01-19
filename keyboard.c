#include "keyboard.h"
#include "MKL05Z4.h"

// Definicje kolumn (C2–C4)
#define C2_MASK (1 << 10)  // PTA10
#define C3_MASK (1 << 11)  // PTA11
#define C4_MASK (1 << 12)  // PTA12

// Definicje wierszy (R1–R4)
#define R1_PIN (3)   // PTB3
#define R2_PIN (4)   // PTB4
#define R3_PIN (10)  // PTB10
#define R4_PIN (11)  // PTB11

// Mapa klawiatury
const char* key_map[4][3] = {
    {"1", "2", "3"},
    {"4", "5", "6"},
    {"7", "8", "9"},
    {"*", "0", "#"}
};

// Funkcja inicjalizuj¹ca GPIO dla klawiatury
void Keyboard_Init(void) {
    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK; // W³¹czenie zegara dla portów A i B

    // Kolumny (C2–C4) jako wejœcia z pull-up
    PORTA->PCR[10] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; // C2 › PTA10
    PORTA->PCR[11] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; // C3 › PTA11
    PORTA->PCR[12] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; // C4 › PTA12

    // Wiersze (R1–R4) jako wyjœcia
    PORTB->PCR[R1_PIN] = PORT_PCR_MUX(1); // R1 › PTB3
    PORTB->PCR[R2_PIN] = PORT_PCR_MUX(1); // R2 › PTB4
    PORTB->PCR[R3_PIN] = PORT_PCR_MUX(1); // R3 › PTB10
    PORTB->PCR[R4_PIN] = PORT_PCR_MUX(1); // R4 › PTB11

    PTB->PDDR |= (1 << R1_PIN) | (1 << R2_PIN) | (1 << R3_PIN) | (1 << R4_PIN); // R1–R4 jako wyjœcia
    PTB->PDOR |= (1 << R1_PIN) | (1 << R2_PIN) | (1 << R3_PIN) | (1 << R4_PIN); // Wy³¹cz wszystkie wiersze (stan wysoki)
}

// Funkcja odczytuj¹ca klawisze
uint8_t Keyboard_ReadKey(void) {
    uint8_t row_pins[] = {R4_PIN, R3_PIN, R2_PIN, R1_PIN}; // Kolejnoœæ od do³u do góry

    for (uint8_t row = 0; row < 4; row++) {
        PTB->PDOR |= (1 << R1_PIN) | (1 << R2_PIN) | (1 << R3_PIN) | (1 << R4_PIN); // Wy³¹cz wszystkie wiersze
        PTB->PDOR &= ~(1 << row_pins[row]); // Ustaw niski stan na wybranym wierszu

        if (!(PTA->PDIR & C2_MASK)) return row * 3 + 0; // C2 wciœniête
        if (!(PTA->PDIR & C3_MASK)) return row * 3 + 1; // C3 wciœniête
        if (!(PTA->PDIR & C4_MASK)) return row * 3 + 2; // C4 wciœniête
    }

    return 0xFF; // ¯aden klawisz nie wciœniêty
}
