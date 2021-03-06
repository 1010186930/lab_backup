#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "tts.h"
/************************************************
 ALIENTEK精英STM32开发板实验4
 串口 实验
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司
 作者：正点原子 @ALIENTEK
************************************************/
int main(void)
{
    u8 key_v;
    u16 t;
    u16 len;
    u16 times=0;
    delay_init();	    	 //延时函数初始化
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    uart_init(115200);	 //串口初始化为115200
    LED_Init();			     //LED端口初始化
    KEY_Init();          //初始化与按键连接的硬件接口

    while(1)
    {
        LED0=!LED0;//闪烁LED,提示系统正在运行.
        delay_ms(100);
        key_v=KEY_Scan(0);
        if(key_v==1)
        {
            SPeech("My father, brother and I visited West Point to see a football game between Army and Boston College.");
        }
        else if(key_v==2)
        {
            SPeech("Taking a stroll before kickoff, we met many cadets in neatly pressed uniforms.");

        }
        else if(key_v==3)
        {
            SPeech("to show our son what to expect if he should attend West Point.");
        }

    }
}

