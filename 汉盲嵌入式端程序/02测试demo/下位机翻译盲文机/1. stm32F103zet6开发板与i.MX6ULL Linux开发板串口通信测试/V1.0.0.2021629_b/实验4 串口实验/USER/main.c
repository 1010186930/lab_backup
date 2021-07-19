#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "BrailleUSART.h"
#include "timer.h"
#include "BrailleProtocol.h"
#include "exti.h"
/************************************************
 ALIENTEK��ӢSTM32������ʵ��4
 ���� ʵ��   
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/
u8 buffer1[121]="";
u8 dot_cnt=0;
u8 text_cnt=0;
u8 testbuf[65]={0xe4,0xb9,0x8b,0xe6,0xb1,0x9f,0xe5,0xae,0x9e,0xe9,0xaa,0x8c,0xe5,0xae,0xa4};
 int main(void)
 {		
 	  
	 u8 i=0;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	BraillieUSART_Init(115200);
 	LED_Init();			     //LED�˿ڳ�ʼ��
	EXTIX_Init();
	TIM3_Init(40-1,7200-1);
	 for(i=0; i<sizeof(testbuf)/sizeof(u8); i++)
		{
			if(testbuf[i]!=0x00)
				text_cnt++;
		}
 	while(1)
	{
		UnpackedDot(buffer1,&dot_cnt);
//		printf("123\r\n");
		
		delay_ms(50);
		
	}	 
 }

