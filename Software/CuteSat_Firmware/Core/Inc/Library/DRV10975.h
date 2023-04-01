/*
 * DRV10975.h
 *
 *  Created on: Mar 21, 2022
 *      Author: fame
 */

#ifndef INC_LIBRARY_DRV10975_H_
#define INC_LIBRARY_DRV10975_H_

/*
 * Include
 */
#include "stm32h7xx_hal.h"
#include "math.h"
#include "i2c.h"

/*
 * define
 */
#define DRV10975_SpeedCtrl1		0x00
#define DRV10975_SpeedCtrl2		0x01
#define DRV10975_DevCtrl		0x02
#define DRV10975_EECtrl			0x03
#define DRV10975_Status			0x10
#define DRV10975_MotorSpeed1	0x11
#define DRV10975_MotorSpeed2	0x12
#define DRV10975_MotorPeriod1	0x13
#define DRV10975_MotorPeriod2	0x14
#define DRV10975_MotorKt1		0x15
#define DRV10975_MotorKt2		0x16
#define DRV10975_MotorCurrent1	0x17
#define DRV10975_MotorCurrent2	0x18
#define DRV10975_IPDPosition	0x19
#define DRV10975_SupplyVoltage	0x1A
#define DRV10975_SpeedCmd		0x1B
#define DRV10975_spdCmdBuffer	0x1C
#define DRV10975_FaultCode		0x1E
#define DRV10975_MotorParam1	0x20
#define DRV10975_MotorParam2	0x21
#define DRV10975_MotorParam3	0x22
#define DRV10975_SysOpt1		0x23
#define DRV10975_SysOpt2		0x24
#define DRV10975_SysOpt3		0x25
#define DRV10975_SysOpt4		0x26
#define DRV10975_SysOpt5		0x27
#define DRV10975_SysOpt6		0x28
#define DRV10975_SysOpt7		0x29
#define DRV10975_SysOpt8		0x2A
#define DRV10975_SysOpt9		0x2B

/*
 * struct
 */
typedef struct {
	uint8_t over_temperature;
	uint8_t sleep_and_standby;
	uint8_t over_current;
	uint8_t motor_lock;
} DRV10975_StatusTypeDef;

typedef struct {
	uint8_t closeloop_stuck;
	uint8_t openloop_stuck;
	uint8_t no_motor;
	uint8_t kt_abnormal;
	uint8_t speed_abnormal;
	uint8_t current_limit_lock;
} DRV10975_FaultTypeDef;

typedef struct {
	uint8_t is_connect;
	double motor_speed;
	double motor_kt;
	double motor_period;
	double motor_current;
	double motor_voltage;
	uint8_t address;
	I2C_HandleTypeDef *i2cHandle;
	GPIO_TypeDef *dir_gpio_port;
	uint16_t dir_gpio_pin;
	TIM_HandleTypeDef *tim_handle;
	uint32_t tim_channel;
	DRV10975_StatusTypeDef status;
	DRV10975_FaultTypeDef fault;
} DRV10975;

void DRV10975_Init(DRV10975 *dev,I2C_HandleTypeDef *i2c_handle, TIM_HandleTypeDef *tim_handle, uint32_t tim_channel, GPIO_TypeDef *gpio_port,uint16_t gpio_pin);
void DRV10975_Config(DRV10975 *dev);
void DRV10975_Read_Speed(DRV10975 *dev);
void DRV10975_Read_Period(DRV10975 *dev);
void DRV10975_Read_Kt(DRV10975 *dev);
void DRV10975_Read_Current(DRV10975 *dev);
void DRV10975_Read_Voltage(DRV10975 *dev);
void set_pwm(TIM_HandleTypeDef *tim_pwm, uint32_t tim_channel, double freq,
		double duty_cycle);
void DRV10975_PWM_Set_Speed(DRV10975 *dev,int32_t speed);
void DRV10975_I2C_Set_Speed(DRV10975 *dev, int32_t speed, uint8_t dir);
void DRV10975_Error_Handle(DRV10975 *dev,HAL_StatusTypeDef respond);

#endif /* INC_LIBRARY_DRV10975_H_ */
