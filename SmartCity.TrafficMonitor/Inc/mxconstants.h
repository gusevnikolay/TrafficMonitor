/**
  ******************************************************************************
  * File Name          : mxconstants.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MXCONSTANT_H
#define __MXCONSTANT_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define OLED_EN_Pin GPIO_PIN_0
#define OLED_EN_GPIO_Port GPIOC
#define STEP_UP_EN_Pin GPIO_PIN_1
#define STEP_UP_EN_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_2
#define LED1_GPIO_Port GPIOC
#define LED2_Pin GPIO_PIN_3
#define LED2_GPIO_Port GPIOC
#define DOPLER_2_EN_Pin GPIO_PIN_1
#define DOPLER_2_EN_GPIO_Port GPIOA
#define DOPLER_1_EN_Pin GPIO_PIN_3
#define DOPLER_1_EN_GPIO_Port GPIOA
#define GPS_EN_Pin GPIO_PIN_6
#define GPS_EN_GPIO_Port GPIOA
#define RFM_IO0_Pin GPIO_PIN_0
#define RFM_IO0_GPIO_Port GPIOB
#define RFM_IO1_Pin GPIO_PIN_1
#define RFM_IO1_GPIO_Port GPIOB
#define RFM_RESET_Pin GPIO_PIN_11
#define RFM_RESET_GPIO_Port GPIOB
#define BUTTON_Pin GPIO_PIN_7
#define BUTTON_GPIO_Port GPIOC
#define RS485_TX_Pin GPIO_PIN_9
#define RS485_TX_GPIO_Port GPIOA
#define RS485_RX_Pin GPIO_PIN_10
#define RS485_RX_GPIO_Port GPIOA
#define PPS_Pin GPIO_PIN_15
#define PPS_GPIO_Port GPIOA
#define GPS_TX_Pin GPIO_PIN_10
#define GPS_TX_GPIO_Port GPIOC
#define GPS_RX_Pin GPIO_PIN_11
#define GPS_RX_GPIO_Port GPIOC
#define RS485_DIR_Pin GPIO_PIN_12
#define RS485_DIR_GPIO_Port GPIOC
#define RFM_IO3_Pin GPIO_PIN_3
#define RFM_IO3_GPIO_Port GPIOB
#define RFM_IO4_Pin GPIO_PIN_4
#define RFM_IO4_GPIO_Port GPIOB
#define RFM_IO5_Pin GPIO_PIN_5
#define RFM_IO5_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MXCONSTANT_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
