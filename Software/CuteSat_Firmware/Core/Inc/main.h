/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32h7xx_hal.h"

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
#define D1_DIR_Pin GPIO_PIN_4
#define D1_DIR_GPIO_Port GPIOE
#define D1_SPEED_Pin GPIO_PIN_5
#define D1_SPEED_GPIO_Port GPIOE
#define TEMP_ALERT_Pin GPIO_PIN_2
#define TEMP_ALERT_GPIO_Port GPIOF
#define D2_SPEED_Pin GPIO_PIN_7
#define D2_SPEED_GPIO_Port GPIOF
#define D2_DIR_Pin GPIO_PIN_8
#define D2_DIR_GPIO_Port GPIOF
#define ALERT_INA238_1_Pin GPIO_PIN_2
#define ALERT_INA238_1_GPIO_Port GPIOC
#define ALERT_INA238_2_Pin GPIO_PIN_3
#define ALERT_INA238_2_GPIO_Port GPIOC
#define SPI1_CS_Pin GPIO_PIN_4
#define SPI1_CS_GPIO_Port GPIOA
#define LED4_Pin GPIO_PIN_14
#define LED4_GPIO_Port GPIOF
#define LED3_Pin GPIO_PIN_15
#define LED3_GPIO_Port GPIOF
#define LED2_Pin GPIO_PIN_0
#define LED2_GPIO_Port GPIOG
#define LED1_Pin GPIO_PIN_1
#define LED1_GPIO_Port GPIOG
#define FRAM_CS_Pin GPIO_PIN_12
#define FRAM_CS_GPIO_Port GPIOB
#define FRAM_HOLD_Pin GPIO_PIN_8
#define FRAM_HOLD_GPIO_Port GPIOD
#define FRAM_WP_Pin GPIO_PIN_9
#define FRAM_WP_GPIO_Port GPIOD
#define SDMMC_DETECT_Pin GPIO_PIN_0
#define SDMMC_DETECT_GPIO_Port GPIOD
#define SPI6_CS_Pin GPIO_PIN_11
#define SPI6_CS_GPIO_Port GPIOG
#define WDI2_Pin GPIO_PIN_0
#define WDI2_GPIO_Port GPIOE
#define WDI1_Pin GPIO_PIN_1
#define WDI1_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
