#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "exti.h"
/************************************************
 ALIENTEK ������STM32F429������ʵ��4
 �ⲿ�ж�-HAL�⺯����
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

int main(void)
{
    HAL_Init();                     //��ʼ��HAL��   
    Stm32_Clock_Init(360,25,2,8);   //����ʱ��,180Mhz
    delay_init(180);                //��ʼ����ʱ����
	    
    uart_init(115200);              //��ʼ��USART
	EXTI_Init();                    //�ⲿ�жϳ�ʼ��
    LED_Init();                     //��ʼ��LED 

    while(1)
    {
		
       
		//��ӡOK��ʾ��������
		__HAL_UART_DISABLE(&UART1_Handler);
		printf("\r\nALIENTEK ������STM32F429������ ����ʵ��\r\n\r\n"); 
		LED1=1;
        delay_ms(100);             //ÿ��1s��ӡһ�� 
		uart_init(115200);
		printf("\r\n123\r\n\r\n"); 		
		LED1=0;
		delay_ms(100);   
    }
}

