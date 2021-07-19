#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "key.h"
#include "usmart.h"
#include "malloc.h"
#include "sdio_sdcard.h"
#include "w25qxx.h"
#include "ff.h"
#include "exfuns.h"
#include "text.h"


int main(void)
{
	  volatile u32 j=0xFFC7FFAD;
    volatile u8 i=(u8)j;
	 
	
    Stm32_Clock_Init(9);		//ϵͳʱ������
    uart_init(72,115200);		//���ڳ�ʼ��Ϊ115200
    delay_init(72);	   	 		//��ʱ��ʼ��
    usmart_dev.init(72);		//��ʼ��USMART
    LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
    KEY_Init();					//��ʼ������
    LCD_Init();			   		//��ʼ��LCD
    W25QXX_Init();				//��ʼ��W25Q128
    font_init();
    LCD_Clear(YELLOW);		   	//����


    for(i=0; i<5; i++)
    {
        LCD_Draw_Ellipse(400,240,300+i,200+i,BLACK);
    }
    POINT_COLOR=PINK;
    for(i=0; i<10; i++)
    {
        LCD_DrawRectangle(320+i,270+i,480-i,350-i);
    }
    POINT_COLOR=BLUE;
		BACK_COLOR=RED;
		
    Show_Str(300,208,50,32,"��",32,1);
//    POINT_COLOR=BLACK;
//    Show_Str(348,224,50,16,"ѧϰ",16,1);


    while(1)
    {
        LED0=!LED0;
        delay_ms(100);
    }
}










