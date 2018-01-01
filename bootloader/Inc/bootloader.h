
#include "stdint.h"

#ifndef __BOOTLOADER_H
#define __BOOTLOADER_H

#define USE_CHECKSUM            0       /* Check application checksum on startup */
#define USE_WRITE_PROTECTION    0       /* Enable write protection after performing in-app-programming */
#define SET_VECTOR_TABLE        1       /* Automatically set vector table location before launching application */
#define CLEAR_RESET_FLAGS       1       /* If enabled: bootloader clears reset flags. (This occurs only when OBL RST flag is active.)
                                           If disabled: bootloader does not clear reset flags, not even when OBL RST is active. */

#define APP_ADDRESS     (uint32_t)0x08008000    /* Start address of application space in flash */
#define END_ADDRESS     (uint32_t)0x080FFFFB    /* End address of application space (addr. of last byte) */
#define CRC_ADDRESS     (uint32_t)0x080FFFFC    /* Start address of application checksum in flash */
#define SYSMEM_ADDRESS  (uint32_t)0x1FFF0000    /* Address of System Memory (ST Bootloader) */
#define FLASH_SIZE      (uint32_t)0x08010000

#if (STM32L496xx)
#define RAM_SIZE        (uint32_t)0x00040000
#elif (STM32L476xx)
#define RAM_SIZE        (uint32_t)0x00018000
#endif

#define FLASH_PAGE_NBPERBANK    256            
#define APP_SIZE        (uint32_t)(((END_ADDRESS - APP_ADDRESS) + 3) / 4) /* Size of application in DWORD (32bits or 4bytes) */

enum
{
    BL_OK = 0,
    BL_NO_APP,
    BL_SIZE_ERROR,
    BL_CHKS_ERROR,
    BL_ERASE_ERROR,
    BL_WRITE_ERROR,
    BL_OBP_ERROR
};

enum
{
    BL_PROTECTION_NONE  = 0,
    BL_PROTECTION_WRP   = 0x1,
    BL_PROTECTION_RDP   = 0x2,
    BL_PROTECTION_PCROP = 0x4,
};

void    Bootloader_Init(void);
uint8_t Bootloader_Erase(void);

void     Bootloader_FlashBegin(void);
uint16_t Bootloader_FlashNext(uint32_t address, uint16_t data);
void     Bootloader_FlashEnd(void);

uint8_t Bootloader_GetProtectionStatus(void); 
uint8_t Bootloader_ConfigProtection(uint32_t protection);

uint8_t Bootloader_CheckSize(uint32_t appsize);
uint8_t Bootloader_VerifyChecksum(void);
uint8_t Bootloader_CheckForApplication(void);
void    Bootloader_JumpToApplication(uint32_t address);
void    Bootloader_JumpToSysMem(void);

#endif /* __BOOTLOADER_H */