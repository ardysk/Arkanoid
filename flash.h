#ifndef FLASH_H
#define FLASH_H

#include <stdint.h>
#include <stdbool.h>

// Prototypy funkcji
bool Flash_EraseSector(uint32_t address);
bool Flash_Write(uint32_t address, const uint8_t* data, uint32_t size);
bool Flash_Read(uint32_t address, uint8_t* buffer, uint32_t size);
bool Flash_IsErased(uint32_t address, uint32_t size);

#endif // FLASH_H
