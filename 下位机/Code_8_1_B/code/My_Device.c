#include "common.h"

//#include "ALL_Variables.h"


void Init_All(void)
{
    gpio_init(KEY_Down, GPI, GPIO_HIGH, GPI_PULL_UP);//四个按键初始化
    gpio_init(KEY_Left, GPI, GPIO_HIGH, GPI_PULL_UP);
    gpio_init(KEY_Right, GPI, GPIO_HIGH, GPI_PULL_UP);
    gpio_init(KEY_Enter, GPI, GPIO_HIGH, GPI_PULL_UP);

    gpio_init(LED1, GPO, GPIO_HIGH, GPO_PUSH_PULL);//四个LED灯
    gpio_init(LED2, GPO, GPIO_HIGH, GPO_PUSH_PULL);
    gpio_init(LED3, GPO, GPIO_HIGH, GPO_PUSH_PULL);
    gpio_init(LED4, GPO, GPIO_HIGH, GPO_PUSH_PULL);

    gpio_init(DIR_X_Left, GPO, GPIO_HIGH, GPO_PUSH_PULL);//四个步进电机方向初始化
    gpio_init(DIR_X_Right,GPO, GPIO_HIGH, GPO_PUSH_PULL);
    gpio_init(DIR_Y, GPO, GPIO_HIGH, GPO_PUSH_PULL);
    gpio_init(DIR_Z, GPO, GPIO_HIGH, GPO_PUSH_PULL);

    gpio_init(PWM_X_Left, GPO, GPIO_HIGH, GPO_PUSH_PULL);//三个步进电机PWM输出的IO口初始化
    gpio_init(PWM_X_Right,GPO, GPIO_HIGH, GPO_PUSH_PULL);
    gpio_init(PWM_Y, GPO, GPIO_HIGH, GPO_PUSH_PULL);
    gpio_init(PWM_Z, GPO, GPIO_HIGH, GPO_PUSH_PULL);

    gpio_init(Chess_Gripper, GPO, GPIO_HIGH, GPO_PUSH_PULL);

    ips200_init(IPS200_TYPE_PARALLEL8);//双排

//    gpio_init(P21_2, GPO, GPIO_LOW, GPO_PUSH_PULL);
//    gpio_init(P21_4, GPO, GPIO_LOW, GPO_PUSH_PULL);
//    gpio_init(P21_3, GPO, GPIO_LOW, GPO_PUSH_PULL);
//    gpio_init(P21_5, GPO, GPIO_LOW, GPO_PUSH_PULL);
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     按键状态扫描
// 使用示例     Key_Scan();
// 备注信息     这个函数放在主循环或者 PIT 中断中
// 备注信息     按键按下key_press_time开始自增，计数大为长按，计数小分为短按和没按
// 备注信息     此函数在定时器3中调用，执行时给按键赋予状态，存储在Key_State[]中
//-------------------------------------------------------------------------------------------------------------------
void Key_Scan(void)
{
    uint8 i=0;
    for(i = 0;i<5; i ++)
    {
        if( !gpio_get_level(Key_index[i]))//按键按下开始计数，计数大为长按，计数小分为短按和没按
        {
            key_press_time[i]++;
            if(key_press_time[i]>=KEY_LongPress_Period)//长时间按下
            {
                Key_State[i]=KEY_LongPress;
            }
        }
        else
        {
            if((Key_State[i]!=KEY_LongPress) && (key_press_time[i]>=KEY_ShortPress_Period))
            {
                Key_State[i]=KEY_ShortPress;
            }
            else
            {
                Key_State[i]=KEY_Release;
            }
            key_press_time[i]=0;
         }
    }
}
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     按键状态获取
// 使用示例     if(Key_Get(Key_Up)==KEY_Release);//对按键状态进行判断
// 备注信息     此函数用在屏幕操作上
//-------------------------------------------------------------------------------------------------------------------
KEY_State Key_Get(Key_index_enum pin)
{
    return Key_State[pin];
}
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     按键状态清除
// 使用示例     Key_clear_state(Key_Up);
// 备注信息     此函数放在按键状态获取的结尾;实际松手过后，按键扫描扫到此按键时就已经会给按键状态清零，此函数用于双重保险
//-------------------------------------------------------------------------------------------------------------------
void Key_clear_state (Key_index_enum key_n)
{
    Key_State[key_n] = KEY_Release;
}


