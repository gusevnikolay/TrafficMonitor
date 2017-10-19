
#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "stm32f1xx_it.h"

extern PCD_HandleTypeDef hpcd_USB_FS;
extern UART_HandleTypeDef huart1;


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

/**
* @brief This function handles System service call via SWI instruction.
*/
void SVC_Handler(void)
{

}

/**
* @brief This function handles Debug monitor.
*/
void DebugMon_Handler(void)
{

}

/**
* @brief This function handles Pendable request for system service.
*/
void PendSV_Handler(void)
{

}

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
}

/**
* @brief This function handles USB low priority or CAN RX0 interrupts.
*/
void USB_LP_CAN1_RX0_IRQHandler(void)
{
	
  HAL_PCD_IRQHandler(&hpcd_USB_FS);
}

/**
* @brief This function handles USART1 global interrupt.
*/
void USART1_IRQHandler(void)
{

  HAL_UART_IRQHandler(&huart1);
}
