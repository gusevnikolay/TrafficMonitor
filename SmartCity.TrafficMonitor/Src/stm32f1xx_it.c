#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "stm32f1xx_it.h"

extern PCD_HandleTypeDef hpcd_USB_FS;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim6;
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart1;
extern void nmea_append(char ch);

void NMI_Handler(void)
{

}


void HardFault_Handler(void)
{

  while (1)
  {
  }
}

void MemManage_Handler(void)
{

  while (1)
  {
  }
}


void BusFault_Handler(void)
{
  while (1)
  {
  }
}


void UsageFault_Handler(void)
{

  while (1)
  {
  }
}


void SVC_Handler(void)
{

}


void DebugMon_Handler(void)
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


void USB_LP_CAN1_RX0_IRQHandler(void)
{

  HAL_PCD_IRQHandler(&hpcd_USB_FS);
}


void USART1_IRQHandler(void)
{

  HAL_UART_IRQHandler(&huart1);
}


void EXTI15_10_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);	
}

extern void speed_append_sensor_two(uint16_t tim);
extern void speed_append_sensor_one(uint16_t tim);
void TIM5_IRQHandler(void)
{
	__HAL_TIM_SetCounter(&htim5, 0);
	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	speed_append_sensor_two(__HAL_TIM_GetCompare(&htim5, TIM_CHANNEL_3));
	speed_append_sensor_one(__HAL_TIM_GetCompare(&htim5, TIM_CHANNEL_1));
  HAL_TIM_IRQHandler(&htim5);
}

void UART4_IRQHandler(void)
{
	nmea_append(UART4->DR);
  HAL_UART_IRQHandler(&huart4);
}

void TIM6_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim6);
}
