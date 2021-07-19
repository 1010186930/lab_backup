#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "exti.h"
#include "dot_driver.h"
#include "key.h"
#include "string.h"
/************************************************
 ALIENTEK ������STM32F429������ ʵ��1
 �����ʵ��-HAL��汾
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/




/*������������ʹ��HAL�⺯��ʵ�ֿ���IO�����*/
 
int main(void)
{
	int i=0;
	unsigned char InputBraille[121]="101101011010110101101011010110101101011010110101101011010110101101011010110101101011010110101101011010110101101011010110";
	unsigned char InputToIO[15]={0x00};
    HAL_Init();                     //��ʼ��HAL��   
    Stm32_Clock_Init(360,25,2,8);   //����ʱ��,180Mhz
    delay_init(180);                //��ʼ����ʱ����
	DOT_Init();
	EXTI_Init();
//	KEY_Init();
	Dot_Control(ALLDOWN);
//	Braille_Display(InputBraille,120,InputToIO);


	
    while(1)
    {
//        key=KEY_Scan(0);
//		if(key==KEY_NEXT_PRESS)
//			Dot_Control(ALLDOWN);
//		else if(key==KEY_PREVIOUS_PRESS)
			Dot_Control(ALLUP);
    }
}
 

 
/*����������ʹ��λ������ʵ�֣�*/
/*
int main(void)
{ 
    HAL_Init();                     //��ʼ��HAL��   
    Stm32_Clock_Init(360,25,2,8);   //����ʱ��,180Mhz
    delay_init(180);                //��ʼ����ʱ����
    LED_Init();                     //��ʼ��LED    while(1)
	{
         LED0=0;			     //LED0��
	     LED1=1;				 //LED1��
		 delay_ms(500);
		 LED0=1;				//LED0��
		 LED1=0;				//LED1��
		 delay_ms(500);
	 }
}*/




/*
����������ʹ��ֱ�Ӳ����������ʽʵ�������
*/
/*
int main(void)
{ 
    HAL_Init();                     //��ʼ��HAL��   
    Stm32_Clock_Init(360,25,2,8);   //����ʱ��,180Mhz
    delay_init(180);                //��ʼ����ʱ����
    LED_Init();                     //��ʼ��LED  
	while(1)
	{
      GPIOB->BSRR=GPIO_PIN_1;     //LED0��
	  GPIOB->BSRR=GPIO_PIN_0<<16; //LED1��
	  delay_ms(500);
      GPIOB->BSRR=GPIO_PIN_1<<16; //LED0��
	  GPIOB->BSRR=GPIO_PIN_0;     //LED1��
	  delay_ms(500);
	 }
 }	
*/




