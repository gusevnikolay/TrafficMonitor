#include "stm32f1xx_hal.h"
#include "bootloader.h"

typedef void (*pFunction)(void);

static uint32_t flash_ptr = APP_ADDRESS;

void Bootloader_Init(void)
{
    HAL_FLASH_Unlock();
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR | FLASH_FLAG_OPTVERR);
    HAL_FLASH_Lock();
}

uint8_t Bootloader_Erase(void)
{
    uint32_t NbrOfPages = 0;
    uint32_t PageError = 0;
    FLASH_EraseInitTypeDef pEraseInit;
    HAL_StatusTypeDef status = HAL_OK;
    HAL_FLASH_Unlock();
    NbrOfPages = (FLASH_BASE + 0x08010000 - APP_ADDRESS) / FLASH_PAGE_SIZE;

    if(NbrOfPages > FLASH_PAGE_NBPERBANK)
    {
        pEraseInit.Banks     = FLASH_BANK_1;
        pEraseInit.NbPages   = NbrOfPages % FLASH_PAGE_NBPERBANK;
        pEraseInit.NbPages   = FLASH_PAGE_NBPERBANK - pEraseInit.NbPages;
        pEraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
        status               = HAL_FLASHEx_Erase(&pEraseInit, &PageError);

        NbrOfPages = FLASH_PAGE_NBPERBANK;
    }

    if(status == HAL_OK)
    {
        //pEraseInit.Banks = FLASH_BANK_2;
        pEraseInit.NbPages = NbrOfPages;
        //pEraseInit.Page = FLASH_PAGE_NBPERBANK - pEraseInit.NbPages;
        pEraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
        //status = HAL_FLASHEx_Erase(&pEraseInit, &PageError);
    }

    HAL_FLASH_Lock();
    
    return (status == HAL_OK) ? BL_OK : BL_ERASE_ERROR;
}

/*** Begin flash programming **************************************************/
void Bootloader_FlashBegin(void)
{    
    flash_ptr = APP_ADDRESS;
    HAL_FLASH_Unlock();
}

/*** Program 64bit data into flash ********************************************/
uint16_t Bootloader_FlashNext(uint32_t address, uint16_t data)
{   
		__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR | FLASH_FLAG_OPTVERR);
    if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, address, data) == HAL_OK)      
    {
				return *(uint16_t*)address;
    }
		return 0x1;
}

void Bootloader_FlashEnd(void)
{   
    HAL_FLASH_Lock();
}



/*** Check if application fits into user flash ********************************/
uint8_t Bootloader_CheckSize(uint32_t appsize)
{
    return ((FLASH_BASE + FLASH_SIZE - APP_ADDRESS) >= appsize) ? BL_OK : BL_SIZE_ERROR;
}

/*** Verify checksum of application *******************************************/
uint8_t Bootloader_VerifyChecksum(void)
{
#if (USE_CHECKSUM)
    CRC_HandleTypeDef CrcHandle;
    volatile uint32_t calculatedCrc = 0;
    
    __HAL_RCC_CRC_CLK_ENABLE();
    CrcHandle.Instance = CRC;
    CrcHandle.Init.DefaultPolynomialUse    = DEFAULT_POLYNOMIAL_ENABLE;
    CrcHandle.Init.DefaultInitValueUse     = DEFAULT_INIT_VALUE_ENABLE;
    CrcHandle.Init.InputDataInversionMode  = CRC_INPUTDATA_INVERSION_NONE;
    CrcHandle.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
    CrcHandle.InputDataFormat              = CRC_INPUTDATA_FORMAT_WORDS;
    if(HAL_CRC_Init(&CrcHandle) != HAL_OK)
    {    
        return BL_CHKS_ERROR;
    }
    
    calculatedCrc = HAL_CRC_Calculate(&CrcHandle, (uint32_t*)APP_ADDRESS, APP_SIZE);
    
    __HAL_RCC_CRC_FORCE_RESET();
    __HAL_RCC_CRC_RELEASE_RESET();
    
    if( (*(uint32_t*)CRC_ADDRESS) == calculatedCrc )
    {
        return BL_OK;
    }
#endif
    return BL_CHKS_ERROR;
}
/*
uint8_t Bootloader_CheckForApplication(void)
{
    return ( ((*(__IO uint32_t*)APP_ADDRESS) & ~(RAM_SIZE-1)) == 0x20000000 ) ? BL_OK : BL_NO_APP;
}
*/
/*** Jump to application ******************************************************/
void Bootloader_JumpToApplication(uint32_t address)
{
    uint32_t  JumpAddress = *(__IO uint32_t*)(address + 4);
    pFunction Jump = (pFunction)JumpAddress;    
    HAL_RCC_DeInit();
    HAL_DeInit();   
    SysTick->CTRL = 0;
    SysTick->LOAD = 0;
    SysTick->VAL  = 0;    
#if (SET_VECTOR_TABLE)
    SCB->VTOR = address;
#endif 
    __set_MSP(*(__IO uint32_t*)address);
    Jump();
}

/*** Jump to System Memory (ST Bootloader) ************************************/
void Bootloader_JumpToSysMem(void)
{
    uint32_t  JumpAddress = *(__IO uint32_t*)(SYSMEM_ADDRESS + 4);
    pFunction Jump = (pFunction)JumpAddress;
    
    HAL_RCC_DeInit();
    HAL_DeInit();
    
    SysTick->CTRL = 0;
    SysTick->LOAD = 0;
    SysTick->VAL  = 0;
    
    //__HAL_SYSCFG_REMAPMEMORY_SYSTEMFLASH();
    
    __set_MSP(*(__IO uint32_t*)SYSMEM_ADDRESS);
    Jump();
    
    while(1);
}
