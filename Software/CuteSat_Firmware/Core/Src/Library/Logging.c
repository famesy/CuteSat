
#include "Library/Logging.h"

void SD_Card_Write_Log(uint8_t log_type, uint8_t *message, uint16_t message_length) {
	RTC_DateTypeDef gDate;
	RTC_TimeTypeDef gTime;
	uint8_t date[25] = {0};
	uint8_t time[25] = {0};
	uint8_t log_type_message[25] = {0};
	HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);
	sprintf((char*) time, "%02d:%02d:%02d,\t", gTime.Hours, gTime.Minutes,
			gTime.Seconds);
	sprintf((char*) date, "%02d-%02d-%2d,\t", gDate.Date, gDate.Month,
			2000 + gDate.Year);
	if (log_type == LOG_INFO){
		sprintf((char*) log_type_message, "info,\t\t");
	}
	else if (log_type == LOG_ERROR){
		sprintf((char*) log_type_message, "error,\t");
	}
	else if (log_type == LOG_DEBUG){
		sprintf((char*) log_type_message, "debug,\t");
	}
	uint8_t enter_msg[5] = "\n";
	static uint32_t byteswritten;
	f_mount(&SDFatFS, (TCHAR const*) SDPath, 0);
	FRESULT sd_result = f_open(&SDFile, "log.txt", FA_OPEN_APPEND | FA_WRITE);
	if (sd_result == FR_OK) {
		f_write(&SDFile, log_type_message, strlen((char*) log_type_message), (void*) &byteswritten);
		f_write(&SDFile, date, strlen((char*) date), (void*) &byteswritten);
		f_write(&SDFile, time, strlen((char*) time), (void*) &byteswritten);
		f_write(&SDFile, message, strlen((char*) message), (void*) &byteswritten);
		f_write(&SDFile, enter_msg, strlen((char*) enter_msg), (void*) &byteswritten);
		f_close(&SDFile);
	}
}
