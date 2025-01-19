#include "flash.h"
#include "MKL05Z4.h"
#include <stdio.h>

// Oczekiwane kody statusu
#define FLASH_CMD_SUCCESS 0x80
#define FLASH_CMD_ACCERR  0x20
#define FLASH_CMD_FPVIOL  0x10
#define FLASH_CMD_MGSTAT0 0x01

// Rozmiar sektora pamiêci Flash
#define FLASH_SECTOR_SIZE 1024

// Funkcja czekaj¹ca na zakoñczenie operacji Flash
static void wait_for_flash(void) {
    while (!(FTFA->FSTAT & FLASH_CMD_SUCCESS)) {
        // Czekaj na zakoñczenie operacji
    }
}

// Funkcja czyszcz¹ca flagi b³êdów
static void clear_flash_errors(void) {
    FTFA->FSTAT = FLASH_CMD_ACCERR | FLASH_CMD_FPVIOL | FLASH_CMD_MGSTAT0;
}

// Funkcja do wymazywania sektora Flash
bool Flash_EraseSector(uint32_t address) {
    printf("Erasing Flash Sector: Address = 0x%08X\n", address);

    // Sprawdzenie wyrównania adresu do granicy sektora
    if (address % FLASH_SECTOR_SIZE != 0) {
        printf("Error: Address not aligned to sector boundary.\n");
        return false;
    }

    clear_flash_errors();

    // Ustawienie komendy wymazywania sektora
    FTFA->FCCOB0 = 0x09;
    FTFA->FCCOB1 = (address >> 16) & 0xFF;
    FTFA->FCCOB2 = (address >> 8) & 0xFF;
    FTFA->FCCOB3 = address & 0xFF;

    // Rozpoczêcie operacji
    FTFA->FSTAT = FLASH_CMD_SUCCESS;
    wait_for_flash();

    // Sprawdzenie b³êdów
    if (FTFA->FSTAT & (FLASH_CMD_ACCERR | FLASH_CMD_FPVIOL | FLASH_CMD_MGSTAT0)) {
        printf("Error: Flash erase failed (FSTAT=0x%02X).\n", FTFA->FSTAT);
        return false;
    }

    printf("Flash sector erased successfully.\n");
    return true;
}

// Funkcja do zapisu danych do Flash
bool Flash_Write(uint32_t address, const uint8_t* data, uint32_t size) {
    printf("Writing to Flash: Address = 0x%08X, Size = %d\n", address, size);

    // Sprawdzenie poprawnoœci rozmiaru danych
    if (size % 4 != 0) {
        printf("Error: Data size must be a multiple of 4.\n");
        return false;
    }

    clear_flash_errors();

    for (uint32_t i = 0; i < size; i += 4) {
        // Ustawienie komendy zapisu s³owa
        FTFA->FCCOB0 = 0x07;
        FTFA->FCCOB1 = (address >> 16) & 0xFF;
        FTFA->FCCOB2 = (address >> 8) & 0xFF;
        FTFA->FCCOB3 = address & 0xFF;
        FTFA->FCCOB4 = data[i];
        FTFA->FCCOB5 = data[i + 1];
        FTFA->FCCOB6 = data[i + 2];
        FTFA->FCCOB7 = data[i + 3];

        // Rozpoczêcie operacji
        FTFA->FSTAT = FLASH_CMD_SUCCESS;
        wait_for_flash();

        // Sprawdzenie b³êdów
        if (FTFA->FSTAT & (FLASH_CMD_ACCERR | FLASH_CMD_FPVIOL | FLASH_CMD_MGSTAT0)) {
            printf("Error: Flash write failed (FSTAT=0x%02X).\n", FTFA->FSTAT);
            return false;
        }

        printf("Written word at 0x%08X: 0x%02X%02X%02X%02X\n",
               address, data[i], data[i + 1], data[i + 2], data[i + 3]);

        address += 4; // Przesuniêcie do kolejnego adresu
    }

    printf("Flash write completed successfully.\n");
    return true;
}

// Funkcja do odczytu danych z Flash
bool Flash_Read(uint32_t address, uint8_t* buffer, uint32_t size) {
    printf("Reading from Flash: Address = 0x%08X, Size = %d\n", address, size);

    for (uint32_t i = 0; i < size; i++) {
        buffer[i] = *((volatile uint8_t*)(address + i));
    }

    printf("Read completed: ");
    for (uint32_t i = 0; i < size; i++) {
        printf("0x%02X ", buffer[i]);
    }
    printf("\n");

    return true;
}

// Funkcja sprawdzaj¹ca, czy sektor Flash jest wymazany
bool Flash_IsErased(uint32_t address, uint32_t size) {
    printf("Checking if Flash sector is erased: Address = 0x%08X, Size = %d\n", address, size);

    for (uint32_t i = 0; i < size; i += 4) {
        uint32_t value = *((volatile uint32_t*)(address + i));
        if (value != 0xFFFFFFFF) {
            printf("Flash not erased at 0x%08X: 0x%08X\n", address + i, value);
            return false;
        }
    }

    printf("Flash sector is erased.\n");
    return true;
}
