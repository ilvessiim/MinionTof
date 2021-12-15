/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "i2c.h"
#include "iwdg.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "iBus.h"
#include "modes.h"
#include "minion_drive.h"
#include "odom.h"
#include <stdlib.h>
#include "sonar.h"
#include "../../../../Drivers/VL53L1X/core/inc/vl53l1_api.h"
#include "tof.h"
//#include "visEffect.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart7;



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
volatile uint8_t rec_data[10];// = {'A','A','1','6','0','0','1','5','0','0'};


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM3_Init();
  MX_TIM1_Init();
  MX_TIM4_Init();
  MX_UART7_Init();
  MX_I2C2_Init();
  MX_IWDG_Init();
  MX_USART3_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  uint16_t v = 1500;
  uint16_t w = 1500;

  //int32_t motor_step_counter[2] = {0, 0};
  //int32_t sonars[3] = {0, 0, 0};
  int32_t odom_1 = 0;
  int32_t odom_2 = 0;
  int16_t sonar_1 = 0;
  int16_t sonar_2 = 0;
  int16_t sonar_3 = 0;
  int16_t tof_1 = 0;
  uint8_t data_to_send[29];
  void send_data(int32_t tof_1, int32_t odom_2, int16_t sonar_1, int16_t sonar_2, int16_t sonar_3){
  	itoa(tof_1, data_to_send, 10);
  	itoa(2, data_to_send+8, 10);
  	itoa(3, data_to_send+16, 10);
  	itoa(5, data_to_send+20, 10);
  	itoa(6, data_to_send+24, 10);
	/*memcpy(&odom_1, data_to_send, 10);
	memcpy(&odom_2, data_to_send+4, 10);
	memcpy(&sonar_1, data_to_send+8, 10);
	memcpy(&sonar_2, data_to_send+12, 10);
	memcpy(&sonar_3, data_to_send+16, 10);*/
  	data_to_send[28] = '\n';
  	HAL_UART_Transmit (&huart3, data_to_send, 29, 100);

  }
  void led_1_on()
  {
	  HAL_GPIO_WritePin(LED1_out_GPIO_Port, LED1_out_Pin, 1);
  }
  void led_1_off()
  {
	  HAL_GPIO_WritePin(LED1_out_GPIO_Port, LED1_out_Pin, 0);
  }
  void led_2_on()
  {
	  HAL_GPIO_WritePin(LED2_out_GPIO_Port, LED2_out_Pin, 1);
  }
  void led_2_off()
  {
	  HAL_GPIO_WritePin(LED2_out_GPIO_Port, LED2_out_Pin, 0);
  }
  void led_3_on()
  {
	  HAL_GPIO_WritePin(LED3_out_GPIO_Port, LED3_out_Pin, 1);
  }
  void led_3_off()
  {
	  HAL_GPIO_WritePin(LED3_out_GPIO_Port, LED3_out_Pin, 0);
  }
  // initiate the reception of the first byte.
  HAL_UART_Receive_IT(&huart7, ibus_rx_buffer, 1);
  HAL_UART_Receive_IT(&huart3, rec_data, 10);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  zero_time1 = HAL_GetTick();
  zero_time2 = HAL_GetTick();
  zero_time3 = HAL_GetTick();

  tof_init();
  while (1)
  {
	  sonar_1 = sonar_s1(sonar_1);
	  sonar_2 = sonar_s2(sonar_2);
	  sonar_3 = sonar_s3(sonar_3);
	  uint32_t  kaka = HAL_GetTick();
	  HAL_IWDG_Refresh(&hiwdg);
	  ReceiverState_t message_data = { 0 };
	  uint8_t has_new_message = 0;
	  Speeds speed = {0};
	  SpeedPercentages sp = {0};

	  if (ibus_rx_flags == IBUS_HAS_MESSAGE)
	  {
		  //HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
		  message_data = HandleReceiverMessage();
		  has_new_message = 1;
	  }
	  else
	  {
		  // hacky solution to ISR errors.
		  CheckUartInterruptStatus();
	  }

	  if (has_new_message)
	  {
		  // select mode
		  if(message_data.switch_c == ReceiverSwitchUp) // manual
		  {
			  if(sonar_1 > 100 && sonar_2 > 100 && sonar_3 > 100 ){
				  led_1_on();
				  led_2_off();
				  led_3_off();
				  v = message_data.right_vertical;
				  w = message_data.right_horizontal;
			  }

			  else{
				  v=1500;
				  w=1500;
			  }
		  }
		  else if(message_data.switch_c == ReceiverSwitchMiddle) //automatic
		  {
			  led_1_off();
			  led_2_on();
			  led_3_off();
			  speed = automatic(rec_data);
			  v = speed.v;
			  w = speed.w;
		  }
		  else //armed
		  {
			  v = 1500;
			  w = 1500;
			  led_1_off();
			  led_2_off();
			  led_3_on();
		  }

	  }
	  else
	  {
		  ;
		  //v = 1500;
		  //w = 1500;
	  }

	  sp = setThrottle(v, w);
	  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, sp.lv);
	  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, sp.rv);

	  odom_1 = odometry_m1(odom_1);
	  odom_2 = odometry_m2(odom_2);
	  tof_1 = tof_t1();

	  send_data(tof_1, odom_2, sonar_1, sonar_2, sonar_3);//odometry_m1, odometry_m2, sonars[0], sonars[1], sonars[2]);


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 96;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART3|RCC_PERIPHCLK_UART7
                              |RCC_PERIPHCLK_I2C1|RCC_PERIPHCLK_I2C2;
  PeriphClkInitStruct.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
  PeriphClkInitStruct.Uart7ClockSelection = RCC_UART7CLKSOURCE_PCLK1;
  PeriphClkInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInitStruct.I2c2ClockSelection = RCC_I2C2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
