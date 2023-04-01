/*
 * EDAC.c
 *
 *  Created on: May 16, 2022
 *      Author: fame
 */
#include <Library/EDAC.h>

void hamming7264_encode(uint8_t data[8], uint8_t target_arr[9])
{
    uint8_t current_idx = 0;
    for (int i = 0; i < 9; i++){
        target_arr[i] = 0;
    }
    // arrange data into target array
    for (int i = 0; i < 72; i++)
    {
        // check if it not power of two?
        if ((i & (i - 1)) != 0)
        {
            int arr_num = i / 8;
            int arr_idx = i % 8;
            target_arr[arr_num] |= ((data[current_idx / 8] >> (current_idx % 8)) & 0x01) << arr_idx;
            current_idx++;
        }
    }
    // calculate parity_bits
    //  0 is parity bits
    for (int i = 0; i < 7; i++)
    {
        uint8_t parity_idx = pow(2, i);
        uint8_t parity_value = 0;
        // check if that idx should be calculate in parity bits
        for (int j = 0; j < 72; j++)
        {
            if (((j & parity_idx) == parity_idx) && (j != parity_idx))
            {
                parity_value ^= (target_arr[j / 8] >> (j % 8)) & 0x01;
            }
        }
        parity_value = parity_value & 0x01;
        target_arr[parity_idx / 8] |= parity_value << (parity_idx % 8);
    }
    // calculate all parity_bits
    uint8_t parity_value = 0;
    for (int i = 0; i < 72; i++)
    {
        parity_value ^= (target_arr[i / 8] >> (i % 8)) & 0x01;
    }
    parity_value = parity_value & 0x01;
    target_arr[0] |= parity_value;
}

uint8_t hamming7264_decode(uint8_t data[9], uint8_t target_data[8])
{
    uint8_t result = 0;
    // check overall parity (work)
    uint8_t overall_msg_parity = 0;
    for (int i = 0; i < 72; i++)
    {
        overall_msg_parity ^= (data[i / 8] >> (i % 8));
    }
    overall_msg_parity = overall_msg_parity & 0x01;
    //get store parity bit (maybe work?)
    uint8_t store_parity_bits = 0;
    for (int i = 0; i < 7; i++){
        uint8_t parity_idx = pow(2, i);
        store_parity_bits |= ((data[parity_idx/8] >> (parity_idx % 8)) & 0x01) << i;
    }
    //calculate current parity bit (meh)
    uint8_t current_parity_bits = 0;
    uint8_t fix_parity_bits = 0; // this one use when 1 bits error has occured!
    for (int i = 0; i < 7; i++)
    {
        uint8_t parity_idx = pow(2, i);
        uint8_t parity_value = 0;
        // check if that idx should be calculate in parity bits
        for (int j = 0; j < 72; j++)
        {
            if (((j & parity_idx) == parity_idx) && (j != parity_idx))
            {
                parity_value ^= (data[j / 8] >> (j % 8)) & 0x01;
            }
        }
        current_parity_bits |= parity_value << i;
        parity_value ^= (data[parity_idx / 8] >> (parity_idx % 8)) & 0x01;
        fix_parity_bits |= parity_value << i;
    }
    if ((overall_msg_parity == 0) && (store_parity_bits != current_parity_bits)){
        return 2;
    }
    else if ((overall_msg_parity == 1) && (store_parity_bits != current_parity_bits)){
        data[fix_parity_bits/8] ^= (int)(pow(2,(fix_parity_bits % 8)));
        result = 1;
    }
    else if (overall_msg_parity != (data[0] ^ 0x01)){
        result = 1;
    }
    //decode data (work)
    uint8_t cnt = 0;
    for (int i = 0; i < 72; i++){
        if ((i & (i - 1)) != 0){
            target_data[cnt/8] |= ((data[i/8] >> (i%8)) & 0x01) << (cnt%8);
            cnt++;
        }
    }
    return result;
}

void FRAM_Encode_Write(FRAM *dev, uint16_t addr, uint8_t data[8]){
	uint8_t encode_data[9] = {0};
	hamming7264_encode(data,encode_data);
	FRAM_Seq_Write(dev, addr, encode_data, sizeof(encode_data));
}

void FRAM_Decode_Read(FRAM *dev, uint16_t addr, uint8_t data[8]){
	uint8_t decode_data[9] = {0};
	FRAM_Seq_Read(dev, addr, decode_data, sizeof(decode_data));
	uint8_t result = hamming7264_decode(decode_data, data);
	if (result == 1){
		FRAM_Encode_Write(dev, addr, data);
	}
}

void FRAM_Encode_Write_Block(FRAM *dev, uint16_t block, uint32_t first_data[1], uint32_t second_data[1]){
	uint64_t combine_data = ((uint64_t) *first_data << 32) | *second_data;
	uint8_t arr_buf[8] = {0};
	memcpy(arr_buf, &combine_data, 8);
	FRAM_Encode_Write(dev, (block * 9), arr_buf);
}

void FRAM_Encode_Read_Block(FRAM *dev, uint16_t block, uint8_t select_half, uint32_t *data){
	uint8_t read_buf[8] = {0};
	FRAM_Decode_Read(dev, (block*9), read_buf);
	if(select_half == 0){
		memcpy(data, (read_buf+4), 4);
	}
	else {
		memcpy(data, read_buf, 4);
	}
}

void FRAM_Scrubbing(FRAM *dev, uint16_t end_block) {
	uint16_t datasize = 9 * end_block;
	uint8_t decode_data[8192] = {0};
	FRAM_Seq_Read(dev, 0, decode_data, datasize);
	uint8_t data_bef_decode[9] = {0};
	uint8_t data[8] = {0};
	for (uint16_t i = 0; i < end_block; i++) {
//		uint8_t result = hamming7264_decode(decode_data, data);
		memcpy(data_bef_decode,(decode_data + (i * 9)),9);
		uint8_t result = hamming7264_decode(data_bef_decode, data);
		if (result == 1) {
			FRAM_Encode_Write(dev, i * 9, data);
		}
	}
//	free(decode_data);
}
