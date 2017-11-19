#include "stm32f0xx_hal.h"
#include "flasher.h"

void flash_append(uint8_t *data, uint16_t data_length)
{
	
}

void flash_unlock(void) {
		FLASH->KEYR = FLASH_KEY1;
		FLASH->KEYR = FLASH_KEY2;
}

void FLASH_errase_Page(uint32_t address_start)
{
		flash_unlock();
		FLASH->CR = FLASH_CR_PER;
		FLASH->AR = address_start;
		FLASH->CR|= FLASH_CR_STRT;
		while ((FLASH->SR & FLASH_SR_BSY) != 0 );
		FLASH->CR = FLASH_CR_LOCK;      
}

void Write_FLASH(){
      uint32_t address =0;
      uint32_t address2 =0;
      int long numstring = 0;
      uint8_t temp3 = 0; 
      uint8_t temp4 = 0;
      uint32_t data = 0;
      int long line =0;
      uint8_t temp5 = 0;
      uint32_t temp6;
        
      FLASH_errase();
        
  for(temp3=0; temp3<couBaits_toFLASH; temp3++)
       {
        flash_unlock();
                
        FLASH->CR |= FLASH_CR_PG; //????????? ???????????????? ?????
                
        address=0;
        temp6=0;
                
        address = BUFFER_data[line][1];
        temp6 = address;                
        address = BUFFER_data[line][2];
        temp6 = temp6 << 8;
        address |=  temp6 ;
        
        temp6 = 0x8001800;
        temp6&=~0x00FFFFF;
        address |= temp6;
                
        for(temp4=0;temp4<16; temp4=temp4+4)
          {
           data = 0;
           data |= (BUFFER_data[line][temp4+7]) ;   data = data <<8;
           data |= (BUFFER_data[line][temp4+6] );   data = data <<8;    
           data |= (BUFFER_data[line][temp4+5] );   data = data <<8;
           data |= (BUFFER_data[line][temp4 + 4] );
                        
           while ((FLASH->SR & FLASH_SR_BSY) != 0 );
      *(__IO uint16_t*)address = (uint16_t)data; //??????? 2 ?????
          while ((FLASH->SR & FLASH_SR_BSY) != 0 );
                        
          address+=2;
          data>>=16;
       *(__IO uint16_t*)address = (uint16_t)data; //??????? 2 ?????
          while ((FLASH->SR & FLASH_SR_BSY) != 0 );
          address+=2;
         }
          data = 0;
          FLASH->CR &= ~(FLASH_CR_PG); //?????? ????????????????
          line++;
   }    
}
