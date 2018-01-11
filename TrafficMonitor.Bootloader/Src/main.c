#include "stm32f1xx_hal.h"
#include "lora.h"
#include "bootloader.h"

CRC_HandleTypeDef hcrc;
SPI_HandleTypeDef hspi2;

void SystemClock_Config(void);
void Error_Handler(void);
static void MX_GPIO_Init(void);
static void MX_SPI2_Init(void);
static void MX_CRC_Init(void);
static void MX_GPIO_DeInit(void);

int sec_to_boot    = 600;
uint16_t offset    = 0;
uint8_t rx_present = 0;
void Lora_Rx_Handler(uint8_t *data, uint8_t data_length)
{			
		sec_to_boot = 600;
		uint32_t address = 0;	
	  uint8_t buffer[256];
		if(data[0] == 26 && data[1] == 126 && data[2] == 76){
					offset = data[3]*256 + data[4];	
					buffer[0] = 128;
					buffer[1] = 185;
					buffer[2] = 27;
					buffer[3] = data[3];
					buffer[4] = data[4];
					Rfm_Send(buffer,5);
		}
		
		if(data[0] == 76 && data[1] == 74 && data[2] == 98){
					if(rx_present == 0){
							Bootloader_erase();
							rx_present = 1;
					}
					uint8_t buffer[256];
					address = ((data[3]*256 + data[4]) | (offset<<16));	
					uint16_t crc = 0;
					for(int i=0;i<data[5];i++)
					{
							buffer[i] = data[i+7];
						  crc += data[i+7];
					}
					if((data[6] - (crc & 0xFF)) == 0){
							Bootloader_write(address, buffer, data[5]);
							buffer[0] = 24;
							buffer[1] = 42;
							buffer[2] = 64;
							buffer[3] = data[3];
							buffer[4] = data[4];
							Rfm_Send(buffer,5);
					}
		}
					
		if(data[0] == 1 && data[1] == 241 && data[2] == 38){
				  buffer[0] = 87;
					buffer[1] = 24;
					buffer[2] = 73;
					buffer[3] = 0;
					buffer[4] = 0;
					for (int i=0;i<10;i++){
							Rfm_Send(buffer,5);
							HAL_Delay(1000);
					}		
					MX_GPIO_DeInit();
			    HAL_SPI_DeInit(&hspi2);
					HAL_CRC_DeInit(&hcrc); 
					HAL_RCC_DeInit();
					Bootloader_start();
		}
}		

int main(void)
{

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
	HAL_GPIO_WritePin(RFM_RESET_GPIO_Port, RFM_RESET_Pin, GPIO_PIN_SET);
  MX_SPI2_Init();
  MX_CRC_Init();
	Lora_Init();
	unsigned long delay = 0;
  while (1)
  {
		Lora_Polling();
		if(delay++>24000){
			delay = 0;
			if(sec_to_boot-->0){
					if(rx_present == 0){
							uint8_t buffer[5];
							buffer[0] = 48;
							buffer[1] = 85;
							buffer[2] = 127;
							Rfm_Send(buffer, 5);		
					}
			}else{
				MX_GPIO_DeInit();
				HAL_SPI_DeInit(&hspi2);
				HAL_CRC_DeInit(&hcrc); 
				HAL_RCC_DeInit();
				Bootloader_start();
			}
		}
  }
}


void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* CRC init function */
static void MX_CRC_Init(void)
{

  hcrc.Instance = CRC;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }

}

/* SPI2 init function */
static void MX_SPI2_Init(void)
{
	hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  HAL_GPIO_WritePin(GPIOC, LED2_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB, RFM_RESET_Pin|GPIO_PIN_12, GPIO_PIN_RESET);
  GPIO_InitStruct.Pin = LED2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = RFM_IO1_Pin|GPIO_PIN_2|RFM_IO3_Pin|RFM_IO4_Pin 
                          |RFM_IO5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = RFM_RESET_Pin|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

}

static void MX_GPIO_DeInit(void)
{
  HAL_GPIO_DeInit(GPIOC, LED2_Pin);
  HAL_GPIO_DeInit(GPIOB, GPIO_PIN_0);
  HAL_GPIO_DeInit(GPIOB, RFM_IO1_Pin|GPIO_PIN_2|RFM_IO3_Pin|RFM_IO4_Pin |RFM_IO5_Pin);
  HAL_GPIO_DeInit(GPIOB, RFM_RESET_Pin|GPIO_PIN_12);
  HAL_NVIC_DisableIRQ(EXTI0_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/