#include "stm32f1xx_hal.h"
#include "lora.h"
#include <stdint.h>
extern SPI_HandleTypeDef hspi2;
char lora_status_line[18] = "Lora:Wait  SQ: -87";


void Rfm_Write(uint8_t reg, uint8_t data)
{
		uint8_t buffer[4];
		buffer[0] = reg | 0x80;
		buffer[1] = data;
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
		HAL_SPI_Transmit(&hspi2, buffer, 2, 100);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
}

uint8_t Rfm_Read(uint8_t reg)
{
		uint8_t bb[3]={0,0,0};
		uint8_t bt[3]={0,0,0};		
		bb[0] = reg;	
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
	  HAL_SPI_TransmitReceive(&hspi2, bb, bt, 2, 100);	//Receive
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);		
		return bt[1];
}

void Rfm_Send(uint8_t *data, uint8_t length)
{
		Rfm_Write(0x40, 0x40);
    Rfm_Write(0x22, length);
		Rfm_Write(0xD, Rfm_Read(0xE));
		for(int i=0; i<length;i++)Rfm_Write(0, data[i]);
		Rfm_Write(0x1, 0x83);
		lora_status_line[5] = 'T'; lora_status_line[6] = 'X'; lora_status_line[7] = '-'; lora_status_line[8] = '>';
}

void Lora_Init(void)
{
		Rfm_Write(0x01, 0);
		while(Rfm_Read(0x01) != 0)
		{
				HAL_Delay(1);
		}
		Rfm_Write(0x1, 0x80);
		Rfm_Write(0x1, 0x81);
		Rfm_Write(0x6, 0xD9);
		Rfm_Write(0x7, 0x6);
		Rfm_Write(0x8, 0x8B);
		Rfm_Write(0x9, 0xFF);
		Rfm_Write(0x1D, 0x72);
		Rfm_Write(0x1E, 0x74);
		Rfm_Write(0x20, 0x0);
		Rfm_Write(0x21, 0x8);
		Rfm_Write(0x39, 0x34);
		Rfm_Write(0x33, 0x27);
		Rfm_Write(0x3B, 0x1D);
		Rfm_Write(0xE, 0x80);
		Rfm_Write(0xF, 0x0);
		Rfm_Write(0x1, 0x85);
}

void Lora_Polling()
{
		unsigned char irq = Rfm_Read(0x12);
	  unsigned char mode = Rfm_Read(0x1);
	  if((irq & 0x8)>0){lora_status_line[5] = 'T'; lora_status_line[6] = 'X'; lora_status_line[7] = '+'; lora_status_line[8] = '+';	Rfm_Write(0x12, irq);Rfm_Write(0x1, 0x81);}
		else if(mode == 0x81){lora_status_line[5] = 'W'; lora_status_line[6] = 'a'; lora_status_line[7] = 'i'; lora_status_line[8] = 't';}
		
}
