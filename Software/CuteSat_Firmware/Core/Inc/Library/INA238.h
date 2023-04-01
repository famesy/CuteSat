/*
 * INA238.h
 *
 *  Created on: Nov 24, 2021
 *      Author: hue
 */

#ifndef INC_INA238_H_
#define INC_INA238_H_

#include "stm32h7xx.h"
#include "Logging.h"

/*
 * Define Register Map
 * Register Size = 2 bytes
 */
#define INA238_CONFIG 			0x00
#define INA238_ADC_CONFIG 		0x01
#define INA238_SHUNT_CAL 		0x02
#define INA238_VSHUNT 			0x04
#define INA238_VBUS 			0x05
#define INA238_DIETEMP 			0x06
#define INA238_CURRENT 			0x07
#define INA238_POWER 			0x08
#define INA238_DIAG_ALRT 		0x0B
#define INA238_SOVL 			0x0C
#define INA238_SUVL 			0x0D
#define INA238_BOVL 			0x0E
#define INA238_BUVL 			0x0F
#define INA238_TEMP_LIMIT 		0x10
#define INA238_PWR_LIMIT 		0x11
#define INA238_MANUFACTURER_ID 	0x3E
#define INA238_DEVICE_ID 		0x3F

/*
 * Device Struct
 */

/*
 * INA238 Error need to change how to represent error
 */
typedef struct {
	uint8_t MATHOF;
	uint8_t TMPOL;
	uint8_t SHNTOL;
	uint8_t SHNTUL;
	uint8_t BUSOL;
	uint8_t BUSUL;
	uint8_t POL;
	uint8_t MEMSTAT;
} ErrorStruct;

typedef struct {
	I2C_HandleTypeDef *i2cHandle;
	uint8_t address;
	float shunt_voltage;
	float current;
	float power;
	float bus_voltage;
	float temp;
	float Current_LSB;
	uint8_t is_connect;
	uint16_t SHUNT_CAL;
	uint8_t ADCRANGE;
	uint16_t manufacturer_id;
	uint16_t device_id;
	uint8_t device_rev;
	ErrorStruct error;
} INA238;

/*
 * Define Function
 */


HAL_StatusTypeDef i2c_mem_write(INA238 *dev, uint8_t mem_adress, uint16_t *data);
HAL_StatusTypeDef i2c_mem_read(INA238 *dev, uint8_t mem_adress, uint16_t *data);
void INA238_init(INA238 *dev, I2C_HandleTypeDef *i2cHandle, uint8_t address);
void INA238_calibrate(INA238 *dev, uint8_t ADCRANGE,
		float r_shunt);
void INA238_reset(INA238 *dev);
void INA238_set_conv_delay(INA238 *dev, uint16_t step);
void INA238_set_ADCRANGE(INA238 *dev, uint16_t range);
void INA238_set_mode(INA238 *dev, uint16_t mode);
void INA238_set_bus_voltage_cnvtime(INA238 *dev, uint16_t conv_level);
void INA238_set_shunt_voltage_cnvtime(INA238 *dev, uint16_t conv_level);
void INA238_set_temp_cnvtime(INA238 *dev, uint16_t conv_level);
void INA238_set_average_count(INA238 *dev, uint16_t count);
void INA238_read_shunt_voltage(INA238 *dev);
void INA238_read_bus_voltage(INA238 *dev);
void INA238_read_temp(INA238 *dev);
void INA238_read_current(INA238 *dev);
void INA238_read_power(INA238 *dev);
void INA238_set_minmax_shunt_voltage(INA238 *dev, int16_t overvoltage_step,
		int16_t undervoltage_step);
void INA238_set_minmax_bus_voltage(INA238 *dev, uint16_t overvoltage_step,
		uint16_t undervoltage_step);
void INA238_set_temp_overlimit(INA238 *dev, int16_t overlimit_step);
void INA238_set_power_overlimit(INA238 *dev, uint16_t overlimit_step);
void INA238_read_manufacturer_id(INA238 *dev);
void INA238_read_device_id(INA238 *dev);
void INA238_set_alert_latch(INA238 *dev, uint8_t mode);
void INA238_set_conv_flag(INA238 *dev, uint8_t mode);
void INA238_set_using_avg_comparing_alert(INA238 *dev, uint8_t mode);
void INA238_set_fault_pin_polarity(INA238 *dev, uint8_t logic);
void INA238_read_error(INA238 *dev);
void INA238_read_all(INA238 *dev);
void INA238_Error_Handle(INA238 *dev,HAL_StatusTypeDef respond);

#endif /* INC_INA238_H_ */
