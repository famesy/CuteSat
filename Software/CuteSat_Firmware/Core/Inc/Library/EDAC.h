/*
 * EDAC.h
 *
 *  Created on: May 16, 2022
 *      Author: fame
 */

#ifndef INC_LIBRARY_EDAC_H_
#define INC_LIBRARY_EDAC_H_

#include <Library/FRAM.h>

/*
 * EDAC Original Code
 */
void hamming7264_encode(uint8_t data[8], uint8_t target_arr[9]);
uint8_t hamming7264_decode(uint8_t data[9], uint8_t target_data[8]);
void FRAM_Encode_Write(FRAM *dev, uint16_t addr, uint8_t data[8]);
void FRAM_Decode_Read(FRAM *dev, uint16_t addr, uint8_t data[8]);
void FRAM_Encode_Write_Block(FRAM *dev, uint16_t block, uint32_t first_data[1], uint32_t second_data[1]);
void FRAM_Encode_Read_Block(FRAM *dev, uint16_t block, uint8_t select_half, uint32_t *data);
void FRAM_Scrubbing(FRAM *dev, uint16_t end_block);
/*
 * EDAC Extended Code
 */

#endif /* INC_LIBRARY_EDAC_H_ */
