#include "stm32f1xx_hal.h"
#include "bwl_simplserial.h"
#include "bootloader.h"

#define APPLICATION_ADDRESS         (uint32_t)0x08004000  
#define APPLICATION_ADDRESS_END     (uint32_t)0x08010000 
I2C_HandleTypeDef hi2c1;
SPI_HandleTypeDef hspi2;
UART_HandleTypeDef huart1;
HAL_StatusTypeDef	flash_ok = HAL_ERROR;

void SystemClock_Config(void);
void Error_Handler(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI2_Init(void);
static void MX_USART1_UART_Init(void);

sserial_response_t sserial_response;
sserial_request_t sserial_request;

void var_delay_ms(int ms){HAL_Delay(ms);}
void sserial_send_start(unsigned char portindex){HAL_GPIO_WritePin(RS485_DIR_GPIO_Port, RS485_DIR_Pin, GPIO_PIN_SET);}
void sserial_send_end(unsigned char portindex){HAL_GPIO_WritePin(RS485_DIR_GPIO_Port, RS485_DIR_Pin, GPIO_PIN_RESET);}
	
void uart_send(unsigned char port, unsigned char data)
{
	uint8_t tx_buffer[1];
	tx_buffer[0] = data;
	HAL_UART_Transmit(&huart1, tx_buffer, 1, 100);	
}
uint8_t data[1];
unsigned char uart_get( unsigned char port)
{
	return (unsigned char)data[0];	
}

unsigned char uart_received(unsigned char port)
{
	return 1;
}

typedef void (*pFunction)(void);

void JumpToApp(void)
{
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

void Flash_Erase()
{
		 FLASH_EraseInitTypeDef EraseInitStruct;
		 uint32_t PageError = 0;
     EraseInitStruct.TypeErase = TYPEERASE_PAGES;
     EraseInitStruct.PageAddress = APPLICATION_ADDRESS;
     EraseInitStruct.NbPages =  (APPLICATION_ADDRESS_END - APPLICATION_ADDRESS)/FLASH_PAGE_SIZE;
	   HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);
}

uint32_t flash_data = 0;
uint16_t dataOffset = 0x000;

void sserial_process_request(unsigned char portindex)
{
	if (sserial_request.command==1)
	{
			Flash_Erase();
		  CLEAR_BIT (FLASH->CR, (FLASH_CR_PER));
			sserial_send_response();
	}
	
	if(sserial_request.command==2)
	{
			uint32_t address = (sserial_request.data[0]*256 + sserial_request.data[1]) + (dataOffset<<16);
			uint8_t data_hex[128];
		  for(int i=0;i<sserial_request.datalength-3;i++){
					data_hex[i] = sserial_request.data[i+3];
			}
			Bootloader_write(address, data_hex, sserial_request.datalength-3);
			sserial_response.result = 128;
			sserial_response.datalength = sserial_request.datalength-3;
			sserial_send_response();
	}
	
	if(sserial_request.command==4)
	{
			dataOffset = sserial_request.data[0] * 256 + sserial_request.data[1];
			sserial_response.result = 128;
			sserial_send_response();
	}
	
	if (sserial_request.command==3)
	{
			sserial_send_response();
			Bootloader_start();
	}
}

int main(void)
{

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_SPI2_Init();
  MX_USART1_UART_Init();
	HAL_GPIO_WritePin(RS485_DIR_GPIO_Port, RS485_DIR_Pin, GPIO_PIN_RESET);
	sserial_set_devname("SmartCity.AccessPoint v1.0    ");
	Bootloader_erase();
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
  while (1)
  {
		if(HAL_UART_Receive(&huart1, data, 1, 1000)==HAL_OK){
			 
				sserial_poll_uart(0);		
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
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}


static void MX_I2C1_Init(void)
{

  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
}


static void MX_SPI2_Init(void)
{
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 38400;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
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
  HAL_GPIO_WritePin(GPIOC, OLED_EN_Pin|LED1_Pin|LED2_Pin|RS485_DIR_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB, RFM_RESET_Pin|GPIO_PIN_12, GPIO_PIN_RESET);
  GPIO_InitStruct.Pin = OLED_EN_Pin|LED1_Pin|LED2_Pin|RS485_DIR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = RFM_IO0_Pin|RFM_IO1_Pin|GPIO_PIN_2|RFM_IO3_Pin 
                          |RFM_IO4_Pin|RFM_IO5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = RFM_RESET_Pin|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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
