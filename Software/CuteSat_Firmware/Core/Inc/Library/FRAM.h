/*
 * FRAM.h
 *
 *  Created on: Nov 20, 2021
 *      Author: fames
 */

#ifndef INC_FRAM_H_
#define INC_FRAM_H_

// include stm32h7 driver
#include "stm32h7xx.h"
#include "Library/Logging.h"
#include <string.h>

/*
 * DEFINES STH
 */

// FRAM OPCODE
#define FRAM_WREN	0x06
#define FRAM_WRDI	0x04
#define FRAM_RDSR	0x05
#define FRAM_WRSR	0x01
#define FRAM_READ	0x03
#define FRAM_WRITE	0x02
#define FRAM_RDID	0x9F

/*
 * FRAM struct
 */
typedef struct {
	SPI_HandleTypeDef *spiHandle;
	GPIO_TypeDef *cs_port;
	uint16_t cs_pin;
	uint32_t device_id;
	uint8_t is_connect;
} FRAM;


/*
 * Function
 */

uint8_t FRAM_Initialise(FRAM *dev, SPI_HandleTypeDef *spiHandle, GPIO_TypeDef *cs_port, uint16_t cs_pin);
HAL_StatusTypeDef FRAM_Write(FRAM *dev, uint16_t addr, uint8_t *data);
HAL_StatusTypeDef FRAM_Read(FRAM *dev, uint16_t addr,uint8_t *data);
HAL_StatusTypeDef FRAM_Seq_Write(FRAM *dev, uint16_t addr, uint8_t *data, uint16_t data_size);
HAL_StatusTypeDef FRAM_Seq_Read(FRAM *dev, uint16_t addr,uint8_t *data, uint16_t data_size);
HAL_StatusTypeDef FRAM_Write_Status(FRAM *dev, uint8_t wpen,uint8_t bp);
HAL_StatusTypeDef FRAM_Read_Status(FRAM *dev, uint8_t *data);
HAL_StatusTypeDef FRAM_Lock(FRAM *dev);
HAL_StatusTypeDef FRAM_Unlock(FRAM *dev);
void FRAM_Error_Handle(FRAM *dev,HAL_StatusTypeDef respond);

#endif /* INC_FRAM_H_ */
