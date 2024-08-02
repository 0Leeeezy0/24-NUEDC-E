/*
 * Data.h
 *
 *  Created on: 2024Äê7ÔÂ30ÈÕ
 *      Author: 86152
 */

#ifndef CODE_DATA_H_
#define CODE_DATA_H_

#include "common.h"

void int16_2_uint8(int16 int16data);
int16 uint8_2_int16(uint8 low_byte, uint8 high_byte);
void int32_2_uint8(int32 int32data);
int32 uint8_2_int32(uint8 Byte_A, uint8 Byte_B, uint8 Byte_C, uint8 Byte_D);

void uart3_send_int16(int16 INT16DATA);
void uart3_send_int32(int32 INT32DATA);
void uart3_send_Mode(uint8 mode,uint8 color);

#endif /* CODE_DATA_H_ */
