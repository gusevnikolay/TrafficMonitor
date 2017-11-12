#include "stm32f0xx_hal.h"
#include "stm32f0xx.h"
#include "stm32f0xx_it.h"
#include "sx1276.h"
#include "usbd_cdc_if.h"

extern PCD_HandleTypeDef hpcd_USB_FS;
extern UART_HandleTypeDef huart2;

void NMI_Handler(void)
{

}

void HardFault_Handler(void)
{
  while (1)
  {
  }
}

void SVC_Handler(void)
{

}

void PendSV_Handler(void)
{

}

void SysTick_Handler(void)
{

  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
}

void EXTI0_1_IRQHandler(void)
{
	if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_0) != RESET) 
  { 
		SX1276OnDio0Irq();
  }
	if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_1) != RESET) 
  { 
		SX1276OnDio1Irq();
  }
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
}


void EXTI2_3_IRQHandler(void)
{
	if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_2) != RESET) 
  { 
		SX1276OnDio2Irq();
  }
	if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_3) != RESET) 
  { 
		SX1276OnDio3Irq();
  }
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
}


void EXTI4_15_IRQHandler(void)
{
	if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_4) != RESET) 
  { 
		SX1276OnDio4Irq();
  }
	if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_5) != RESET) 
  { 
		SX1276OnDio5Irq();
  }
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
}

uint8_t isUsart = 1;
unsigned char uart_received( unsigned char port)
{
		return 1;
}


uint8_t dataByte = 0;
unsigned char uart_get( unsigned char port)
{
		return dataByte;
}

void uart_send( unsigned char port, unsigned char data)
{	
		if(port==0){
				USART1->TDR = data;
				while((USART2->ISR & 0x80) == 0);
		}else{
				uint8_t buf[1];
			  buf[0] = data;
 				CDC_Transmit_FS(buf, 1);
		}
}

extern void sserial_poll_uart(unsigned char port);
void USART2_IRQHandler(void)
{
		dataByte = USART2->RDR;
	  sserial_poll_uart(0);
		HAL_GPIO_WritePin(GPIOB, LED0_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOB, LED0_Pin, GPIO_PIN_SET);
		HAL_UART_IRQHandler(&huart2);
}


void USB_IRQHandler(void)
{
	
  HAL_PCD_IRQHandler(&hpcd_USB_FS);
}
