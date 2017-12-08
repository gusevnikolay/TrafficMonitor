#include "stm32f0xx_hal.h"
#include "bwl_simplserial.h"

#define APPLICATION_ADDRESS     	0x08002000
#define APPLICATION_ADDRESS_END   0x08008000
__IO uint32_t VectorTable[48] __attribute__((at(0x20000000)));
CRC_HandleTypeDef  hcrc;
UART_HandleTypeDef huart2;
sserial_response_t sserial_response;
sserial_request_t sserial_request;

void SystemClock_Config(void);
void Error_Handler(void);
static void MX_GPIO_Init(void);
static void MX_CRC_Init(void);
static void MX_USART2_UART_Init(void);

void var_delay_ms(int ms){HAL_Delay(ms);}
void sserial_send_start(unsigned char portindex){}
void sserial_send_end(unsigned char portindex){}
	
void uart_send(unsigned char port, unsigned char data)
{
	uint8_t tx_buffer[1];
	tx_buffer[0] = data;
	HAL_UART_Transmit(&huart2, tx_buffer, 1, 100);
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

void Go_To_User_App(void)
{
		__disable_irq();
	  __HAL_RCC_SYSCFG_CLK_ENABLE();
		for(int i = 0; i < 48; i++)
		{
			VectorTable[i] = *(__IO uint32_t*)(APPLICATION_ADDRESS + (i<<2));
		}
		SYSCFG->CFGR1 |= SYSCFG_CFGR1_MEM_MODE;    
		RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;
    typedef void (*pFunction)(void);
    pFunction Jump_To_Application;
		uint32_t JumpAddress = APPLICATION_ADDRESS;  
		JumpAddress = *(__IO uint32_t*) (APPLICATION_ADDRESS);
    Jump_To_Application = (pFunction) JumpAddress;
    //__set_MSP(*(__IO uint32_t*) APPLICATION_ADDRESS);
		__asm volatile ("cpsie i");
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
    Jump_To_Application();
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

uint32_t flash_data;
void sserial_process_request(unsigned char portindex)
{
	if (sserial_request.command==1)
	{
		HAL_FLASH_Unlock();
		Flash_Erase();
		sserial_send_response();
	}
	if(sserial_request.command==2)
	{
			uint32_t address = (sserial_request.data[0]*256*256*256 + sserial_request.data[1]*256*256 + sserial_request.data[2]*256 + sserial_request.data[3]);
			HAL_FLASH_Unlock();
			__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP|FLASH_FLAG_WRPERR | FLASH_FLAG_PGERR | FLASH_FLAG_BSY);
		
			for(int i = 1; i<sserial_request.datalength/4;i++)
			{
					flash_data = sserial_request.data[i*4] + sserial_request.data[i*4+1]*256 + sserial_request.data[i*4+2]*256*256 + sserial_request.data[i*4+3]*256*256*256;
					HAL_FLASH_Program(TYPEPROGRAM_WORD, address+(i-1)*4, flash_data);
			}
			
			sserial_response.result = 128;
			sserial_send_response();
	}
	if (sserial_request.command==3)
	{
		HAL_FLASH_Lock();
		sserial_send_response();
		Go_To_User_App();
	}
}

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART2_UART_Init();
	sserial_set_devname("SmartCity.AccessPoint v1.0    ");
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
  while (1)
  {
		if(HAL_UART_Receive(&huart2, data, 1, 1000)==HAL_OK){
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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL3;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}


static void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 38400;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_2;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_RS485Ex_Init(&huart2, UART_DE_POLARITY_HIGH, 0, 0) != HAL_OK)
  {
    Error_Handler();
  }

}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

void Error_Handler(void)
{
  while(1) 
  {
  }
}

#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{

}

#endif
