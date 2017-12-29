#ifndef __STM32F1xx_IT_H
#define __STM32F1xx_IT_H

#ifdef __cplusplus
 extern "C" {
#endif 

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void DMA1_Channel1_IRQHandler(void);
void ADC1_2_IRQHandler(void);
void USB_LP_CAN1_RX0_IRQHandler(void);
void EXTI15_10_IRQHandler(void);
void TIM6_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif 

