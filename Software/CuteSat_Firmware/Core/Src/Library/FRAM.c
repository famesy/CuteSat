/*
 * FRAM.c
 *
 *  Created on: Nov 20, 2021
 *      Author: fames
 */
#include <Library/FRAM.h>

uint8_t FRAM_Initialise(FRAM *dev, SPI_HandleTypeDef *spiHandle, GPIO_TypeDef *cs_port, uint16_t cs_pin){
	dev->spiHandle = spiHandle;
	dev->cs_port = cs_port;
	dev->cs_pin = cs_pin;
	dev->device_id = 0x00000000;
	dev->is_connect = 2;

	uint8_t sent_data[1] = {FRAM_RDID};
	uint8_t recieve_data[4] = {0};
	HAL_SPI_Transmit(dev->spiHandle, sent_data, 1, 100);
	HAL_StatusTypeDef rep = HAL_SPI_Receive(dev->spiHandle, recieve_data, 4, 100);
	memcpy(&(dev->device_id), recieve_data ,sizeof(dev->device_id));
	FRAM_Write_Status(dev, 1, 0);
	FRAM_Error_Handle(dev, rep);
	if (((dev->device_id) & 0xFFFF0000) == 0x047F0000){
		return 1; //Fujitsu manufacturer and right continuation code
	}
	return 0;
}

HAL_StatusTypeDef FRAM_Lock(FRAM *dev){
	uint8_t buf[1] = {FRAM_WRDI};
//	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, 0);
	HAL_StatusTypeDef state = HAL_SPI_Transmit(dev->spiHandle, buf, 1, 100);
//	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, 1);
	FRAM_Error_Handle(dev, state);
	return state;
}

HAL_StatusTypeDef FRAM_Unlock(FRAM *dev){
	uint8_t buf[1] = {FRAM_WREN};
//	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, 0);
	HAL_StatusTypeDef state = HAL_SPI_Transmit(dev->spiHandle, buf, 1, 100);
	FRAM_Error_Handle(dev, state);
//	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, 1);
	return state;
}

HAL_StatusTypeDef FRAM_Write(FRAM *dev, uint16_t addr, uint8_t *data){
	uint8_t buf[4] = {FRAM_WRITE, (uint8_t)(addr >> 8), (uint8_t)(addr), *data};
	FRAM_Unlock(dev);
//	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, 0);
	HAL_StatusTypeDef state = HAL_SPI_Transmit(dev->spiHandle, buf, 4, 100);
//	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, 1);
	FRAM_Error_Handle(dev, state);
	return state;
}

HAL_StatusTypeDef FRAM_Read(FRAM *dev, uint16_t addr,uint8_t *data){
	uint8_t buf[3] = {FRAM_READ, (uint8_t)(addr >> 8), (uint8_t)(addr)};
//	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, 0);
	HAL_SPI_Transmit(dev->spiHandle, buf, 3, 100);
	HAL_StatusTypeDef state = HAL_SPI_Receive(dev->spiHandle, (uint8_t *)data, 1, 100);
	FRAM_Error_Handle(dev, state);
//	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, 1);
	return state;
}

HAL_StatusTypeDef FRAM_Seq_Write(FRAM *dev, uint16_t addr, uint8_t *data, uint16_t data_size){
	uint8_t buf[3] = {0};
	buf[0] = FRAM_WRITE;
	buf[1] = (uint8_t)(addr >> 8);
	buf[2] = (uint8_t)(addr);
	FRAM_Unlock(dev);
//	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, 0);
	HAL_StatusTypeDef state = HAL_SPI_Transmit(dev->spiHandle, buf, 3, 100);
	state = HAL_SPI_Transmit(dev->spiHandle, data, data_size, 100);
	FRAM_Error_Handle(dev, state);
//	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, 1);
	return state;
}

HAL_StatusTypeDef FRAM_Seq_Read(FRAM *dev, uint16_t addr,uint8_t *data, uint16_t data_size){
	uint8_t buf[3] = {FRAM_READ, (uint8_t)(addr >> 8), (uint8_t)(addr)};
//	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, 0);
	HAL_SPI_Transmit(dev->spiHandle, buf, 3, 100);
	HAL_StatusTypeDef state = HAL_SPI_Receive(dev->spiHandle, (uint8_t *) data, data_size, 100);
	FRAM_Error_Handle(dev, state);
//	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, 1);
	return state;
}

HAL_StatusTypeDef FRAM_Write_Status(FRAM *dev, uint8_t wpen,uint8_t bp){
	uint8_t status = 0x00;
	if (wpen > 1){wpen = 1;}
	if (bp > 3){bp = 3;}
	status = status + (bp << 2);
	status = status + (wpen << 7);
	uint8_t buf[2] = {FRAM_WRSR, status};
	FRAM_Unlock(dev);
//	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, 0);
	HAL_StatusTypeDef state = HAL_SPI_Transmit(dev->spiHandle, buf, 2, 100);
	FRAM_Error_Handle(dev, state);
//	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, 1);
	return state;
}

HAL_StatusTypeDef FRAM_Read_Status(FRAM *dev, uint8_t *data){
	uint8_t buf[1] = {FRAM_RDSR};
//	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, 0);
	HAL_SPI_Transmit(dev->spiHandle, buf, 1, 100);
	HAL_StatusTypeDef state = HAL_SPI_Receive(dev->spiHandle, data, 1, 100);
	FRAM_Error_Handle(dev, state);
//	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, 1);
	return state;
}

void FRAM_Error_Handle(FRAM *dev,HAL_StatusTypeDef respond){
	if ((respond == HAL_OK) && (dev->is_connect == 2)){
				uint8_t message[40] = "FRAM initializes successfully.";
				SD_Card_Write_Log(LOG_INFO, message, strlen((char *)message));
				dev->is_connect = 1;
	}
	else if ((respond != HAL_OK) && (dev->is_connect == 2)){
		uint8_t message[40] = "FRAM initialization fails.";
		SD_Card_Write_Log(LOG_ERROR, message, strlen((char *)message));
		dev->is_connect = 0;
	}
	else if ((respond == HAL_OK) && (dev->is_connect == 0)){
		uint8_t message[40] = "connect with FRAM successfully.";
		SD_Card_Write_Log(LOG_INFO, message, strlen((char *)message));
		dev->is_connect = 1;
	}
	else if ((respond != HAL_OK) && (dev->is_connect == 1)){
		uint8_t message[40] = "can't communicate with FRAM.";
		SD_Card_Write_Log(LOG_ERROR, message, strlen((char *)message));
		dev->is_connect = 0;
	}
}


