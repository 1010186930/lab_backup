#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "sdram.h"
#include "timer.h"
/************************************************
 ALIENTEK ������STM32F429������ʵ��13
 SDRAMʵ��-HAL�⺯����
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com  
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/
u8 flag=0;



int main(void)
{
	u8 x=0;
  	u8 lcd_id[12];
	u8 key;		 
	u8 i=0;	     
	u32 ts=0; 
    HAL_Init();                     //��ʼ��HAL��   
    Stm32_Clock_Init(180,4,2,4);   //����ʱ��,180Mhz
    delay_init(180);                //��ʼ����ʱ����
    uart_init(115200);              //��ʼ��USART
//    LED_Init();                     //��ʼ��LED 
    KEY_Init();                     //��ʼ������
    SDRAM_Init();                   //��ʼ��SDRAM
	LCD_Init();                     //LCD��ʼ��
	TIM3_Init(10000-1,9000-1);       //��ʱ��3��ʼ������ʱ��ʱ��Ϊ90M����Ƶϵ��Ϊ9000-1��
                                    //���Զ�ʱ��3��Ƶ��Ϊ90M/9000=10K���Զ���װ��Ϊ5000-1����ô��ʱ�����ھ���500ms
	POINT_COLOR=RED; 
	BACK_COLOR=YELLOW;
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//��LCD ID��ӡ��lcd_id���顣	
	while(1)
	{
		switch(x)
		{
			case 0:LCD_Clear(WHITE);break;
			case 1:LCD_Clear(BLACK);break;
			case 2:LCD_Clear(BLUE);break;
			case 3:LCD_Clear(RED);break;
			case 4:LCD_Clear(MAGENTA);break;
			case 5:LCD_Clear(GREEN);break;
			case 6:LCD_Clear(CYAN);break; 
			case 7:LCD_Clear(YELLOW);break;
			case 8:LCD_Clear(BRRED);break;
			case 9:LCD_Clear(GRAY);break;
			case 10:LCD_Clear(LGRAY);break;
			case 11:LCD_Clear(BROWN);break;
		}
		POINT_COLOR=RED;	  
		LCD_ShowString(10,40,260,32,32,"LTDC TEST"); 	
		
 		LCD_ShowString(10,130,240,32,32,lcd_id);		//��ʾLCD ID	      					 
		
		x++;
		if(x==12)x=0;  
		delay_ms(1000);			
//		if(flag==1)
//		{
//			HAL_TIM_Base_Stop_IT(&TIM3_Handler);
//			printf("123\r\n");
//			flag=0;
//			HAL_TIM_Base_Start_IT(&TIM3_Handler);
//			
//		}
//		
//		delay_ms(1000);   
		
	}
}
