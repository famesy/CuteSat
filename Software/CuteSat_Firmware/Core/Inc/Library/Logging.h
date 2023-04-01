/*
 * Logging.h
 *
 *  Created on: May 20, 2022
 *      Author: fame
 */

#ifndef INC_LIBRARY_LOGGING_H_
#define INC_LIBRARY_LOGGING_H_

#include "sdmmc.h"
#include "fatfs.h"
#include "string.h"
#include "rtc.h"
#include <stdio.h>

#define LOG_INFO 0
#define LOG_DEBUG 1
#define LOG_ERROR 2

void SD_Card_Write_Log(uint8_t log_type, uint8_t *message, uint16_t message_length);

#endif /* INC_LIBRARY_LOGGING_H_ */
