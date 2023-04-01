/*
 * AS5047U.h
 *
 *  Created on: Jan 24, 2022
 *      Author: Thansak Pongpaket
 */

#ifndef INC_AS5047U_H_
#define INC_AS5047U_H_

/*
 * Include Driver H7
 */
#include "stm32h7xx.h"
#include "Library/Logging.h"
/*
 * 	  --> Register Map <--
 *     Volatile Registers (Read Only Register)
 */
#define ENC_NOP 			0x0000
#define	ENC_ERRFL			0x0001
#define	ENC_PROG			0x0003 // (R/W)
#define	ENC_DIA				0x3FF5
#define	ENC_AGC				0x3FF9
#define	ENC_Sin		 		0x3FFA
#define	ENC_Cos				0x3FFB
#define	ENC_VEL				0x3FFC
#define	ENC_MAG				0x3FFD
#define	ENC_ANGLEUNC		0x3FFE
#define	ENC_ANGLECOM		0x3FFF
#define	ENC_ECC_Checksum	0x00D1

/*
 * Non-Volatile Registers (OTP)
 */
#define	ENC_DISABLE			0x0015
#define	ENC_ZPOSM			0x0016
#define	ENC_ZPOSL			0x0017
#define	ENC_SETTINGS1		0x0018
#define	ENC_SETTINGS2		0x0019
#define	ENC_SETTINGS3		0x001A
#define	ENC_ECC				0x001B

/*
 *
 */

typedef struct {
	uint8_t CORDIC_Overflow;
	uint8_t Offset_Compensation_Not_Finished;
	uint8_t Watchdog_Error;
	uint8_t CRC_Error;
	uint8_t Command_Error;
	uint8_t Framing_Error;
	uint8_t P2ram_Error;
	uint8_t P2ram_Warning;
	uint8_t MagHalf;
	uint8_t Agc_warning;
} AS5047UError;

typedef struct {
	SPI_HandleTypeDef *hspiHandle;
	CRC_HandleTypeDef *hcrcHandle;
	GPIO_TypeDef *CSGPIOTypedef;
	uint16_t CSGPIOPin;
	uint16_t Position;
	AS5047UError Error_Status;
	uint8_t is_connect;
	float Offset;
} AS5047U;




/*
 * Function
 */
float EncPulse2Rad_Read(AS5047U *Enc,uint8_t inv_dir);

void AS5047U_init(AS5047U *dev, SPI_HandleTypeDef *hspiHandle, GPIO_TypeDef *CSGPIOTypedef, CRC_HandleTypeDef *hcrcHandle, uint16_t CSGPIOPin, float offset);
void AS5047U_Write(AS5047U *dev,uint16_t Register_Address, uint16_t Data);
HAL_StatusTypeDef AS5047U_Read(AS5047U *dev,uint16_t Register_Address, uint16_t *Data);
uint16_t AS5047U_Position_Highspeed_Read(AS5047U *dev,uint8_t dir);
int16_t AS5047U_Speed_Highspeed_Read(AS5047U *dev);
HAL_StatusTypeDef AS5047U_Read_Error(AS5047U *dev);
void AS5047U_Error_Handle(AS5047U *dev,HAL_StatusTypeDef respond);

#endif /* INC_AS5047U_H_ */
