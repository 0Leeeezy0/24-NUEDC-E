#include "common.h"

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     箭头显示
// 参数说明     line为需要显示箭头的行数
// 参数说明     LineStart为开始显示的行数，刷新结束行默认为到18行
//-------------------------------------------------------------------------------------------------------------------
void Show_Row(uint8 line,uint8 LineStart)
{
    for(uint8 i=LineStart;i<19;i++)
    {
        if(i==line)
        {
            ips200_show_string(0,16*i,">");
        }
        else
        {
            ips200_show_string(0,16*i," ");
        }
    }
}


void Menu_Second_A_Operate_Right(void)
{
    switch(Line_A)
    {
        case 0:Step_X_Temp+=10;ips200_show_int(88,16*0,Step_X_Temp,6);break;
        case 2:Step_Y_Temp+=10;ips200_show_int(88,16*2,Step_Y_Temp,6);break;
        case 4:Step_Z_Temp+=4;ips200_show_int(88,16*4,Step_Z_Temp,6);break;
//        case 6:Mortor_Move_X(187);break;
//        case 7:Mortor_Move_Y(-187);break;
    }
}

void Menu_Second_A_Operate_Left(void)
{
    switch(Line_A)
    {
        case 0:Step_X_Temp-=10;ips200_show_int(88,16*0,Step_X_Temp,6);break;
        case 2:Step_Y_Temp-=10;ips200_show_int(88,16*2,Step_Y_Temp,6);break;
        case 4:Step_Z_Temp-=4;ips200_show_int(88,16*4,Step_Z_Temp,6);break;
//        case 6:Mortor_Move_X(-187);break;
//        case 7:Mortor_Move_Y(187);break;
    }
}

void Menu_Second_A(void)
{
    Line_A=0;
    FirstLine=0;
    LastLine=10;
    ips200_clear();
    ips200_show_chinese(16,16*0,16,(const uint8 *)chinese_MenuSecondA_A,4, RGB565_RED);ips200_show_string(80,16*0,":");ips200_show_int(88,16*0,Step_X_Temp,6);
    ips200_show_chinese(16,16*1,16,(const uint8 *)chinese_SingleStepSet,4, RGB565_RED);
    ips200_show_chinese(16,16*2,16,(const uint8 *)chinese_MenuSecondA_B,4, RGB565_RED);ips200_show_string(80,16*2,":");ips200_show_int(88,16*2,Step_Y_Temp,6);
    ips200_show_chinese(16,16*3,16,(const uint8 *)chinese_SingleStepSet,4, RGB565_RED);
    ips200_show_chinese(16,16*4,16,(const uint8 *)chinese_MenuSecondA_C,4, RGB565_RED);ips200_show_string(80,16*4,":");ips200_show_int(88,16*4,Step_Z_Temp,6);
    ips200_show_chinese(16,16*5,16,(const uint8 *)chinese_SingleStepSet,4, RGB565_RED);
    ips200_show_string(16,16*6,"zhua");
    ips200_show_string(16,16*7,"fang");
//    ips200_show_string(16,16*9,"BACK");
    ips200_show_chinese(16,16*LastLine,16,(const uint8 *)chinese_Back,2, RGB565_RED);
    Show_Row(Line_A,0);
    while(1)
    {
        ips200_show_string(0,16*19,"Line:");
        ips200_show_uint(40,16*19,Line_A,2);
        ips200_show_int(16,16*11,Step_X_absolute,9);ips200_show_int(100,16*11,Step_Z_absolute,9);
        ips200_show_int(16,16*12,Step_Y_absolute,9);
        if(!gpio_get_level(KEY_Down))
        {
            while(!gpio_get_level(KEY_Down));
            Line_A++;
            if(Line_A>LastLine){Line_A=FirstLine;}
            Show_Row(Line_A,FirstLine);
        }
        if(Key_Get(Key_Left)==KEY_ShortPress)//左减(短按)
        {
            Menu_Second_A_Operate_Left();
            gpio_toggle_level(LED2);
            Key_clear_state(Key_Left);
        }
        if(Key_Get(Key_Left)==KEY_LongPress)//左减(长按)
        {
            system_delay_ms(50);
            Menu_Second_A_Operate_Left();
        }
        if(Key_Get(Key_Right)==KEY_ShortPress)//右加(短按)
        {
            Menu_Second_A_Operate_Right();
            Key_clear_state(Key_Right);
        }
        if(Key_Get(Key_Right)==KEY_LongPress)//右加(长按)
        {
            system_delay_ms(50);
            Menu_Second_A_Operate_Right();
        }

        if(Key_Get(Key_Enter)==KEY_ShortPress)//确定键盘
        {
            if(Line_A==1)
            {
                Mortor_Move_X(Step_X_Temp);
            }
            if(Line_A==3)
            {
                Mortor_Move_Y(Step_Y_Temp);
            }
            if(Line_A==5)
            {
                Mortor_Move_Z(Step_Z_Temp);
            }
            if(Line_A==6)
            {
                Chess_Grab();
            }
            if(Line_A==7)
            {
                Chess_Put();
            }
            if(Line_A==LastLine)
            {
                menu2=0;
                break;
            }
            Key_clear_state(Key_Enter);
        }
    }
}

void Menu_Second_B_Operate_Right(void)
{
    switch(Line_A)
    {
        case 0:Position_AX-=10;ips200_show_int(16,16*0,Position_AX,6);break;
        case 1:Position_AY-=10;ips200_show_int(16,16*1,Position_AY,6);break;
        case 3:Chess_Put();break;
    }
}

void Menu_Second_B_Operate_Left(void)
{
    switch(Line_A)
    {
        case 0:Position_AX+=10;ips200_show_int(16,16*0,Position_AX,6);break;
        case 1:Position_AY+=10;ips200_show_int(16,16*1,Position_AY,6);break;
        case 3:Chess_Grab();break;
    }
}

void Menu_Second_B(void)
{
    Line_A=0;
    FirstLine=0;
    LastLine=5;
    ips200_clear();
//    ips200_show_chinese(16,16*0,16,(const uint8 *)chinese_MenuSecondB_A,4, RGB565_RED);
//    ips200_show_chinese(16,16*1,16,(const uint8 *)chinese_MenuSecondB_B,4, RGB565_RED);
//    ips200_show_chinese(16,16*2,16,(const uint8 *)chinese_BackOrigin,4, RGB565_RED);

    ips200_show_uint(16,16*0,Position_AX,2);
    ips200_show_uint(16,16*1,Position_AY,2);
    ips200_show_string(0,16*2,"MOVE");
    ips200_show_string(0,16*3,"zhua_fang");

    ips200_show_chinese(16,16*LastLine,16,(const uint8 *)chinese_Back,2, RGB565_RED);
    Show_Row(Line_A,0);
    while(1)
    {
        ips200_show_string(0,16*19,"Line:");
        ips200_show_uint(40,16*19,Line_A,2);
        if(!gpio_get_level(KEY_Down))
        {
            while(!gpio_get_level(KEY_Down));
            Line_A++;
            if(Line_A>LastLine){Line_A=FirstLine;}
            Show_Row(Line_A,FirstLine);
        }
        if(Key_Get(Key_Left)==KEY_ShortPress)//左减(短按)
        {
            Menu_Second_B_Operate_Left();
            Key_clear_state(Key_Left);
        }
        if(Key_Get(Key_Left)==KEY_LongPress)//左减(长按)
        {
            system_delay_ms(50);
            Menu_Second_B_Operate_Left();
        }
        if(Key_Get(Key_Right)==KEY_ShortPress)//右加(短按)
        {
            Menu_Second_B_Operate_Right();
            Key_clear_state(Key_Right);
        }
        if(Key_Get(Key_Right)==KEY_LongPress)//右加(长按)
        {
            system_delay_ms(50);
            Menu_Second_B_Operate_Right();
        }
        if(Key_Get(Key_Enter)==KEY_ShortPress)//确定键盘
        {
            if(Line_A==2)
            {
                Facility_Move_From_ATOB_MM(0,0,Position_AX,Position_AY);
            }
            if(Line_A==LastLine)
            {
                menu2=0;
                break;
            }
            Key_clear_state(Key_Enter);
        }
    }
}

void Menu_Second_C(void)
{
    Line_A=1;
    FirstLine=1;
    LastLine=15;
    ips200_clear();
    ips200_show_string(120,16*1,"MODE_0");
    ips200_show_string(120,16*2,"MODE_1");
    ips200_show_string(120,16*3,"MODE_2");
    ips200_show_chinese(16,16*5,16,(const uint8 *)chinese_MenuSecondC_A,4, RGB565_RED);ips200_show_string(80,16*5,":");
    ips200_show_chinese(16,16*6,16,(const uint8 *)chinese_MenuSecondC_B,4, RGB565_RED);ips200_show_string(80,16*6,":");
    ips200_show_chinese(16,16*7,16,(const uint8 *)chinese_MenuSecondC_C,4, RGB565_RED);ips200_show_string(80,16*7,":");
    ips200_show_chinese(16,16*8,16,(const uint8 *)chinese_MenuSecondC_D,4, RGB565_RED);ips200_show_string(80,16*8,":");
    ips200_show_chinese(16,16*9,16,(const uint8 *)chinese_MenuSecondC_E,4, RGB565_RED);ips200_show_string(80,16*9,":");
    ips200_show_chinese(16,16*10,16,(const uint8 *)chinese_MenuSecondC_F,4, RGB565_RED);ips200_show_string(80,16*10,":");
    ips200_show_chinese(16,16*11,16,(const uint8 *)chinese_MenuSecondC_G,4, RGB565_RED);ips200_show_string(80,16*11,":");
    ips200_show_chinese(16,16*12,16,(const uint8 *)chinese_MenuSecondC_H,4, RGB565_RED);ips200_show_string(80,16*12,":");
    ips200_show_chinese(16,16*13,16,(const uint8 *)chinese_MenuSecondC_I,4, RGB565_RED);ips200_show_string(80,16*13,":");

    ips200_show_chinese(16,16*LastLine,16,(const uint8 *)chinese_Back,2, RGB565_RED);
    Show_Row(Line_A,0);
    while(1)
    {
        ips200_show_string(0,16*19,"Line:");
        ips200_show_uint(40,16*19,Line_A,2);

        //显示九宫格坐标信息
        ips200_show_int(88,16*15,ChessPosition[4][0],9);ips200_show_int(144,16*15,ChessPosition[4][1],9);
        if(DataRefreshFlag1 == 1)
        {
            DataRefreshFlag1=0;
            ips200_show_int(88,16*5,ChessPosition[0][0],9);ips200_show_int(144,16*5,ChessPosition[0][1],9);
            ips200_show_int(88,16*6,ChessPosition[1][0],9);ips200_show_int(144,16*6,ChessPosition[1][1],9);
            ips200_show_int(88,16*7,ChessPosition[2][0],9);ips200_show_int(144,16*7,ChessPosition[2][1],9);
            ips200_show_int(88,16*8,ChessPosition[3][0],9);ips200_show_int(144,16*8,ChessPosition[3][1],9);
            ips200_show_int(88,16*9,ChessPosition[4][0],9);ips200_show_int(144,16*9,ChessPosition[4][1],9);
            ips200_show_int(88,16*10,ChessPosition[5][0],9);ips200_show_int(144,16*10,ChessPosition[5][1],9);
            ips200_show_int(88,16*11,ChessPosition[6][0],9);ips200_show_int(144,16*11,ChessPosition[6][1],9);
            ips200_show_int(88,16*12,ChessPosition[7][0],9);ips200_show_int(144,16*12,ChessPosition[7][1],9);
            ips200_show_int(88,16*13,ChessPosition[8][0],9);ips200_show_int(144,16*13,ChessPosition[8][1],9);
        }
        if(DataRefreshFlag2 == 1)
        {
            DataRefreshFlag2=0;
            ips200_show_int(88,16*5,BlackChessPosition[0][0],9);ips200_show_int(144,16*5,BlackChessPosition[0][1],9);
            ips200_show_int(88,16*6,BlackChessPosition[1][0],9);ips200_show_int(144,16*6,BlackChessPosition[1][1],9);
            ips200_show_int(88,16*7,BlackChessPosition[2][0],9);ips200_show_int(144,16*7,BlackChessPosition[2][1],9);
            ips200_show_int(88,16*8,BlackChessPosition[3][0],9);ips200_show_int(144,16*8,BlackChessPosition[3][1],9);
            ips200_show_int(88,16*9,BlackChessPosition[4][0],9);ips200_show_int(144,16*9,BlackChessPosition[4][1],9);
        }
        if(DataRefreshFlag3 == 1)
        {
            DataRefreshFlag3=0;
            ips200_show_int(88,16*5,WhiteChessPosition[0][0],9);ips200_show_int(144,16*5,WhiteChessPosition[0][1],9);
            ips200_show_int(88,16*6,WhiteChessPosition[1][0],9);ips200_show_int(144,16*6,WhiteChessPosition[1][1],9);
            ips200_show_int(88,16*7,WhiteChessPosition[2][0],9);ips200_show_int(144,16*7,WhiteChessPosition[2][1],9);
            ips200_show_int(88,16*8,WhiteChessPosition[3][0],9);ips200_show_int(144,16*8,WhiteChessPosition[3][1],9);
            ips200_show_int(88,16*9,WhiteChessPosition[4][0],9);ips200_show_int(144,16*9,WhiteChessPosition[4][1],9);
        }

        if(!gpio_get_level(KEY_Down))
        {
            while(!gpio_get_level(KEY_Down));
            Line_A++;
            if(Line_A>LastLine){Line_A=FirstLine;}
            Show_Row(Line_A,FirstLine);
        }
        if(Key_Get(Key_Enter)==KEY_ShortPress)//确定键盘
        {
            if(Line_A==1)
            {
                Facility_TO_Point(position_P_X,position_P_Y);
                system_delay_ms(2500);
                DataMode=0;
                uart3_send_Mode(DataMode,0);
            }
            if(Line_A==2)
            {
                Facility_TO_Point(position_P_X,position_P_Y);
                system_delay_ms(2500);
                DataMode=1;
                uart3_send_Mode(DataMode,0);
            }
            if(Line_A==3)
            {
                Facility_TO_Point(position_P_X,position_P_Y);
                system_delay_ms(2500);
                DataMode=2;
                uart3_send_Mode(DataMode,0);
            }
            if(Line_A==LastLine)
            {
                menu2=0;
                break;
            }
            Key_clear_state(Key_Enter);
        }
    }
}

void Menu_Second_D_Operate_Right(void)
{
    switch(Line_A)
    {
        case 4:Facility_Move_MM(-1,0);break;
        case 5:Facility_Move_MM(0,-1);break;
        case 7:Facility_Move_MM(0,-30);break;
        case 8:Facility_Move_MM(-30,0);break;
        case 9:Chess_Put();break;
    }
}

void Menu_Second_D_Operate_Left(void)
{
    switch(Line_A)
    {
        case 4:Facility_Move_MM(1,0);break;
        case 5:Facility_Move_MM(0,1);break;
        case 7:Facility_Move_MM(0,30);break;
        case 8:Facility_Move_MM(30,0);break;
        case 9:Chess_Grab();break;
    }
}

void Menu_Second_D(void)
{
    Line_A=0;
    FirstLine=0;
    LastLine=10;
    ips200_clear();
    ips200_show_string(16,16*1,"JiLUCenter");//记录图像中心位置，在此处将绝对坐标置为0
    ips200_show_int(16,16*2,Step_X_absolute,9);ips200_show_int(100,16*2,Step_Z_absolute,9);
    ips200_show_int(16,16*3,Step_Y_absolute,9);
    ips200_show_string(16,16*4,"MOVE_XMM");
    ips200_show_string(16,16*5,"MOVE_YMM");
    ips200_show_string(16,16*6,"BACKCENTER");
    ips200_show_string(16,16*7,"Hengyige");
    ips200_show_string(16,16*8,"Shuyige");
    ips200_show_string(16,16*9,"zhua_or_fang");
    ips200_show_chinese(16,16*LastLine,16,(const uint8 *)chinese_Back,2, RGB565_RED);
    Show_Row(Line_A,0);
    while(1)
    {
        ips200_show_string(0,16*19,"Line:");
        ips200_show_uint(40,16*19,Line_A,2);

        ips200_show_int(16,16*2,Step_X_absolute,9);ips200_show_int(100,16*2,Step_Z_absolute,9);
        ips200_show_int(16,16*3,Step_Y_absolute,9);
        //显示九宫格坐标信息
        if(!gpio_get_level(KEY_Down))
        {
            while(!gpio_get_level(KEY_Down));
            Line_A++;
            if(Line_A>LastLine){Line_A=FirstLine;}
            Show_Row(Line_A,FirstLine);
        }
        if(Key_Get(Key_Left)==KEY_ShortPress)//左减(短按)
        {
            Menu_Second_D_Operate_Left();
            gpio_toggle_level(LED2);
            Key_clear_state(Key_Left);
        }
        if(Key_Get(Key_Right)==KEY_ShortPress)//右加(短按)
        {
            Menu_Second_D_Operate_Right();
            Key_clear_state(Key_Right);
        }
        if(Key_Get(Key_Enter)==KEY_ShortPress)//确定键盘
        {
            if(Line_A==1)
            {
                Step_X_absolute=0;
                Step_Y_absolute=0;
                Step_Z_absolute=0;
            }
            if(Line_A==6)
            {
                Mortor_Move_X(-Step_X_absolute);
                Mortor_Move_Y(-Step_Y_absolute);
            }
            if(Line_A==LastLine)
            {
                menu2=0;
                break;
            }
            Key_clear_state(Key_Enter);
        }
    }
}

void Menu_Second_E_Operate_Right(void)
{
    switch(Line_A)
    {

    }
}

void Menu_Second_E_Operate_Left(void)
{
    switch(Line_A)
    {

    }
}

void Menu_Second_E(void)
{
    Line_A=0;
    FirstLine=0;
    LastLine=10;
    ips200_clear();
    ips200_show_string(16,16*0,"Center");
    ips200_show_string(16,16*1,"P_dian");
    ips200_show_string(16,16*2,"Origin");
    ips200_show_string(16,16*3,"BLACK1");
    ips200_show_string(16,16*4,"BLACK2");
    ips200_show_string(16,16*5,"BLACK3");
    ips200_show_string(16,16*6,"BLACK4");
    ips200_show_string(16,16*7,"BLACK5");
    ips200_show_string(16,16*8,"WUHAO");
    ips200_show_chinese(16,16*LastLine,16,(const uint8 *)chinese_Back,2, RGB565_RED);
    Show_Row(Line_A,0);
    while(1)
    {
        ips200_show_string(0,16*19,"Line:");
        ips200_show_uint(40,16*19,Line_A,2);

        ips200_show_int(16,16*12,Step_X_absolute,9);ips200_show_int(100,16*12,Step_Z_absolute,9);
        ips200_show_int(16,16*13,Step_Y_absolute,9);

//        ips200_show_int(88,16*11,ChessPosition[4][0],9);ips200_show_int(144,16*11,ChessPosition[4][1],9);
//        ips200_show_int(88,16*12,BlackChessPosition[0][0],9);ips200_show_int(144,16*12,BlackChessPosition[0][1],9);
//        //显示九宫格坐标信息
        if(!gpio_get_level(KEY_Down))
        {
            while(!gpio_get_level(KEY_Down));
            Line_A++;
            if(Line_A>LastLine){Line_A=FirstLine;}
            Show_Row(Line_A,FirstLine);
        }
        if(Key_Get(Key_Left)==KEY_ShortPress)//左减(短按)
        {
            Menu_Second_E_Operate_Left();
            gpio_toggle_level(LED2);
            Key_clear_state(Key_Left);
        }
        if(Key_Get(Key_Right)==KEY_ShortPress)//右加(短按)
        {
            Menu_Second_E_Operate_Right();
            Key_clear_state(Key_Right);
        }
        if(Key_Get(Key_Enter)==KEY_ShortPress)//确定键盘
        {
            if(Line_A==0)
            {
                Facility_TO_Point(Step_Origin_TO_Center_X,Step_Origin_TO_Center_Y);
                system_delay_ms(1000);
            }
            if(Line_A==1)
            {
                Facility_TO_Point(position_P_X,position_P_Y);
            }
            if(Line_A==2)
            {
                Facility_TO_Point(0,0);
            }
            if(Line_A==3)
            {
                Facility_TO_Point(Step_Origin_TO_Center_X,Step_Origin_TO_Center_Y);//先到中心
                system_delay_ms(1000);
                Facility_Move_From_ATOB_Pixel(160,120,BlackChessPosition[0][0],BlackChessPosition[0][1]);
                system_delay_ms(1000);
                Chess_Grab();
                system_delay_ms(1000);
                Facility_Move_From_ATOB_Pixel(BlackChessPosition[0][0],BlackChessPosition[0][1],ChessPosition[4][0],ChessPosition[4][1]);
                system_delay_ms(1000);
                Chess_Put();
            }
            if(Line_A==4)
            {
                Facility_TO_Point(Step_Origin_TO_Center_X,Step_Origin_TO_Center_Y);//先到中心
                system_delay_ms(1000);
                Facility_Move_From_ATOB_Pixel(160,120,BlackChessPosition[1][0],BlackChessPosition[1][1]);
                system_delay_ms(1000);
                Chess_Grab();
                system_delay_ms(1000);
                Facility_Move_From_ATOB_Pixel(BlackChessPosition[1][0],BlackChessPosition[1][1],ChessPosition[4][0],ChessPosition[4][1]);
                system_delay_ms(1000);
                Chess_Put();
            }
            if(Line_A==5)
            {
                Facility_TO_Point(Step_Origin_TO_Center_X,Step_Origin_TO_Center_Y);//先到中心
                system_delay_ms(1000);
                Facility_Move_From_ATOB_Pixel(160,120,BlackChessPosition[2][0],BlackChessPosition[2][1]);
                system_delay_ms(1000);
                Chess_Grab();
                system_delay_ms(1000);
                Facility_Move_From_ATOB_Pixel(BlackChessPosition[2][0],BlackChessPosition[2][1],ChessPosition[4][0],ChessPosition[4][1]);
                system_delay_ms(1000);
                Chess_Put();
            }
            if(Line_A==6)
            {
                Facility_TO_Point(Step_Origin_TO_Center_X,Step_Origin_TO_Center_Y);//先到中心
                system_delay_ms(1000);
                Facility_Move_From_ATOB_Pixel(160,120,BlackChessPosition[3][0],BlackChessPosition[3][1]);
                system_delay_ms(1000);
                Chess_Grab();
                system_delay_ms(1000);
                Facility_Move_From_ATOB_Pixel(BlackChessPosition[3][0],BlackChessPosition[3][1],ChessPosition[4][0],ChessPosition[4][1]);
                system_delay_ms(1000);
                Chess_Put();
            }
            if(Line_A==7)
            {
                Facility_TO_Point(Step_Origin_TO_Center_X,Step_Origin_TO_Center_Y);//先到中心
                system_delay_ms(1000);
                Facility_Move_From_ATOB_Pixel(160,120,BlackChessPosition[4][0],BlackChessPosition[4][1]);
                system_delay_ms(1000);
                Chess_Grab();
                system_delay_ms(1000);
                Facility_Move_From_ATOB_Pixel(BlackChessPosition[4][0],BlackChessPosition[4][1],ChessPosition[4][0],ChessPosition[4][1]);
                system_delay_ms(1000);
                Chess_Put();
            }
            if(Line_A==8)
            {
                Facility_TO_Point(Step_Origin_TO_Center_X,Step_Origin_TO_Center_Y);//先到中心
                system_delay_ms(1000);
                Facility_Move_From_ATOB_Pixel(160,120,ChessPosition[4][0],ChessPosition[4][1]);
            }
            if(Line_A==LastLine)
            {
                menu2=0;
                break;
            }
            Key_clear_state(Key_Enter);
        }
    }
}

void Menu_Second_F_Operate_Right(void)
{
    switch(Line_A)
    {
        case 13:Select_Num+=1;ips200_show_int(72,16*13,Select_Num,4);break;
    }
}

void Menu_Second_F_Operate_Left(void)
{
    switch(Line_A)
    {
        case 13:Select_Num-=1;ips200_show_int(72,16*13,Select_Num,4);break;
    }
}

void Menu_Second_F(void)
{
    int Num = 0;
    ips200_clear();
    Line_A=0;
    FirstLine=0;
    LastLine=15;


    ips200_show_string(16,16*0,"Black:");
    for(int i = 1;i < 6;i++)
    {
        ips200_show_int(16,16*i,BlackChessPosition[i-1][0],4);ips200_show_int(100,16*i,BlackChessPosition[i-1][1],4);
    }
    ips200_show_string(16,16*6,"White:");
    for(int i = 7;i < 12;i++)
    {
        ips200_show_int(16,16*i,WhiteChessPosition[i-7][0],4);ips200_show_int(100,16*i,WhiteChessPosition[i-7][1],4);
    }
    ips200_show_string(16,16*12,"Nine: 11~19");

    ips200_show_string(16,16*13,"Choose:");ips200_show_int(72,16*13,Select_Num,4);
    ips200_show_string(16,16*14,"Move");

    ips200_show_chinese(16,16*LastLine,16,(const uint8 *)chinese_Back,2, RGB565_RED);
    Show_Row(Line_A,0);
    while(1)
    {
        ips200_show_string(0,16*19,"Line:");
        ips200_show_uint(40,16*19,Line_A,2);


//        //显示九宫格坐标信息
        if(!gpio_get_level(KEY_Down))
        {
            while(!gpio_get_level(KEY_Down));
            Line_A++;
            if(Line_A>LastLine){Line_A=FirstLine;}
            Show_Row(Line_A,FirstLine);
        }
        if(Key_Get(Key_Left)==KEY_ShortPress)//左减(短按)
        {
            Menu_Second_F_Operate_Left();
            Key_clear_state(Key_Left);
        }
        if(Key_Get(Key_Right)==KEY_ShortPress)//右加(短按)
        {
            Menu_Second_F_Operate_Right();
            Key_clear_state(Key_Right);
        }
        if(Key_Get(Key_Enter)==KEY_ShortPress)//确定键盘
        {
            if(Line_A==0)
            {
                UART3_READ_DATA();
            }
            if(Line_A==13)
            {
                if(Num < 4 && Select_Num >= 1 && Select_Num < 11)
                {
                    Point_Num_Select[Num] = Select_Num;
                    Point_Num_Select[Num] = Select_Num;
                }
                if(Num >= 4 && Num < 8 && Select_Num >= 11 && Select_Num < 20)
                {
                    Num_Select[Num-4] = Select_Num;
                    Num_Select[Num-4] = Select_Num;
                }
                Num++;
            }
            if(Line_A==14)
            {
                Question2_3();
            }
            if(Line_A==LastLine)
            {
                menu2=0;
                break;
            }
            Key_clear_state(Key_Enter);
        }
    }
}

void Menu_First_Operate_Right(void)
{
    switch(Line_A)
    {
        case 7:Facility_TO_Point(position_P_X,position_P_Y);DataMode=3;COLOR=0;uart3_send_Mode(DataMode,COLOR);
        ips200_show_string(112,16*7,"White");break;
    }
}

void Menu_First_Operate_Left(void)
{
    switch(Line_A)
    {
        case 7:Facility_TO_Point(position_P_X,position_P_Y);DataMode=3;COLOR=1;uart3_send_Mode(DataMode,COLOR);
        ips200_show_string(112,16*7,"Black");break;
    }
}

uint8 Menu_First(void)
{
    Line_A=0;//箭头所在行
    FirstLine=0;
    LastLine=8;
    ips200_clear();
    ips200_show_string(16,16*0,"Check_Motor");
    ips200_show_chinese(16,16*1,16,(const uint8 *)chinese_MenuFirst_A,4, RGB565_RED);
    ips200_show_chinese(16,16*2,16,(const uint8 *)chinese_MenuFirst_B,4, RGB565_RED);
    ips200_show_chinese(16,16*3,16,(const uint8 *)chinese_MenuFirst_C,4, RGB565_RED);
    ips200_show_string(16,16*4,"MENU_4");
    ips200_show_string(16,16*5,"Question1");
    ips200_show_string(16,16*6,"Question2_3");
    ips200_show_string(16,16*7,"DeviceColor:");
    Show_Row(Line_A,0);
    while(1)
    {
        if(!gpio_get_level(KEY_Down))
        {
            while(!gpio_get_level(KEY_Down));
            Line_A++;
            if(Line_A>LastLine){Line_A=FirstLine;}
            Show_Row(Line_A,FirstLine);
        }
        if(Key_Get(Key_Left)==KEY_ShortPress)//左减(短按)
        {
            Menu_First_Operate_Left();
            Key_clear_state(Key_Left);
        }
        if(Key_Get(Key_Right)==KEY_ShortPress)//右加(短按)
        {
            Menu_First_Operate_Right();
            Key_clear_state(Key_Right);
        }
        if(Key_Get(Key_Enter)==KEY_ShortPress)//确定键盘
        {
            if(Line_A==0)
            {
                Motor_Move_Check();
            }
            if(Line_A==1)
            {
//                menu2=1;
                UART3_READ_DATA();
                return menu2;
            }
            if(Line_A==2)
            {
                menu2=2;
                return menu2;
            }
            if(Line_A==3)
            {
                menu2=3;
                return menu2;
            }
            if(Line_A==4)
            {
                menu2=4;
                return menu2;
            }
            if(Line_A==5)
            {
                menu2=5;
                return menu2;
            }
            if(Line_A==6)
            {
                menu2=6;
                return menu2;
            }
            if(Line_A==7)
            {
                Question4();
            }
            Key_clear_state(Key_Enter);
        }
    }

}

void Menu_Switch(void)
{
    menu2=Menu_First();
    if(menu2 == 1){Menu_Second_A();}
    if(menu2 == 2){Menu_Second_B();}
    if(menu2 == 3){Menu_Second_C();}
    if(menu2 == 4){Menu_Second_D();}
    if(menu2 == 5){Menu_Second_E();}
    if(menu2 == 6){Menu_Second_F();}
}

