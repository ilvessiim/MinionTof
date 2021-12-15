/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

#include "stm32f7xx_ll_tim.h"
#include "stm32f7xx_ll_bus.h"
#include "stm32f7xx_ll_cortex.h"
#include "stm32f7xx_ll_rcc.h"
#include "stm32f7xx_ll_system.h"
#include "stm32f7xx_ll_utils.h"
#include "stm32f7xx_ll_pwr.h"
#include "stm32f7xx_ll_gpio.h"
#include "stm32f7xx_ll_dma.h"

#include "stm32f7xx_ll_exti.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Sonar_sda_Pin GPIO_PIN_0
#define Sonar_sda_GPIO_Port GPIOF
#define Sonar_scl_Pin GPIO_PIN_1
#define Sonar_scl_GPIO_Port GPIOF
#define LD1_Pin GPIO_PIN_0
#define LD1_GPIO_Port GPIOC
#define M1_dir_out_Pin GPIO_PIN_5
#define M1_dir_out_GPIO_Port GPIOA
#define M2_dir_out_Pin GPIO_PIN_6
#define M2_dir_out_GPIO_Port GPIOA
#define ODO2_V_Pin GPIO_PIN_14
#define ODO2_V_GPIO_Port GPIOF
#define ODO1_U_Pin GPIO_PIN_15
#define ODO1_U_GPIO_Port GPIOF
#define Ibus_rx_Pin GPIO_PIN_7
#define Ibus_rx_GPIO_Port GPIOE
#define Ibus_tx_Pin GPIO_PIN_8
#define Ibus_tx_GPIO_Port GPIOE
#define LED1_out_Pin GPIO_PIN_10
#define LED1_out_GPIO_Port GPIOE
#define ODO2_U_Pin GPIO_PIN_11
#define ODO2_U_GPIO_Port GPIOE
#define LED2_out_Pin GPIO_PIN_12
#define LED2_out_GPIO_Port GPIOE
#define ODO2_W_Pin GPIO_PIN_13
#define ODO2_W_GPIO_Port GPIOE
#define LED3_out_Pin GPIO_PIN_14
#define LED3_out_GPIO_Port GPIOE
#define LD3_Pin GPIO_PIN_14
#define LD3_GPIO_Port GPIOB
#define ODO1_W_Pin GPIO_PIN_9
#define ODO1_W_GPIO_Port GPIOG
#define ODO1_V_Pin GPIO_PIN_14
#define ODO1_V_GPIO_Port GPIOG
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
