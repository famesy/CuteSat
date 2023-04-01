/*
 * INA238.c
 *
 *  Created on: Nov 24, 2021
 *      Author: hue
 */

#include <Library/INA238.h>

HAL_StatusTypeDef i2c_mem_write(INA238 *dev, uint8_t mem_adress, uint16_t *data) {
	/*
	 * only support 2 bytes memory size
	 */
	uint8_t Buffer[2] = {(uint8_t)(0x00FF & (*data>>8)),(uint8_t)(0x00FF & *data)};
	HAL_StatusTypeDef rep = HAL_I2C_Mem_Write(dev->i2cHandle, dev->address, mem_adress,
	I2C_MEMADD_SIZE_8BIT, Buffer, 2, 100);
	INA238_Error_Handle(dev, rep);
	return rep;
}

HAL_StatusTypeDef i2c_mem_read(INA238 *dev, uint8_t mem_adress, uint16_t *data) {
	/*
	 * only support 2 bytes memory size
	 */
	uint8_t Buffer[2];
	HAL_StatusTypeDef rep = HAL_I2C_Mem_Read(dev->i2cHandle, dev->address, mem_adress,
	I2C_MEMADD_SIZE_8BIT, Buffer, 2, 100);
	*data = (uint16_t)Buffer[1] | (uint16_t)Buffer[0] << 8;
	INA238_Error_Handle(dev, rep);
	return rep;
}

/*
 * Very Useful Function!!
 */

void INA238_init(INA238 *dev, I2C_HandleTypeDef *i2cHandle, uint8_t address) {
	dev->i2cHandle = i2cHandle;
	dev->address = address;

	dev->shunt_voltage = 0;
	dev->bus_voltage = 0;
	dev->current = 0;
	dev->power = 0;

	dev->is_connect = 2;

	dev->Current_LSB = 0;
	dev->SHUNT_CAL = 0;

	dev->ADCRANGE = 0;
	INA238_reset(dev);
	INA238_read_manufacturer_id(dev);
	INA238_read_device_id(dev);
	dev->error.MATHOF = 0;
	dev->error.TMPOL = 0;
	dev->error.SHNTOL = 0;
	dev->error.SHNTUL = 0;
	dev->error.BUSOL = 0;
	dev->error.BUSUL = 0;
	dev->error.POL = 0;
	dev->error.MEMSTAT = 0;
}

void INA238_calibrate(INA238 *dev, uint8_t ADCRANGE,
		float r_shunt) {
	//	calculate best ADCRANGE
	/*
	 * ±163.84 mV (ADCRANGE = 0)
	 * ±40.96 mV (ADCRANGE = 1
	 */
	float expected_maximum_current = 0.0;
	if (ADCRANGE > 1){ADCRANGE = 1;}
	if (ADCRANGE == 0){
		expected_maximum_current  = 0.16384f/r_shunt;
	}
	if (ADCRANGE == 1){
		expected_maximum_current  = 0.04096f/r_shunt;
	}
	INA238_set_ADCRANGE(dev, ADCRANGE);
	dev->ADCRANGE = ADCRANGE;
	dev->Current_LSB = expected_maximum_current / 32768.0f;
	/*
	 * SHUNT_CAL MUST NOT EXCEED 32768
	 */
	dev->SHUNT_CAL = 819200000 * r_shunt * dev->Current_LSB;
	if (ADCRANGE == 1){
		dev->SHUNT_CAL = dev->SHUNT_CAL * 4;
	}
	i2c_mem_write(dev, INA238_SHUNT_CAL, &(dev->SHUNT_CAL));
}

void INA238_reset(INA238 *dev) {
	/*
	 * Reset All register to default
	 */
	uint16_t data = 0x8000;
	i2c_mem_write(dev, INA238_CONFIG, &data);
}

/*
 * Setup ADC Function
 */
void INA238_set_conv_delay(INA238 *dev, uint16_t step) {
	/*
	 * 1 step = 2ms
	 * maximum step is 255
	 */
	uint16_t data = 0;
	i2c_mem_read(dev, INA238_CONFIG, &data);
	data = (data & 0xC03F) | (step << 6);
	i2c_mem_write(dev, INA238_CONFIG, &data);
}

void INA238_set_ADCRANGE(INA238 *dev, uint16_t range) {
	/*	Shunt full scale range selection across IN+ and IN–.
	 0h = ±163.84 mV
	 1h = ± 40.96 mV*/
	uint16_t data = 0;
	i2c_mem_read(dev, INA238_CONFIG, &data);
	data = (data & 0xFFEF) | (range << 4);
	i2c_mem_write(dev, INA238_CONFIG, &data);
}

void INA238_set_mode(INA238 *dev, uint16_t mode) {
	/*	0h = Shutdown
	 1h = Triggered bus voltage, single shot
	 2h = Triggered shunt voltage triggered, single shot
	 3h = Triggered shunt voltage and bus voltage, single shot
	 4h = Triggered temperature, single shot
	 5h = Triggered temperature and bus voltage, single shot
	 6h = Triggered temperature and shunt voltage, single shot
	 7h = Triggered bus voltage, shunt voltage and temperature, single
	 shot
	 8h = Shutdown
	 9h = Continuous bus voltage only
	 Ah = Continuous shunt voltage only
	 Bh = Continuous shunt and bus voltage
	 Ch = Continuous temperature only
	 Dh = Continuous bus voltage and temperature
	 Eh = Continuous temperature and shunt voltage
	 Fh = Continuous bus, shunt voltage and temperature*/
	uint16_t data = 0;
	i2c_mem_read(dev, INA238_ADC_CONFIG, &data);
	data = (data & 0x0FFF) | (mode << 12);
	i2c_mem_write(dev, INA238_ADC_CONFIG, &data);
}

void INA238_set_bus_voltage_cnvtime(INA238 *dev, uint16_t conv_level) {
	/*	0 = 50 μs
	 1 = 84 μs
	 2 = 150 μs
	 3 = 280 μs
	 4 = 540 μs
	 5 = 1052 μs
	 6 = 2074 μs
	 7 = 4120 μs*/
	uint16_t data = 0;
	i2c_mem_read(dev, INA238_ADC_CONFIG, &data);
	data = (data & 0xF1FF) | (conv_level << 9);
	i2c_mem_write(dev, INA238_ADC_CONFIG, &data);
}

void INA238_set_shunt_voltage_cnvtime(INA238 *dev, uint16_t conv_level) {
	/*	0 = 50 μs
	 1 = 84 μs
	 2 = 150 μs
	 3 = 280 μs
	 4 = 540 μs
	 5 = 1052 μs
	 6 = 2074 μs
	 7 = 4120 μs*/
	uint16_t data = 0;
	i2c_mem_read(dev, INA238_ADC_CONFIG, &data);
	data = (data & 0xFE3F) | (conv_level << 6);
	i2c_mem_write(dev, INA238_ADC_CONFIG, &data);
}

void INA238_set_temp_cnvtime(INA238 *dev, uint16_t conv_level) {
	/*	0 = 50 μs
	 1 = 84 μs
	 2 = 150 μs
	 3 = 280 μs
	 4 = 540 μs
	 5 = 1052 μs
	 6 = 2074 μs
	 7 = 4120 μs*/
	uint16_t data = 0;
	i2c_mem_read(dev, INA238_ADC_CONFIG, &data);
	data = (data & 0xFFC7) | (conv_level << 3);
	i2c_mem_write(dev, INA238_ADC_CONFIG, &data);
}

void INA238_set_average_count(INA238 *dev, uint16_t count) {
	/*	0 = 1
	 1 = 4
	 2 = 16
	 3 = 64
	 4 = 128
	 5 = 256
	 6 = 512
	 7 = 1024*/
	uint16_t data = 0;
	i2c_mem_read(dev, INA238_ADC_CONFIG, &data);
	data = (data & 0xFFF8) | count;
	i2c_mem_write(dev, INA238_ADC_CONFIG, &data);
}

/*
 * Reading Data Function!!
 */

void INA238_read_shunt_voltage(INA238 *dev) {
	uint16_t data = 0;
	i2c_mem_read(dev, INA238_VSHUNT, &data);
	if (dev->ADCRANGE == 0) {
		dev->shunt_voltage = (int16_t)data * 0.000005f;
	} else {
		dev->shunt_voltage = (int16_t)data * 0.00000125f;
	}
}

void INA238_read_bus_voltage(INA238 *dev) {
	uint16_t data = 0;
	i2c_mem_read(dev, INA238_VBUS, &data);
	dev->bus_voltage = (int16_t)data * 0.003125f;
}

void INA238_read_temp(INA238 *dev) {
	/*
	 * 	return as celsius (value store in dev->temp
	 */
	uint16_t data = 0;
	i2c_mem_read(dev, INA238_DIETEMP, &data);
	dev->temp = (int16_t)((data & 0x8000) | ((data & 0x7FF0) >> 4)) * 0.125f;
}

void INA238_read_current(INA238 *dev) {
	uint16_t data = 0;
	i2c_mem_read(dev, INA238_CURRENT, &data);
	dev->current = (int16_t)data * dev->Current_LSB;
	//return as ampere
}

void INA238_read_power(INA238 *dev) {
	uint32_t data = 0;
//	HAL_I2C_Master_Sequential_Transmit_IT(dev->i2cHandle, dev->address,
//			(uint8_t*) INA238_POWER, 2, I2C_FIRST_FRAME);
//	while (HAL_I2C_GetState(dev->i2cHandle) != HAL_I2C_STATE_READY);
//	HAL_I2C_Master_Sequential_Receive_IT(dev->i2cHandle, dev->address,
//			(uint8_t*) &data, 3, I2C_LAST_FRAME);
	uint8_t Buffer[3];
	HAL_I2C_Mem_Read(dev->i2cHandle, dev->address, INA238_POWER,
		I2C_MEMADD_SIZE_8BIT, Buffer, 3, 100);
	data = ((uint32_t)(Buffer[0])) << 16 | ((uint32_t)(Buffer[1])) << 8 | ((uint32_t)(Buffer[2]));
	dev->power = data * 0.2f * dev->Current_LSB;
}

void INA238_set_minmax_shunt_voltage(INA238 *dev, int16_t overvoltage_step,
		int16_t undervoltage_step) {
	/*
	 * can be positive/negative [−32768, +32767]
	 * 5 μV/LSB when ADCRANGE = 0
	 * 1.25 μV/LSB when ADCRANGE = 1.
	 * overvoltage default value is 0x7FFF
	 * undervoltage default value is 0x8000
	 */
	i2c_mem_write(dev, INA238_SOVL, (uint16_t*) &overvoltage_step);
	i2c_mem_write(dev, INA238_SUVL, (uint16_t*) &undervoltage_step);
}

void INA238_set_minmax_bus_voltage(INA238 *dev, uint16_t overvoltage_step,
		uint16_t undervoltage_step) {
	/* can be positive [0, 32768]
	 * unsigned value
	 * 3.125 mV/LSB
	 * overvoltage default value is 0x7FFF
	 * undervoltage default value is 0x8000
	 */
	//	change to 15 bits value
	overvoltage_step = overvoltage_step & 0x7FFF;
	undervoltage_step = undervoltage_step & 0x7FFF;
	i2c_mem_write(dev, INA238_BOVL, &overvoltage_step);
	i2c_mem_write(dev, INA238_BUVL, &undervoltage_step);
}

void INA238_set_temp_overlimit(INA238 *dev, int16_t overlimit_step) {
	/*
	 * can be positive/negative [−4096, +4095]
	 * 125 m°C/LSB.
	 * overlimit default value is 0xFFFF
	 */
	overlimit_step = (overlimit_step & 0x8000) | ((overlimit_step & 0x7FF0) >> 4);
	i2c_mem_write(dev, INA238_TEMP_LIMIT, (uint16_t*) &overlimit_step);
}

void INA238_set_power_overlimit(INA238 *dev, uint16_t power_lsb) {
	/*
	 * unsigned [0, 65535]
	 * 256 × Power LSB.
	 * overlimit default value is 0x7FF0
	 */
	i2c_mem_write(dev, INA238_PWR_LIMIT, &power_lsb);
}

void INA238_read_manufacturer_id(INA238 *dev) {
	uint16_t data = 0;
	i2c_mem_read(dev, INA238_MANUFACTURER_ID, &data);
	dev->manufacturer_id = data;
}

// dev id reg 17

void INA238_read_device_id(INA238 *dev) {
	uint16_t data = 0;
	i2c_mem_read(dev, INA238_DEVICE_ID, &data);
	dev->device_rev = data & 0x0003;
	dev->device_id = (data >> 3);
}

/*
 *
 *
 *
 *
 *
 *
 * 	Yung mai sed ;((((((((
 *  NOT That useful funciton
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
void INA238_set_alert_latch(INA238 *dev, uint8_t mode) {
	/*
	 * if mode == 0 (auto reset flag)
	 * if mode == 1 (read to clear flag)
	 */
	if (mode > 1){
		mode = 1;
	}
	uint16_t data = 0;
	i2c_mem_read(dev, INA238_DIAG_ALRT, &data);
	data = (data & 0x7FFF) | (mode << 15);
	i2c_mem_write(dev, INA238_DIAG_ALRT, &data);
}

void INA238_set_conv_flag(INA238 *dev, uint8_t mode) {
	/*
	 * if mode == 0 Disable conversion ready flag on ALERT pin
	 * if mode == 1 Enable conversion ready flag on ALERT pin
	 */
	if (mode > 1){
		mode = 1;
	}
	uint16_t data = 0;
	i2c_mem_read(dev, INA238_DIAG_ALRT, &data);
	data = (data & 0xBFFF) | (mode << 14);
	i2c_mem_write(dev, INA238_DIAG_ALRT, &data);
}

void INA238_set_using_avg_comparing_alert(INA238 *dev, uint8_t mode) {
	/*
	 if mode = 0 ALERT comparison on non-averaged (ADC) value
	 if mode = 1 ALERT comparison on Averaged value
	 */
	if (mode > 1){
		mode = 1;
	}
	uint16_t data = 0;
	i2c_mem_read(dev, INA238_DIAG_ALRT, &data);
	data = (data & 0xDFFF) | (mode << 13);
	i2c_mem_write(dev, INA238_DIAG_ALRT, &data);
}

void INA238_set_fault_pin_polarity(INA238 *dev, uint8_t logic) {
	/*
	 * 0h = Normal (Active-low, open-drain)
	 * 1h = Inverted (active-high, open-drain )
	 */
	if (logic > 1){
		logic = 1;
	}
	uint16_t data = 0;
	i2c_mem_read(dev, INA238_DIAG_ALRT, &data);
	data = (data & 0xEFFF) | (logic << 12);
	i2c_mem_write(dev, INA238_DIAG_ALRT, &data);
}

void INA238_read_error(INA238 *dev) {
	uint16_t data = 0;
	i2c_mem_read(dev, INA238_DIAG_ALRT, &data);
	dev->error.MATHOF = ((data & 0x0200) == 0x0200);
	dev->error.TMPOL = ((data & 0x0080) == 0x0080);
	dev->error.SHNTOL = ((data & 0x0040) == 0x0040);
	dev->error.SHNTUL = ((data & 0x0020) == 0x0020);
	dev->error.BUSOL = ((data & 0x0010) == 0x0010);
	dev->error.BUSUL = ((data & 0x0008) == 0x0008);
	dev->error.POL = ((data & 0x0004) == 0x0004);
	dev->error.MEMSTAT = ((data & 0x0001) == 0x0001);
}

void INA238_read_all(INA238 *dev){
	INA238_read_shunt_voltage(dev);
	INA238_read_bus_voltage(dev);
	INA238_read_temp(dev);
	INA238_read_current(dev);
	INA238_read_power(dev);
}

void INA238_Error_Handle(INA238 *dev,HAL_StatusTypeDef respond){
	uint8_t message[40] = {0};
	if ((respond == HAL_OK) && (dev->is_connect == 2)){
		sprintf((char *)message,"INA238(%x) initializes successfully." ,dev->address);
		SD_Card_Write_Log(LOG_INFO, message, strlen((char *)message));
		dev->is_connect = 1;
	}
	else if ((respond != HAL_OK) && (dev->is_connect == 2)){
		sprintf((char *)message,"INA238(%x) initializes fails." ,dev->address);
		SD_Card_Write_Log(LOG_ERROR, message, strlen((char *)message));
		dev->is_connect = 0;
	}
	else if ((respond == HAL_OK) && (dev->is_connect == 0)){
		sprintf((char *)message,"connect with INA238(%x) successfully." ,dev->address);
		SD_Card_Write_Log(LOG_ERROR, message, strlen((char *)message));
		dev->is_connect = 1;
	}
	else if ((respond != HAL_OK) && (dev->is_connect == 1)){
		sprintf((char *)message,"can't communicate with INA238(%x)." ,dev->address);
		SD_Card_Write_Log(LOG_ERROR, message, strlen((char *)message));
		dev->is_connect = 0;
	}
}
