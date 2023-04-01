/*
 * TMP75.h
 *
 *  Created on: May 15, 2022
 *      Author: fame
 */

#ifndef INC_LIBRARY_TMP75_H_
#define INC_LIBRARY_TMP75_H_

#include "stm32h7xx_hal.h"
#include "i2c.h"

#define TMP75_ADDR	0x90
#define FTMP75_TEMP_AD_STEP		0.0625

void TMP75_Init(void);
void Write_Register(uint8_t register_pointer, uint16_t register_value);
void Read_Register(uint8_t register_pointer, uint8_t* receive_buffer);
void TMP75_Read_TempCelsius(float* receive_buffer);

#endif /* INC_LIBRARY_TMP75_H_ */
