#include "common.h"

#ifndef CODE_MOTOR_H_
#define CODE_MOTOR_H_

void Mortor_Move_X(int32 step_X);
void Mortor_Move_Y(int32 step_Y);
void Mortor_Move_Z(int32 step_Z);
void Motor_Move_Check(void);
void Chess_Grab(void);
void Chess_Put(void);
void Facility_TO_Point(int32 position_x, int32 position_y);
void Facility_Move_MM(int32 xmm, int32 ymm);
void Facility_Move_From_ATOB_MM(int32 A_XMM, int32 A_YMM, int32 B_XMM, int32 B_YMM);
void Facility_Catch_From_ATOB_MM(int32 A_XMM, int32 A_YMM, int32 B_XMM, int32 B_YMM);
void Facility_Move_From_ATOB_Pixel(int32 A_XPixel, int32 A_YPixel, int32 B_XPixel, int32 B_YPixel);
void Facility_Catch_From_ATOB_Pixel(int32 A_XPixel, int32 A_YPixel, int32 B_XPixel, int32 B_YPixel);
void Question2_3_Base(int32 NumChess,int32 NumNine);
void Question2_3(void);
void Question4(void);

#endif /* CODE_MOTOR_H_ */
