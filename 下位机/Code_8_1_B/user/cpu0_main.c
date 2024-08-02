/*********************************************************************************************************************
* TC264 Opensourec Library 即（TC264 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是 TC264 开源库的一部分
*
* TC264 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          cpu0_main
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          ADS v1.9.4
* 适用平台          TC264D
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期              作者                备注
* 2022-09-15       pudding            first version
********************************************************************************************************************/
#include "common.h"
#pragma section all "cpu0_dsram"
// 将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中
// **************************** 代码区域 ****************************
//#define IPS200_TYPE     (IPS200_TYPE_PARALLEL8)                                 // 双排排针 并口两寸屏 这里宏定义填写 IPS200_TYPE_PARALLEL8
//                                                                                // 单排排针 SPI 两寸屏 这里宏定义填写 IPS200_TYPE_SPI
int core0_main(void)
{
    clock_init();                   // 获取时钟频率<务必保留>
    debug_init();                   // 初始化默认调试串口
    // 此处编写用户代码 例如外设初始化代码等

    Init_All();

    pit_us_init(CCU60_CH0,1000);//可以通过修改这个定时器的频率实现步进电机速度调制
    pit_ms_init(CCU60_CH1,1);//按键扫描定时器

//    pwm_init(ATOM0_CH4_P02_4,Fre_A,5000);

    uart_init(UART_3,115200,UART3_TX_P15_6,UART3_RX_P15_7);//接在定位模块的通信
    uart_rx_interrupt(UART_3,1);

//    Motor_Move_Check();
    // 此处编写用户代码 例如外设初始化代码等
	cpu_wait_event_ready();         // 等待所有核心初始化完毕
	while (TRUE)
	{
	    Menu_Switch();

//        if(Key_Get(Key_Left)==KEY_ShortPress)
//        {
////            pwm_set_duty(ATOM0_CH4_P02_4,0);
//            gpio_set_level(P20_10,0);
//            gpio_toggle_level(LED2);
//            Key_clear_state(Key_Left);
//        }
//        if(Key_Get(Key_Right)==KEY_ShortPress)
//        {
////            pwm_set_duty(ATOM0_CH4_P02_4,5000);
//            gpio_set_level(P20_10,1);
//            gpio_toggle_level(LED3);
//            Key_clear_state(Key_Right);
//        }
//        if(Key_Get(Key_Enter)==KEY_ShortPress)
//        {
//            Key_clear_state(Key_Enter);
//        }
//	    if(!gpio_get_level(KEY_Down))
//	    {
//	        while(!gpio_get_level(KEY_Down));
//	        gpio_toggle_level(LED1);
//	    }
	}
}

#pragma section all restore
// **************************** 代码区域 ****************************

// *************************** 例程常见问题说明 ***************************
// 遇到问题时请按照以下问题检查列表检查
// 问题1：屏幕不显示
//      如果使用主板测试，主板必须要用电池供电 检查屏幕供电引脚电压
//      检查屏幕是不是插错位置了 检查引脚对应关系
//      如果对应引脚都正确 检查一下是否有引脚波形不对 需要有示波器
//      无法完成波形测试则复制一个GPIO例程将屏幕所有IO初始化为GPIO翻转电平 看看是否受控
