#include "Library/Tmp75.h"
#include "Library/Logging.h"

void TMP75_Init(void) {
	/*configuration register = 0x01
	 OS R1 R0 F1 F0 POL TM SD
	 0  1  1  0  0  0   0  0 = 0x60
	 SD TM POL F0 F1 R0 R1 OS
	 0  0  0   0  0  1  1  0
	 */
	uint8_t data[2];
	data[0] = 0x01;     // TMP75_ADDR
	data[1] = 0x06;    // MSB byte of 16bit data
	HAL_StatusTypeDef rep = HAL_I2C_Master_Transmit(&hi2c2, TMP75_ADDR, data, 2, 100);
	if (rep != HAL_OK){
		uint8_t message[40] = "TMP75 initializes successfully.";
		SD_Card_Write_Log(LOG_ERROR, message, strlen((char *)message));
	}
	else {
		uint8_t message[40] = "TMP75 initialization fails.";
		SD_Card_Write_Log(LOG_INFO, message, strlen((char *)message));
	}
}

void Write_Register(uint8_t register_pointer, uint16_t register_value) {
	uint8_t data[3];
	data[0] = register_pointer;     // TMP75_ADDR
	data[1] = register_value >> 8;    // MSB byte of 16bit data
	data[2] = register_value;       // LSB byte of 16bit data
	HAL_I2C_Master_Transmit(&hi2c2, TMP75_ADDR, data, 3, 100);
}

void Read_Register(uint8_t register_pointer, uint8_t* receive_buffer) {
	// first set the register pointer to the register wanted to be read
	HAL_I2C_Master_Transmit(&hi2c2, TMP75_ADDR, &register_pointer, 1, 100);

	// receive the 2 x 8bit data into the receive buffer
	HAL_I2C_Master_Receive(&hi2c2, TMP75_ADDR, receive_buffer, 2, 100);
}

void TMP75_Read_TempCelsius(float *receive_buffer) {
	uint8_t buffer[2];
	uint16_t TempSum;
	Read_Register(0x00, buffer);
	TempSum = (((buffer[0] << 8) | buffer[1]) >> 4);
	*receive_buffer = (TempSum * FTMP75_TEMP_AD_STEP);
}
