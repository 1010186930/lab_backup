#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "tts.h"
/************************************************
 ALIENTEK��ӢSTM32������ʵ��4
 ���� ʵ��
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/
int main(void)
{
    u8 key_v;
    u16 t;
    u16 len;
    u16 times=0;
    delay_init();	    	 //��ʱ������ʼ��
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
    LED_Init();			     //LED�˿ڳ�ʼ��
    KEY_Init();          //��ʼ���밴�����ӵ�Ӳ���ӿ�

    while(1)
    {
        LED0=!LED0;//��˸LED,��ʾϵͳ��������.
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

