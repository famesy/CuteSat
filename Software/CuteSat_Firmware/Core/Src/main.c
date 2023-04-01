/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "crc.h"
#include "dma.h"
#include "fatfs.h"
#include "i2c.h"
#include "rtc.h"
#include "sdmmc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <math.h>
#include <Library/Logging.h>
#include <Library/FRAM.h>
#include <Library/TMP75.h>
#include <Library/INA238.h>
#include <Library/AS5047U.h>
#include <Library/Neopixel.h>
#include <Library/KalmanFilter.h>
#include <Library/EDAC.h>
#include <Library/Utils.h>
#include <Library/DRV10975.h>
#include <usbd_cdc_if.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define KALMAN_Q 5000
#define KALMAN_R 0.1
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
NeopixelParameter Neopixel;
AS5047U Encoder;
INA238 Current_Sensor_System;
INA238 Current_Sensor_Motor;
FRAM Fram;
DRV10975 Sin_Driver;

KalmanFilter KF_Motor;

float LDO_temp = 0.0;
int64_t filtered_motor_pos = 0;
int64_t filtered_motor_speed = 0;

uint16_t adc_in[2] = { 0 };
uint16_t adc_in2[2] = { 0 };

uint8_t d1_voltage = 0;
uint8_t fram_status = 0;
uint8_t d1_dir = 1;
uint8_t test_in[9] = { 0 };
int32_t sin_speed = 511;

uint64_t _micro = 0;
uint8_t final_ans[8] = { 0 };
uint8_t speed_change_trigger = 0;
RTC_TimeTypeDef gTime;

float SpeedBuffer1Sent[3000] = {0};
float SpeedBuffer2Sent[3000] = {0};
uint16_t Count2Sent = 0;
uint16_t CountStart = 0;

double motor_pos = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
 set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void Watchog_Timer_Trigger();
void Read_Power_Monitoring_Data();
void Read_Encoder();
void Control_Loop();
void Device_Init();
void Store_Config();
void Read_Config();
void Read_Driver_Param();
void Test_Fram();
void get_time();
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
  MX_SDMMC1_SD_Init();
  MX_FATFS_Init();
  MX_DMA_Init();
  MX_TIM2_Init();
  MX_USART3_UART_Init();
  MX_SPI2_Init();
  MX_I2C1_Init();
  MX_I2C4_Init();
  MX_SPI1_Init();
  MX_SPI6_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_TIM15_Init();
  MX_TIM17_Init();
  MX_USART2_UART_Init();
  MX_CRC_Init();
  MX_TIM6_Init();
  MX_RTC_Init();
  MX_I2C2_Init();
  MX_TIM4_Init();
  MX_ADC1_Init();
  MX_USB_DEVICE_Init();
  MX_TIM7_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim7);
	Watchog_Timer_Trigger();
	Device_Init();
	DRV10975_I2C_Set_Speed(&Sin_Driver, 0, 1);
	Test_Fram();
	while(1);
	uwTick = 0;
	uint32_t timestamp_1 = HAL_GetTick();
	uint32_t timestamp_2 = HAL_GetTick();
	uint32_t timestamp_3 = HAL_GetTick();
	uint32_t timestamp_4 = HAL_GetTick();
	uint8_t debug_msg[100] = "";
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {
		Read_Encoder();
		if (HAL_GetTick() - timestamp_1 >= 10) {
			timestamp_1 = HAL_GetTick();
			Read_Driver_Param();
			CountStart++;
			if (CountStart >= 500) {
				if (Count2Sent < 3000) {
					if (Count2Sent == 0) {
						DRV10975_I2C_Set_Speed(&Sin_Driver, sin_speed, d1_dir);
					}
					else if (Count2Sent == 1500){
						DRV10975_I2C_Set_Speed(&Sin_Driver, sin_speed, 0);
					}
					SpeedBuffer1Sent[Count2Sent] =
							(float) Sin_Driver.motor_speed;
					SpeedBuffer2Sent[Count2Sent] = (float) (4 * KF_Motor.x2
							/ (6.28318530718));
					Count2Sent++;
				} else {
					if (Count2Sent == 3000) {
						DRV10975_I2C_Set_Speed(&Sin_Driver, 0, d1_dir);
						for (int i = 0; i < 3000; i++) {
							printf("%f %f \n", SpeedBuffer1Sent[i],
									SpeedBuffer2Sent[i]);
						}
					}
					Count2Sent = 0;
					CountStart = 0;
				}
				if (speed_change_trigger) {
					DRV10975_I2C_Set_Speed(&Sin_Driver, sin_speed, d1_dir);
				}
			}
		}
		if (HAL_GetTick() - timestamp_2 >= 100) {
			timestamp_2 = HAL_GetTick();
			Read_Power_Monitoring_Data();
		}
		if (HAL_GetTick() - timestamp_3 >= 1) {
			timestamp_3 = HAL_GetTick();
			Control_Loop();
		}
		if (HAL_GetTick() - timestamp_4 >= 10000) {
			timestamp_4 = HAL_GetTick();
			sprintf((char *)debug_msg, "ldo temp is : %f", LDO_temp);
			SD_Card_Write_Log(LOG_DEBUG, debug_msg, strlen((char *) debug_msg));
			sprintf((char *)debug_msg, "power consumption of system : %f", Current_Sensor_System.power);
			SD_Card_Write_Log(LOG_DEBUG, debug_msg, strlen((char *) debug_msg));
			sprintf((char *)debug_msg, "power consumption of motor and driver : %f", Current_Sensor_Motor.power);
			SD_Card_Write_Log(LOG_DEBUG, debug_msg, strlen((char *) debug_msg));
		}
		HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
		Watchog_Timer_Trigger();

//	  SD_Card_Write_Log();
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

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Macro to configure the PLL clock source
  */
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSE);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 60;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  RCC_OscInitStruct.PLL.PLLR = 24;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */


void Read_Power_Monitoring_Data() {
	TMP75_Read_TempCelsius(&LDO_temp);
	INA238_read_all(&Current_Sensor_Motor);
	INA238_read_all(&Current_Sensor_System);
}

void Read_Encoder() {
	AS5047U_Position_Highspeed_Read(&Encoder, 0);
}

void Read_Driver_Param() {
	DRV10975_Read_Voltage(&Sin_Driver);
	DRV10975_Read_Kt(&Sin_Driver);
	DRV10975_Read_Period(&Sin_Driver);
	DRV10975_Read_Speed(&Sin_Driver);
	DRV10975_Read_Current(&Sin_Driver);
}

void Control_Loop() {
	static uint16_t enc_pos = 0;
	static uint16_t prev_enc_pos = 0;

	enc_pos = Encoder.Position;
	motor_pos += (Unwrap(enc_pos, prev_enc_pos) * (2 * M_PI / 16384.0)); //0.087890625 = (360 / 4096)
	prev_enc_pos = enc_pos;
	KalmanFilter_Update(&KF_Motor, motor_pos);
	filtered_motor_pos = KF_Motor.x1;
	filtered_motor_speed = KF_Motor.x2;
}

void Device_Init() {
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1); // indicate that mcu still alive :>

	uint8_t initialize_msg[25] = "MCU still alive :>";
	SD_Card_Write_Log(LOG_INFO, initialize_msg, strlen((char *) initialize_msg));

	KalmanFilter_Init(&KF_Motor, 0, 0, 1, 0, 0, 1, KALMAN_R, KALMAN_Q, 0.001);

	HAL_GPIO_WritePin(FRAM_WP_GPIO_Port, FRAM_WP_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(FRAM_HOLD_GPIO_Port, FRAM_HOLD_Pin, GPIO_PIN_SET);
	FRAM_Initialise(&Fram, &hspi2, FRAM_CS_GPIO_Port, FRAM_CS_Pin);
	AS5047U_init(&Encoder, &hspi1, SPI1_CS_GPIO_Port, &hcrc, SPI1_CS_Pin, 0);

	DRV10975_Init(&Sin_Driver, &hi2c2, &htim17, TIM_CHANNEL_1, D1_DIR_GPIO_Port,
	D1_DIR_Pin);
	DRV10975_Config(&Sin_Driver);
	//Motor Driver Current Sensor
	INA238_init(&Current_Sensor_Motor, &hi2c4, 0x80);
	INA238_reset(&Current_Sensor_Motor);
	INA238_set_mode(&Current_Sensor_Motor, 0x0F);
	INA238_calibrate(&Current_Sensor_Motor, 0, 0.05);

	//System Current Sensor
	INA238_init(&Current_Sensor_System, &hi2c4, 0x88);
	INA238_reset(&Current_Sensor_System);
	INA238_set_mode(&Current_Sensor_System, 0x0F);
	INA238_calibrate(&Current_Sensor_System, 1, 0.1);

	Neopixel_Init(&Neopixel, &htim2);
}

void Watchog_Timer_Trigger() {
	// External WD Trigger
	HAL_GPIO_TogglePin(WDI1_GPIO_Port, WDI1_Pin);
	HAL_GPIO_TogglePin(WDI2_GPIO_Port, WDI2_Pin);
	// Internal WD
//	HAL_IWDG_Refresh(&hiwdg1);
}

void Test_Fram() {
	float read_first_data = 0;
	uint32_t read_second_data = 0;
	uint8_t test[8] = {0x42,0xf6,0xe6,0x66,0x00,0x00,0x1a,0x85};
	uint8_t before_flip[9] = {0};
//	uint8_t after_flip[9] = { 0 };
	hamming7264_encode(test, before_flip);

//	// declare data
	float write_first_data = 123.45;
	uint32_t write_second_data = 6789;

	printf("This is the data that we want to store. %f, %u\n", write_first_data,
			(unsigned int) write_second_data);

	//encode data and write to fram
	FRAM_Encode_Write_Block(&Fram, 0, (uint32_t*) &write_first_data,
			&write_second_data);

//	uint8_t read_data = 0;
//	FRAM_Seq_Read(&Fram, 0, before_flip, 9);

	printf("This is the data after we encode.            0x");
	for (int i = 0; i < 9; i++) {
		printf("%x", before_flip[i]);
	}
	printf("\n");
	// read -> flip 1 bit of data -> write
//	FRAM_Read(&Fram, 2, &read_data);
//	read_data ^= 0x08;
//	FRAM_Write(&Fram, 2, &read_data);
//	FRAM_Seq_Read(&Fram, 0, after_flip, 9);
	before_flip[2] ^= 0x08;
	printf("This is the encode data after we flip 1 bit. 0x");
	for (int i = 0; i < 9; i++) {
		printf("%x", before_flip[i]);
	}
	printf("\n");
	//read -> decode
	FRAM_Encode_Read_Block(&Fram, 0, 0, (uint32_t*) &read_first_data);
	FRAM_Encode_Read_Block(&Fram, 0, 1, &read_second_data);
	printf("This is the data after we decode. %f, %u\n", write_first_data,
			(unsigned int) write_second_data);

//	uint8_t base_data[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
//	uint8_t base_data_plus[9] = { 0 };
//
//	HAL_GPIO_WritePin(SPI6_CS_GPIO_Port, SPI6_CS_Pin, 0);
//	hamming7264_encode(base_data, base_data_plus);
//	HAL_GPIO_WritePin(SPI6_CS_GPIO_Port, SPI6_CS_Pin, 1);
//	HAL_Delay(1);
//	final_ans[1] = (final_ans[1] ^ 0x40);
//	HAL_GPIO_WritePin(SPI6_CS_GPIO_Port, SPI6_CS_Pin, 0);
//	hamming7264_decode(base_data_plus, final_ans);
//	HAL_GPIO_WritePin(SPI6_CS_GPIO_Port, SPI6_CS_Pin, 1);
//	HAL_Delay(1);
//	HAL_GPIO_WritePin(SPI6_CS_GPIO_Port, SPI6_CS_Pin, 0);
//	FRAM_Encode_Write(&Fram, 1, base_data);
//	HAL_GPIO_WritePin(SPI6_CS_GPIO_Port, SPI6_CS_Pin, 1);
//	HAL_Delay(1);
//	uint8_t data_buffff = 0;
//	FRAM_Read(&Fram, 2, &data_buffff);
//	data_buffff = data_buffff ^ 0x80;
//	FRAM_Write(&Fram, 2, &data_buffff);
//	HAL_Delay(1);
//	HAL_GPIO_WritePin(SPI6_CS_GPIO_Port, SPI6_CS_Pin, 0);
//	FRAM_Decode_Read(&Fram, 1, final_ans);
//	HAL_GPIO_WritePin(SPI6_CS_GPIO_Port, SPI6_CS_Pin, 1);
//	printf("test");
//	for (int i = 0; i < 8; i++) {
//		printf("%d", final_ans[i]);
//	}

//	// fame's check method
//	printf("start\n");
//	uint8_t famefame_dataword[8] = {3,2,3,2,4,1,2,3};
//	uint8_t famefame_codeword[9] = {0};
//	uint8_t imposter[9] = {0};
//	hamming7264_encode(famefame_dataword, famefame_codeword);
//	memcpy(imposter, famefame_codeword, 9);
//	famefame_codeword[2] ^= 0x01;
//	for (int i = 0; i < 910; i++){
//		FRAM_Seq_Write(&Fram, (i*9), famefame_codeword, 9);
//	}
//
//	uint8_t fuckfuck[8190] = {0};
//	uint8_t *addres_boy = fuckfuck;
//	uint8_t final_ans[8] = {0};
//	HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, 1);
//	HAL_GPIO_WritePin(SPI6_CS_GPIO_Port, SPI6_CS_Pin, 0);
////	for (int i = 0; i < 910; i++){
////		FRAM_Decode_Read(&Fram, (i*9), final_ans);
////	}
//	FRAM_Seq_Read(&Fram, 0, fuckfuck, 8190);
//	uint8_t result_fck = 0;
//	for (int i = 0; i < 910; i++){
//		result_fck = hamming7264_decode(addres_boy, final_ans);
//		addres_boy += 9;
//		if (result_fck == 1){
//			hamming7264_encode(final_ans, addres_boy);
//		}
//	}
//	FRAM_Seq_Write(&Fram, 0, fuckfuck, 8190);
//	HAL_GPIO_WritePin(SPI6_CS_GPIO_Port, SPI6_CS_Pin, 1);
//	printf("final ans = ");
//	for(int i = 0; i <8;i++){
//		printf("%d", final_ans[i]);
//	}
//	printf("\n");

//	Check All Memory

//	printf("\n\n\n");
//	#define block_count 20
//	float write_first_data_B = 123.45345;
//	uint32_t write_second_data_B = 64891;
//	HAL_Delay(5);
//	for (uint16_t i = 0; i < block_count; i++) {
//		FRAM_Encode_Write_Block(&Fram, i, (uint32_t*) &write_first_data_B,
//				&write_second_data_B);
//	}
//
//	uint8_t before_flip_20_block[9 * block_count] = { 0 };
//	uint8_t after_flip_20_block[9 * block_count] = { 0 };
//	uint8_t before_Scrubbing_20_block[9 * block_count] = { 0 };
//	uint8_t after_Scrubbing_20_block[9 * block_count] = { 0 };
//
//	HAL_GPIO_WritePin(SPI6_CS_GPIO_Port, SPI6_CS_Pin, 0);
//	FRAM_Seq_Read(&Fram, 0, before_flip_20_block, 9 * block_count);
//	HAL_GPIO_WritePin(SPI6_CS_GPIO_Port, SPI6_CS_Pin, 1);
//	HAL_Delay(1);
//
//	memcpy(after_flip_20_block, before_flip_20_block, 9 * block_count);
//	for (uint16_t i = 0; i < block_count; i++) {
//		after_flip_20_block[(i * 9) + (TIM7->CNT % 8)] ^= (TIM7->CNT % 255);
//		HAL_Delay(2);
//	}
//
//	HAL_GPIO_WritePin(SPI6_CS_GPIO_Port, SPI6_CS_Pin, 0);
//	FRAM_Seq_Write(&Fram, 0, after_flip_20_block, 9 * block_count);
//	HAL_GPIO_WritePin(SPI6_CS_GPIO_Port, SPI6_CS_Pin, 1);
//	HAL_Delay(1);
//
//	FRAM_Seq_Read(&Fram, 0, before_Scrubbing_20_block, 9 * block_count);
//
//	HAL_GPIO_WritePin(SPI6_CS_GPIO_Port, SPI6_CS_Pin, 0);
//	FRAM_Scrubbing(&Fram, block_count);
//	HAL_GPIO_WritePin(SPI6_CS_GPIO_Port, SPI6_CS_Pin, 1);
//	HAL_Delay(1);
//
//	FRAM_Seq_Read(&Fram, 0, after_Scrubbing_20_block, 9 * block_count);
//
//	for (uint16_t i = 0; i < (9 * block_count); i++) {
//		if (before_flip_20_block[i] == after_Scrubbing_20_block[i]) {
//			if (before_flip_20_block[i] != after_flip_20_block[i]) {
//				printf("0x%x\t0x%x\t0x%x\t0x%x  <--- Flip \n",
//						before_flip_20_block[i], after_Scrubbing_20_block[i],
//						before_Scrubbing_20_block[i], after_flip_20_block[i]);
//			} else {
//				printf("0x%x\t0x%x\t0x%x\t0x%x \n", before_flip_20_block[i],
//						after_Scrubbing_20_block[i],
//						before_Scrubbing_20_block[i], after_flip_20_block[i]);
//
//			}
//		} else {
//			printf("0x%x\t0x%x\t0x%x\t0x%x ---->Fail!!<---- \n",
//					before_flip_20_block[i], after_Scrubbing_20_block[i],
//					before_Scrubbing_20_block[i], after_flip_20_block[i]);
//		}
//		if (i % 9 == 8) {
//			printf("%d ----------------------------------\n", i);
//		}
//	}
}

PUTCHAR_PROTOTYPE {
	/* Place your implementation of fputc here */
	/* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
	HAL_UART_Transmit(&huart3, (uint8_t*) &ch, 1, 1);

	return ch;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim == &htim7) {
		_micro += 65535;
	}
}

uint64_t micro(){
	return _micro + TIM7->CNT;
}
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
	while (1) {
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
