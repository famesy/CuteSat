/*
 * DRV10975.c
 *
 *  Created on: Mar 21, 2022
 *      Author: fame
 */

#include "Library/DRV10975.h"
#include  "Library/Logging.h"

void DRV10975_Init(DRV10975 *dev,I2C_HandleTypeDef *i2c_handle, TIM_HandleTypeDef *tim_handle, uint32_t tim_channel, GPIO_TypeDef *gpio_port,uint16_t gpio_pin){
	dev->address = 0xA4;
	dev->i2cHandle = i2c_handle;
	dev->tim_handle = tim_handle;
	dev->tim_channel = tim_channel;
	dev->dir_gpio_port = gpio_port;
	dev->dir_gpio_pin = gpio_pin;
	dev->is_connect = 2;
	HAL_TIM_PWM_Start(dev->tim_handle, dev->tim_channel);
	uint8_t EECtrl[1] = { 0x10 };
	HAL_StatusTypeDef rep = HAL_I2C_Mem_Read(&hi2c2, 0xA4, 0x03, I2C_MEMADD_SIZE_8BIT, EECtrl, 1,
					100);
	DRV10975_Error_Handle(dev, rep);
}

void DRV10975_Config(DRV10975 *dev){
	//set SLDATA to 1
	uint8_t EECtrl[1] = { 0x40 };
	HAL_I2C_Mem_Write(&hi2c2, 0xA4, 0x03, I2C_MEMADD_SIZE_8BIT, EECtrl, 1, 100);
	uint8_t data_jaa[1] = { 0 };
	data_jaa[0] = 0x68;
	HAL_I2C_Mem_Write(&hi2c2, 0xA4, 0x20, I2C_MEMADD_SIZE_8BIT, data_jaa, 1,
			100);
	data_jaa[0] = 0x1F;
	HAL_I2C_Mem_Write(&hi2c2, 0xA4, 0x21, I2C_MEMADD_SIZE_8BIT, data_jaa, 1,
			100);
	data_jaa[0] = 0x3A;
	HAL_I2C_Mem_Write(&hi2c2, 0xA4, 0x22, I2C_MEMADD_SIZE_8BIT, data_jaa, 1,
			100);
	data_jaa[0] = 0xF;
	HAL_I2C_Mem_Write(&hi2c2, 0xA4, 0x23, I2C_MEMADD_SIZE_8BIT, data_jaa, 1,
			100);
	data_jaa[0] = 0x47;
	HAL_I2C_Mem_Write(&hi2c2, 0xA4, 0x24, I2C_MEMADD_SIZE_8BIT, data_jaa, 1,
			100);
	data_jaa[0] = 0xC0;
	HAL_I2C_Mem_Write(&hi2c2, 0xA4, 0x25, I2C_MEMADD_SIZE_8BIT, data_jaa, 1,
			100);
	data_jaa[0] = 0x8F;
	HAL_I2C_Mem_Write(&hi2c2, 0xA4, 0x26, I2C_MEMADD_SIZE_8BIT, data_jaa, 1,
			100);
	data_jaa[0] = 0x9C;
	HAL_I2C_Mem_Write(&hi2c2, 0xA4, 0x27, I2C_MEMADD_SIZE_8BIT, data_jaa, 1,
			100);
	data_jaa[0] = 0x66;
	HAL_I2C_Mem_Write(&hi2c2, 0xA4, 0x28, I2C_MEMADD_SIZE_8BIT, data_jaa, 1,
			100);
	data_jaa[0] = 0x88;
	HAL_I2C_Mem_Write(&hi2c2, 0xA4, 0x29, I2C_MEMADD_SIZE_8BIT, data_jaa, 1,
			100);
	data_jaa[0] = 0xB;
	HAL_I2C_Mem_Write(&hi2c2, 0xA4, 0x2A, I2C_MEMADD_SIZE_8BIT, data_jaa, 1,
			100);
	data_jaa[0] = 0xC;
	HAL_I2C_Mem_Write(&hi2c2, 0xA4, 0x2B, I2C_MEMADD_SIZE_8BIT, data_jaa, 1,
			100);

	// Write 0xB6 to enProgKey
	uint8_t DevCtrl[1] = { 0xB6 };
	HAL_I2C_Mem_Write(&hi2c2, 0xA4, 0x02, I2C_MEMADD_SIZE_8BIT, DevCtrl, 1,
			100);
	// Write eeWrite = 1
	EECtrl[0] = 0x10;
	HAL_I2C_Mem_Write(&hi2c2, 0xA4, 0x03, I2C_MEMADD_SIZE_8BIT, EECtrl, 1, 100);
	EECtrl[0] = 0;
	//wait till eeWrite = 0
	HAL_StatusTypeDef rep = HAL_ERROR;
	while (1) {
		rep = HAL_I2C_Mem_Read(&hi2c2, 0xA4, 0x03, I2C_MEMADD_SIZE_8BIT, EECtrl, 1,
				100);
		if ((EECtrl[0] & 0x10) == 0x00) {
			break;
		}
	}
	DRV10975_Error_Handle(dev, rep);
}

void DRV10975_Read_Speed(DRV10975 *dev){
	uint8_t buf[1] = {0};
	double ans = 0;
	HAL_I2C_Mem_Read(dev->i2cHandle, dev->address, DRV10975_MotorSpeed1, I2C_MEMADD_SIZE_8BIT, buf, 1, 1000);
	ans = (uint16_t)buf[0] << 8;
	HAL_StatusTypeDef rep = HAL_I2C_Mem_Read(dev->i2cHandle, dev->address, DRV10975_MotorSpeed2, I2C_MEMADD_SIZE_8BIT, buf, 1, 1000);
	ans = ((ans + buf[0])/10.0);
	dev->motor_speed = ans;
	DRV10975_Error_Handle(dev, rep);
}

void DRV10975_Read_Period(DRV10975 *dev){
	uint8_t buf[1] = {0};
	double ans = 0;
	HAL_I2C_Mem_Read(dev->i2cHandle, dev->address, DRV10975_MotorPeriod1, I2C_MEMADD_SIZE_8BIT, buf, 1, 1000);
	ans = (uint16_t)buf[0] << 8;
	HAL_StatusTypeDef rep = HAL_I2C_Mem_Read(dev->i2cHandle, dev->address, DRV10975_MotorPeriod2, I2C_MEMADD_SIZE_8BIT, buf, 1, 1000);
	ans = ((ans + buf[0]) * 10.0);
	dev->motor_period = ans;
	DRV10975_Error_Handle(dev, rep);
}

void DRV10975_Read_Kt(DRV10975 *dev){
	uint8_t buf[1] = {0};
	double ans = 0;
	HAL_I2C_Mem_Read(dev->i2cHandle, dev->address, DRV10975_MotorPeriod1, I2C_MEMADD_SIZE_8BIT, buf, 1, 1000);
	ans = (uint16_t)buf[0] << 8;
	HAL_StatusTypeDef rep = HAL_I2C_Mem_Read(dev->i2cHandle, dev->address, DRV10975_MotorPeriod2, I2C_MEMADD_SIZE_8BIT, buf, 1, 1000);
	ans = ((ans + buf[0]) / 2884.0);
	dev->motor_kt = ans;
	DRV10975_Error_Handle(dev, rep);
}

void DRV10975_Read_Current(DRV10975 *dev){
	uint8_t buf[1] = {0};
	uint16_t ans = 0;
	HAL_I2C_Mem_Read(dev->i2cHandle, dev->address, DRV10975_MotorCurrent1, I2C_MEMADD_SIZE_8BIT, buf, 1, 1000);
	ans = (uint16_t)(buf[0] & 0x07) << 8;
	HAL_StatusTypeDef rep = HAL_I2C_Mem_Read(dev->i2cHandle, dev->address, DRV10975_MotorCurrent2, I2C_MEMADD_SIZE_8BIT, buf, 1, 1000);
	ans = ans | ((uint16_t)buf[0] & 0xFF);
	if (ans >= 1023){
		dev->motor_current = (3.0 * (ans - 1023))/512.0;
	}
	else {
		dev->motor_current = (3.0 * ans)/512.0;
	}
	DRV10975_Error_Handle(dev, rep);
//	dev->motor_current = ans;
}

void DRV10975_Read_Voltage(DRV10975 *dev){
//	uint8_t buf[1] = {0};
//	HAL_I2C_Mem_Read(dev->i2cHandle, dev->address, DRV10975_SupplyVoltage, I2C_MEMADD_SIZE_8BIT, buf, 1, 1000);
//	dev->voltage = buf[0] * 22.8 / 256.0;
	uint8_t voltage_buf = 0;
	HAL_StatusTypeDef rep = HAL_I2C_Mem_Read(dev->i2cHandle, dev->address, 0x1A, I2C_MEMADD_SIZE_8BIT, &voltage_buf, 1, 1000);
	DRV10975_Error_Handle(dev, rep);
	dev->motor_voltage = voltage_buf * 22.8 / 256.0;
}

void set_pwm(TIM_HandleTypeDef *tim_pwm, uint32_t tim_channel, double freq,
		double duty_cycle) {
	uint16_t ARR_value = (1000000 / freq) -1; //1000000 come from 240MHz/240
	uint16_t CCRx_value = (ARR_value * duty_cycle) - 1;
	if (duty_cycle == 1.0) {
		CCRx_value = 0;
	}
	__HAL_TIM_SET_AUTORELOAD(tim_pwm, ARR_value);
	__HAL_TIM_SET_COMPARE(tim_pwm, tim_channel, CCRx_value);
}

void DRV10975_PWM_Set_Speed(DRV10975 *dev,int32_t speed){
	//speed = {-100, 100}
	if (speed < 0){
		HAL_GPIO_WritePin(dev->dir_gpio_port, dev->dir_gpio_pin, GPIO_PIN_SET);
		if (speed < -100){
			speed = -100;
		}
		speed = speed * -1;
	}
	else {
		HAL_GPIO_WritePin(dev->dir_gpio_port, dev->dir_gpio_pin, GPIO_PIN_RESET);
		if (speed > 100){
			speed = 100;
		}
	}
	set_pwm(dev->tim_handle, dev->tim_channel, 25000, speed/100.0f);
}

void DRV10975_I2C_Set_Speed(DRV10975 *dev, int32_t speed, uint8_t dir){
	//Disable sleepDis (sleepDis = 1)
	uint8_t EECtrl[1] = { 0x80 };
	HAL_I2C_Mem_Write(&hi2c2, 0xA4, 0x03, I2C_MEMADD_SIZE_8BIT, EECtrl, 1, 100);
	//Disable Write OverRide and write MSB First
	uint8_t SpeedCtrl_MSB[1] = { (speed >> 8) | 0x80 };
	HAL_I2C_Mem_Write(&hi2c2, 0xA4, 0x01, I2C_MEMADD_SIZE_8BIT, SpeedCtrl_MSB,
			1, 100);
	//write LSB
	uint8_t SpeedCtrl_LSB[1] = { speed & 0xFF };
	HAL_StatusTypeDef rep = HAL_I2C_Mem_Write(&hi2c2, 0xA4, 0x00, I2C_MEMADD_SIZE_8BIT, SpeedCtrl_LSB,
			1, 100);
	DRV10975_Error_Handle(dev, rep);
	HAL_GPIO_WritePin(D2_DIR_GPIO_Port, D2_DIR_Pin, dir);
}

void DRV10975_Error_Handle(DRV10975 *dev,HAL_StatusTypeDef respond){
	if ((respond == HAL_OK) && (dev->is_connect == 2)){
			uint8_t message[40] = "DRV10975 initializes successfully.";
			SD_Card_Write_Log(LOG_INFO, message, strlen((char *)message));
			dev->is_connect = 1;
	}
	else if ((respond != HAL_OK) && (dev->is_connect == 2)){
		uint8_t message[40] = "DRV10975 initialization fails.";
		SD_Card_Write_Log(LOG_ERROR, message, strlen((char *)message));
		dev->is_connect = 0;
	}
	else if ((respond == HAL_OK) && (dev->is_connect == 0)){
		uint8_t message[40] = "connect with DRV10975 successfully.";
		SD_Card_Write_Log(LOG_ERROR, message, strlen((char *)message));
		dev->is_connect = 1;
	}
	else if ((respond != HAL_OK) && (dev->is_connect == 1)){
		uint8_t message[40] = "can't communicate with DRV10975.";
		SD_Card_Write_Log(LOG_ERROR, message, strlen((char *)message));
		dev->is_connect = 0;
	}
}
