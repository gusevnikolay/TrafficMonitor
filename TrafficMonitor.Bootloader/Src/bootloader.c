#include "stm32f1xx_hal.h"
#include "bootloader.h"

#define APPLICATION_ADDRESS         (uint32_t)0x08004000  
#define APPLICATION_ADDRESS_END     (uint32_t)0x08010000 
#define CRC_ADDRESS                 (uint32_t)(APPLICATION_ADDRESS_END-4) 

typedef void (*pFunction)(void);

void Bootloader_start(void)
{
	  HAL_FLASH_Lock();
    uint32_t  JumpAddress = *(__IO uint32_t*)(APPLICATION_ADDRESS + 4);
    pFunction Jump = (pFunction)JumpAddress;    
    HAL_RCC_DeInit();
    HAL_DeInit();   
    SysTick->CTRL = 0;
    SysTick->LOAD = 0;
    SysTick->VAL  = 0;    
    SCB->VTOR = APPLICATION_ADDRESS;
    __set_MSP(*(__IO uint32_t*)APPLICATION_ADDRESS);
    Jump();
}

uint8_t Bootloader_write(uint32_t address, uint8_t *data, uint8_t datalength)
{		   
			for(int i = 0; i<datalength;i+=2)
			{
					if(HAL_FLASH_Program(TYPEPROGRAM_HALFWORD, address+i, data[i]+data[1+i]*256) != HAL_OK)
					{
							return 0;
					}
				 	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_SR_PGERR | FLASH_FLAG_WRPERR | FLASH_FLAG_OPTVERR);
			}
			return 1;
}

void Bootloader_erase(void)
{
		 HAL_StatusTypeDef	flash_ok = HAL_ERROR;
		 while(flash_ok != HAL_OK){
				flash_ok = HAL_FLASH_Unlock();
	   }
	   flash_ok = HAL_ERROR;
	   __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_SR_PGERR | FLASH_FLAG_WRPERR | FLASH_FLAG_OPTVERR);
	 	 FLASH_EraseInitTypeDef EraseInitStruct;
		 uint32_t PageError = 0;
     EraseInitStruct.TypeErase = TYPEERASE_PAGES;
     EraseInitStruct.PageAddress = APPLICATION_ADDRESS;
     EraseInitStruct.NbPages =  (APPLICATION_ADDRESS_END - APPLICATION_ADDRESS)/FLASH_PAGE_SIZE;
	   HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);
		 CLEAR_BIT (FLASH->CR, (FLASH_CR_PER));
		 __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_SR_PGERR | FLASH_FLAG_WRPERR | FLASH_FLAG_OPTVERR);
}

uint8_t Bootloader_Checksum(void)
{
    CRC_HandleTypeDef CrcHandle;
    volatile uint32_t calculatedCrc = 0;   
    __HAL_RCC_CRC_CLK_ENABLE();
    CrcHandle.Instance = CRC;
    if(HAL_CRC_Init(&CrcHandle) != HAL_OK)
    {    
        return 0;
    }    
    calculatedCrc = HAL_CRC_Calculate(&CrcHandle, (uint32_t*)APPLICATION_ADDRESS, APPLICATION_ADDRESS-APPLICATION_ADDRESS_END);

    
    if( (*(uint32_t*)CRC_ADDRESS) == calculatedCrc )
    {
        return 1;
    }
    return 0;
}
