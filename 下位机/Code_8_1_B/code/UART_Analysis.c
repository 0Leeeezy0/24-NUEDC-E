#include "common.h"

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     对上位机传下来的数据进行单位换算（转化为像素）和坐标转化
// 函数说明     将摄像头的xy坐标更改为“同原点方向的坐标”
//-------------------------------------------------------------------------------------------------------------------
void PC_Position_Correct(void)
{
    int32 ChessPosition_temp[9][2]={{0,0}};//定义三个数据中转区域
    int32 BlackChessPosition_temp[5][2]={{0,0}};
    int32 WhiteChessPosition_temp[5][2]={{0,0}};
    //数据转存
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            ChessPosition_temp[i][j] = ChessPosition[i][j];
        }
    }
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            BlackChessPosition_temp[i][j] = BlackChessPosition[i][j];
        }
    }
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            WhiteChessPosition_temp[i][j] = WhiteChessPosition[i][j];
        }
    }
    //数据换算之X坐标（X=y）
    for (int i = 0; i < 9; i++)
    {
        ChessPosition[i][0] =320- ChessPosition_temp[i][1]/100;
    }
    for (int i = 0; i < 5; i++)
    {
        BlackChessPosition[i][0] =320- BlackChessPosition_temp[i][1]/100;
        WhiteChessPosition[i][0] =320- WhiteChessPosition_temp[i][1]/100;
    }
    //数据换算之Y坐标（Y=240-x）
    for (int i = 0; i < 9; i++)
    {
        ChessPosition[i][1] = 240-ChessPosition_temp[i][0]/100;
    }
    for (int i = 0; i < 5; i++)
    {
        BlackChessPosition[i][1] = 240-BlackChessPosition_temp[i][0]/100;
        WhiteChessPosition[i][1] = 240-WhiteChessPosition_temp[i][0]/100;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     模式0的数据接收
// 使用示例
//-------------------------------------------------------------------------------------------------------------------
void uart3_receive_Mode0(void)
{
    static int uart_receive_data_num = 0;//用于判断当前接收的数据为第几位
    int receive_EN = 0;//查询缓存区是否有数据的状态位
    uint8_t uart_receive_data;//接收单位数据暂存区
    static uint8_t uart_receive_info_buffer[length_uart_receive_info] = {0x00};//接收暂存区，帧尾正确才转存
//    uart_receive_data = uart_read_byte(UART_3);
    receive_EN = uart_query_byte(UART_3,&uart_receive_data);
    // 串口接收解析
    if(receive_EN == 1)
    {
        if(DataMode!=3)
        {
            uart_receive_data_num++;//接收数据移位
            switch(uart_receive_data_num)
            {
                case 1: // 校验帧头1
                {
                    if(uart_receive_data != 0xA0)
                    {
                        uart_receive_data_num = 0;
                    }
                    break;
                }
                case 2: // 校验帧头2
                {
                    if(uart_receive_data != 0xA1)
                    {
                        uart_receive_data_num = 0;
                    }
                    break;
                }
                case 3:{uart_receive_info_buffer[uart_receive_data_num-3] = uart_receive_data;break; }//第一位
                case 4:{uart_receive_info_buffer[uart_receive_data_num-3] = uart_receive_data;break; }//第二位
                case 5:{uart_receive_info_buffer[uart_receive_data_num-3] = uart_receive_data;break; }//第三位
                case 6:{uart_receive_info_buffer[uart_receive_data_num-3] = uart_receive_data;break; }//第四位
                case 7:{uart_receive_info_buffer[uart_receive_data_num-3] = uart_receive_data;break; }//第五位
                case 8:{uart_receive_info_buffer[uart_receive_data_num-3] = uart_receive_data;break; }//第六位
                case 9:{uart_receive_info_buffer[uart_receive_data_num-3] = uart_receive_data;break; }//第七位
                case 10:{uart_receive_info_buffer[uart_receive_data_num-3] = uart_receive_data;break; }//第八位
                case 11:{uart_receive_info_buffer[uart_receive_data_num-3] = uart_receive_data;break; }//第九位
                case 12:{uart_receive_info_buffer[uart_receive_data_num-3] = uart_receive_data;break; }//第十位
                case 13:{uart_receive_info_buffer[uart_receive_data_num-3] = uart_receive_data;break; }//第十一位
                case 14:{uart_receive_info_buffer[uart_receive_data_num-3] = uart_receive_data;break; }//第十二位
                case (length_uart_receive_info+3):  // 校验帧尾
                {
                    uart_receive_data_num = 0;//最后一位数据，无论成功与否均重开
                    // 帧尾正确
                    if(uart_receive_data == 0xA2)
                    {
                        Analysis_Flag=1;
                        for(int i = 0;i < length_uart_receive_info;i++)//帧尾正确时转存数据
                        {
                            uart_receive_info[i] = uart_receive_info_buffer[i];
                        }
                        for(int i = 0;i < length_uart_receive_info;i++)//将接收缓存区清空
                        {
                            uart_receive_info_buffer[i] = 0;
                        }
                    }
                    // 帧尾错误
                    else
                    {
                        // 清空接收缓存区
                        for(int i = 0;i < length_uart_receive_info;i++)
                        {
                            uart_receive_info_buffer[i] = 0;
                        }
                    }
                    break;
                }
            }
        }
        else if(DataMode==3)
        {
            uart_receive_data_num++;//接收数据移位
            switch(uart_receive_data_num)
            {
                case 1: // 校验帧头1
                {
                    if(uart_receive_data != 0xA0)
                    {
                        uart_receive_data_num = 0;
                    }
                    break;
                }
                case 2: // 校验帧头2
                {
                    if(uart_receive_data != 0xA1)
                    {
                        uart_receive_data_num = 0;
                    }
                    break;
                }
                case 3:{uart_receive_info_buffer[uart_receive_data_num-3] = uart_receive_data;break; }//第一位
                case 4:{uart_receive_info_buffer[uart_receive_data_num-3] = uart_receive_data;break; }//第二位
                case (5):  // 校验帧尾
                {
                    uart_receive_data_num = 0;//最后一位数据，无论成功与否均重开
                    // 帧尾正确
                    if(uart_receive_data == 0xA2)
                    {
                        Analysis_Flag=1;
                        for(int i = 0;i < length_uart_receive_info;i++)//转存多位,但是有效的只有两位
                        {
                            uart_receive_info[i] = uart_receive_info_buffer[i];
                        }
                        for(int i = 0;i < length_uart_receive_info;i++)//将接收缓存区清空
                        {
                            uart_receive_info_buffer[i] = 0;
                        }
                    }
                    // 帧尾错误
                    else
                    {
                        // 清空接收缓存区
                        for(int i = 0;i < length_uart_receive_info;i++)
                        {
                            uart_receive_info_buffer[i] = 0;
                        }
                    }
                    break;
                }
            }
        }
    }
}

void uart3_Analysis(void)
{
    if(Analysis_Flag == 1)
    {
        if(DataMode == 0)
        {
            //九宫格信息
            DataRefreshFlag1=1;
            int32 ChessNum=uint8_2_int32(uart_receive_info[0],uart_receive_info[1],uart_receive_info[2],uart_receive_info[3]);
            int32 ChessPositio_X=uint8_2_int32(uart_receive_info[4],uart_receive_info[5],uart_receive_info[6],uart_receive_info[7]);
            int32 ChessPositio_Y=uint8_2_int32(uart_receive_info[8],uart_receive_info[9],uart_receive_info[10],uart_receive_info[11]);
            switch(ChessNum)
            {
                case 0:ChessPosition[0][0]=320-ChessPositio_X/100;ChessPosition[0][1]=240-ChessPositio_Y/100;break;
                case 1:ChessPosition[1][0]=320-ChessPositio_X/100;ChessPosition[1][1]=240-ChessPositio_Y/100;break;
                case 2:ChessPosition[2][0]=320-ChessPositio_X/100;ChessPosition[2][1]=240-ChessPositio_Y/100;break;
                case 3:ChessPosition[3][0]=320-ChessPositio_X/100;ChessPosition[3][1]=240-ChessPositio_Y/100;break;
                case 4:ChessPosition[4][0]=320-ChessPositio_X/100;ChessPosition[4][1]=240-ChessPositio_Y/100;break;
                case 5:ChessPosition[5][0]=320-ChessPositio_X/100;ChessPosition[5][1]=240-ChessPositio_Y/100;break;
                case 6:ChessPosition[6][0]=320-ChessPositio_X/100;ChessPosition[6][1]=240-ChessPositio_Y/100;break;
                case 7:ChessPosition[7][0]=320-ChessPositio_X/100;ChessPosition[7][1]=240-ChessPositio_Y/100;break;
                case 8:ChessPosition[8][0]=320-ChessPositio_X/100;ChessPosition[8][1]=240-ChessPositio_Y/100;break;
            }
        }
        else if(DataMode == 1)
        {
            DataRefreshFlag2=1;
            int32 BlackChessNum=uint8_2_int32(uart_receive_info[0],uart_receive_info[1],uart_receive_info[2],uart_receive_info[3]);
            int32 ChessPositio_X=uint8_2_int32(uart_receive_info[4],uart_receive_info[5],uart_receive_info[6],uart_receive_info[7]);
            int32 ChessPositio_Y=uint8_2_int32(uart_receive_info[8],uart_receive_info[9],uart_receive_info[10],uart_receive_info[11]);
            switch(BlackChessNum)
            {
                case 0:BlackChessPosition[0][0]=320-ChessPositio_X/100;BlackChessPosition[0][1]=240-ChessPositio_Y/100;AllChessPosition[0][0]=320-ChessPositio_X/100;AllChessPosition[0][1]=240-ChessPositio_Y/100;break;
                case 1:BlackChessPosition[1][0]=320-ChessPositio_X/100;BlackChessPosition[1][1]=240-ChessPositio_Y/100;AllChessPosition[1][0]=320-ChessPositio_X/100;AllChessPosition[1][1]=240-ChessPositio_Y/100;break;
                case 2:BlackChessPosition[2][0]=320-ChessPositio_X/100;BlackChessPosition[2][1]=240-ChessPositio_Y/100;AllChessPosition[2][0]=320-ChessPositio_X/100;AllChessPosition[2][1]=240-ChessPositio_Y/100;break;
                case 3:BlackChessPosition[3][0]=320-ChessPositio_X/100;BlackChessPosition[3][1]=240-ChessPositio_Y/100;AllChessPosition[3][0]=320-ChessPositio_X/100;AllChessPosition[3][1]=240-ChessPositio_Y/100;break;
                case 4:BlackChessPosition[4][0]=320-ChessPositio_X/100;BlackChessPosition[4][1]=240-ChessPositio_Y/100;AllChessPosition[4][0]=320-ChessPositio_X/100;AllChessPosition[4][1]=240-ChessPositio_Y/100;break;
            }
        }
        else if(DataMode == 2)
        {
            DataRefreshFlag3=1;
            int32 WhiteChessNum=uint8_2_int32(uart_receive_info[0],uart_receive_info[1],uart_receive_info[2],uart_receive_info[3]);
            int32 ChessPositio_X=uint8_2_int32(uart_receive_info[4],uart_receive_info[5],uart_receive_info[6],uart_receive_info[7]);
            int32 ChessPositio_Y=uint8_2_int32(uart_receive_info[8],uart_receive_info[9],uart_receive_info[10],uart_receive_info[11]);
            switch(WhiteChessNum)
            {
                case 0:WhiteChessPosition[0][0]=320-ChessPositio_X/100;WhiteChessPosition[0][1]=240-ChessPositio_Y/100;AllChessPosition[5][0]=320-ChessPositio_X/100;AllChessPosition[5][1]=240-ChessPositio_Y/100;break;
                case 1:WhiteChessPosition[1][0]=320-ChessPositio_X/100;WhiteChessPosition[1][1]=240-ChessPositio_Y/100;AllChessPosition[6][0]=320-ChessPositio_X/100;AllChessPosition[6][1]=240-ChessPositio_Y/100;break;
                case 2:WhiteChessPosition[2][0]=320-ChessPositio_X/100;WhiteChessPosition[2][1]=240-ChessPositio_Y/100;AllChessPosition[7][0]=320-ChessPositio_X/100;AllChessPosition[7][1]=240-ChessPositio_Y/100;break;
                case 3:WhiteChessPosition[3][0]=320-ChessPositio_X/100;WhiteChessPosition[3][1]=240-ChessPositio_Y/100;AllChessPosition[8][0]=320-ChessPositio_X/100;AllChessPosition[8][1]=240-ChessPositio_Y/100;break;
                case 4:WhiteChessPosition[4][0]=320-ChessPositio_X/100;WhiteChessPosition[4][1]=240-ChessPositio_Y/100;AllChessPosition[9][0]=320-ChessPositio_X/100;AllChessPosition[9][1]=240-ChessPositio_Y/100;break;
            }
        }
        else if(DataMode == 3)
        {
            checkerboard_PC1=uart_receive_info[0];
            checkerboard_PC2=uart_receive_info[1];
            if(checkerboard_PC2!=0xFF)
            {
                Rigged = true;
            }
            else
            {
                Rigged = false;
            }
            Recive=true;
        }
    }
    Analysis_Flag=0;//要是等等解析有问题再把他删掉
}

void UART3_READ_DATA(void)
{
    Facility_TO_Point(position_P_X,position_P_Y);
    system_delay_ms(500);
    DataMode=0;
    uart3_send_Mode(DataMode,0);
    system_delay_ms(500);
    DataMode=1;
    uart3_send_Mode(DataMode,0);
    system_delay_ms(500);
    DataMode=2;
    uart3_send_Mode(DataMode,0);
    system_delay_ms(500);
    Facility_TO_Point(0,0);
}



