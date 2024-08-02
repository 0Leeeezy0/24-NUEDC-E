#include "common.h"

void int16_2_uint8(int16 int16data)
{
    int16TOuint8_result.low_byte = (uint8)(int16data & 0xFF);
    int16TOuint8_result.high_byte = (uint8)((int16data >> 8) & 0xFF);
}

int16 uint8_2_int16(uint8 low_byte, uint8 high_byte)
{
    int16 High_Data=((int16)high_byte)<<8;
    // 小端序组合：先放低位字节，再放高位字节（右移8位）
    return (int16)(High_Data | low_byte);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     将int32类型的数据拆分成四个uint8数据
// 使用示例
//-------------------------------------------------------------------------------------------------------------------
void int32_2_uint8(int32 int32data)
{
    Int32ToBytes[0] = (uint8)( int32data & 0xFF);        // 最低位字节
    Int32ToBytes[1] = (uint8)((int32data >> 8) & 0xFF);  // 第二低位字节
    Int32ToBytes[2] = (uint8)((int32data >> 16) & 0xFF); // 第二高位字节
    Int32ToBytes[3] = (uint8)((int32data >> 24) & 0xFF); // 最高位字节
}
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     将四个uint8数据合并成一个int32数据
// 使用示例
//-------------------------------------------------------------------------------------------------------------------
int32 uint8_2_int32(uint8 Byte_A, uint8 Byte_B, uint8 Byte_C, uint8 Byte_D)
{
    return ((int32)Byte_D << 24) | ((int32)Byte_C << 16) | ((int32)Byte_B << 8)  | (int32)Byte_A;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     将int16型的数据转化为uint8并发送出去
// 使用示例
//-------------------------------------------------------------------------------------------------------------------
void uart3_send_int16(int16 INT16DATA)
{
    uint8 uart_send_buff[2]={0x00};//定义要通过UART3发送的数组
    int16_2_uint8(INT16DATA);//将传入的数据进行转化,转化结果存在int16TOuint8_result结构体内
    //写入发送区域
    uart_send_buff[0]=int16TOuint8_result.low_byte;
    uart_send_buff[1]=int16TOuint8_result.high_byte;

    uart_write_buffer(UART_3,uart_send_buff,2);
}
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     将int16型的数据转化为uint8并发送出去
// 使用示例
//-------------------------------------------------------------------------------------------------------------------
void uart3_send_int32(int32 INT32DATA)
{
    uint8 uart_send_buff[4]={0x00};//定义要通过UART3发送的数组
    int32_2_uint8(INT32DATA);//将传入的数据进行转化，转化结果存在Int32ToBytes[4]这个数组中
    //写入发送区域
    uart_send_buff[0]=Int32ToBytes[0];
    uart_send_buff[1]=Int32ToBytes[1];
    uart_send_buff[2]=Int32ToBytes[2];
    uart_send_buff[3]=Int32ToBytes[3];

    uart_write_buffer(UART_3,uart_send_buff,4);
}
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     发送一串数据选择上位机下发的数据模式
// 数据格式     A0 A1 模式 A2
//-------------------------------------------------------------------------------------------------------------------
void uart3_send_Mode(uint8 mode,uint8 color)
{
    uint8 uart_send_buff[5]={0x00};//定义要通过UART3发送的数组
    uart_send_buff[0]=0xA0;
    uart_send_buff[1]=0xA1;
    uart_send_buff[2]=mode;
    uart_send_buff[3]=color;
    uart_send_buff[4]=0xA2;

    uart_write_buffer(UART_3,uart_send_buff,5);
}
