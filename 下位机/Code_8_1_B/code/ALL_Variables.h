#include "common.h"

#ifndef CODE_ALL_VARIABLES_H_
#define CODE_ALL_VARIABLES_H_

extern uint8 KEY_LongPress_Period;
extern uint8 KEY_ShortPress_Period;
extern uint32 key_press_time[4];
extern uint8 Key_State[4];
extern gpio_pin_enum Key_index[4];


// **************************** UART_Analysis.c****************************
typedef struct {
    uint8 low_byte;
    uint8 high_byte;
}Int16ToBytes;
//typedef struct {
//    uint32 ChessNum;
//    uint32 ChessNum;
//    uint32 ChessNum;
//};
extern Int16ToBytes int16TOuint8_result;
extern uint8 Int32ToBytes[4];

extern uint8 Analysis_Flag;
extern uint8 uart_receive_info[length_uart_receive_info];//接受到的原始数据（去除关键帧）
extern uint8 DATA_INT16_Temp[2];//定义接收int16型数据的存储数组
extern int16 DATA_1;
extern int32 hahaha;
extern int8 DataMode;
extern int32 ChessPosition[9][2];
extern int32 BlackChessPosition[5][2];
extern int32 WhiteChessPosition[5][2];
extern int32 AllChessPosition[10][2];
extern uint8 ChessNUM_PCSend;
extern uint8 checkerboard_PC1;
extern uint8 checkerboard_PC2;
extern bool Rigged;
extern bool Recive;
// **************************** Motor.c_第一部分****************************

extern uint32 Fre_A;
extern uint8 MotorX_Flag;
extern uint8 MotorY_Flag;
extern uint8 MotorZ_Flag;
extern int32 Step_X_Temp;
extern int32 Step_X;
extern int32 Step_Y_Temp;
extern int32 Step_Y;
extern int32 Step_Z_Temp;
extern int32 Step_Z;
// **************************** Motor.c_第二部分 ****************************
//定义三个步进电机的绝对步进步数
extern int32 Step_X_absolute;
extern int32 Step_Y_absolute;
extern int32 Step_Z_absolute;
//定义坐标原点基于初始位置的绝对步长坐标
extern int32 Step_OriginX_absolute;
extern int32 Step_OriginY_absolute;
//每次移动的相对步长
extern int32 Step_OnceX_relative;
extern int32 Step_OnceY_relative;
extern int32 Step_OnceZ_relative;
//定义点的步长坐标
extern int32 StepNum_PositionAX;
extern int32 StepNum_PositionAY;
extern int32 StepNum_PositionBX;
extern int32 StepNum_PositionBY;

extern int32 X_MM;
extern int32 Y_MM;

extern int32 Position_AX;//A点的坐标
extern int32 Position_AY;
extern int32 Position_BX;//B点的坐标
extern int32 Position_BY;
// **************************** Motor.c_题目第一问****************************
extern int32 Step_Origin_TO_Center_X;//从起始点挪动到图像终点的脉冲数
extern int32 Step_Origin_TO_Center_Y;
extern int32 position_P_X;
extern int32 position_P_Y;
// **************************** Motor.c_题目第一问****************************
// **************************** Motor.c_题目第二问****************************
extern uint8 Select_Num;
extern int32 Point_Num_Select[4];
extern int32 Num_Select[4];
// **************************** Motor.c_题目第二问****************************
// **************************** Motor.c_题目第四/五问****************************
extern uint8 COLOR;
// **************************** Page.c ****************************
extern uint8 menu2;//选择哪个二级菜单
extern uint8 MENU;
extern uint8 Line_A;
extern uint8 FirstLine;
extern uint8 LastLine;
extern uint8 DataRefreshFlag1;
extern uint8 DataRefreshFlag2;
extern uint8 DataRefreshFlag3;
// **************************** Page.c ****************************
//=================================================常用字体===================================================
extern const uint8 chinese_AllMenu[6][16];
extern const uint8 chinese_SingleStepSet[8][16];
extern const uint8 chinese_Back[4][16];
extern const uint8 chinese_BackOrigin[8][16];
//=================================================一级菜单之菜单选择===================================================
extern const uint8 chinese_MenuFirst_A[8][16];
extern const uint8 chinese_MenuFirst_B[8][16];
extern const uint8 chinese_MenuFirst_C[8][16];
//=================================================二级菜单之第一个===================================================
extern const uint8 chinese_MenuSecondA_A[8][16];
extern const uint8 chinese_MenuSecondA_B[8][16];
extern const uint8 chinese_MenuSecondA_C[8][16];
//=================================================二级菜单之第一个===================================================
extern const uint8 chinese_MenuSecondB_A[8][16];
extern const uint8 chinese_MenuSecondB_B[8][16];
//=================================================二级菜单之第三个===================================================
extern const uint8 chinese_MenuSecondC_A[8][16];
extern const uint8 chinese_MenuSecondC_B[8][16];
extern const uint8 chinese_MenuSecondC_C[8][16];
extern const uint8 chinese_MenuSecondC_D[8][16];
extern const uint8 chinese_MenuSecondC_E[8][16];
extern const uint8 chinese_MenuSecondC_F[8][16];
extern const uint8 chinese_MenuSecondC_G[8][16];
extern const uint8 chinese_MenuSecondC_H[8][16];
extern const uint8 chinese_MenuSecondC_I[8][16];

#endif /* CODE_ALL_VARIABLES_H_ */
