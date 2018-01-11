#include "stdint.h"

#ifndef __BOOTLOADER_H
#define __BOOTLOADER_H

void    Bootloader_start(void);
uint8_t Bootloader_write(uint32_t address, uint8_t *data, uint8_t datalength);
void Bootloader_erase(void);

#endif /* __BOOTLOADER_H */
