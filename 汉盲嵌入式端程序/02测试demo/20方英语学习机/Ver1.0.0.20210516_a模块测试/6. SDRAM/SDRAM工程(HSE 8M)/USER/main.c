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
u16 testsram[250000] __attribute__((at(0XC0000000)));//����������

//SDRAM�ڴ����	    
void fsmc_sdram_test(u16 x,u16 y)
{  
	u32 i=0;  	  
	u32 temp=0;	   
	u32 sval=0;	//�ڵ�ַ0����������	  				   
//  	LCD_ShowString(x,y,180,y+16,16,"Ex Memory Test:    0KB "); 
	//ÿ��16K�ֽ�,д��һ������,�ܹ�д��2048������,�պ���32M�ֽ�
	for(i=0;i<32*1024*1024;i+=16*1024)
	{
		*(vu32*)(Bank5_SDRAM_ADDR+i)=temp; 
		temp++;
	}
	//���ζ���֮ǰд�������,����У��		  
 	for(i=0;i<32*1024*1024;i+=16*1024) 
	{	
  		temp=*(vu32*)(Bank5_SDRAM_ADDR+i);
		if(i==0)sval=temp;
 		else if(temp<=sval)break;//�������������һ��Ҫ�ȵ�һ�ζ��������ݴ�.	   		   
//		LCD_ShowxNum(x+15*8,y,(u16)(temp-sval+1)*16,5,16,0);	//��ʾ�ڴ�����  
		
 	}	
	printf("SDRAM Capacity:%dKB\r\n",(u16)(temp-sval+1)*16);//��ӡSDRAM����	
}	

int main(void)
{
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
	TIM3_Init(10000-1,9000-1);       //��ʱ��3��ʼ������ʱ��ʱ��Ϊ90M����Ƶϵ��Ϊ9000-1��
                                    //���Զ�ʱ��3��Ƶ��Ϊ90M/9000=10K���Զ���װ��Ϊ5000-1����ô��ʱ�����ھ���500ms
	
	for(ts=0;ts<20;ts++)
	{
		testsram[ts]=ts;//Ԥ���������	 
	} 	
	
	while(1)
	{
//		key=KEY_Scan(0);//��֧������	
//		if(key==KEY_ENTER_PRESS)fsmc_sdram_test(30,170);//����SRAM����
//		else if(key==KEY_RETURN_PRESS)//��ӡԤ���������
//		{
//			for(ts=0;ts<20;ts++)
//			{
////				LCD_ShowxNum(30,190,testsram[ts],6,16,0);//��ʾ��������	
//				printf("testsram[%d]:%d\r\n",ts,testsram[ts]);
//			}
//		}
//		else ;
		if(flag==1)
		{
			HAL_TIM_Base_Stop_IT(&TIM3_Handler);
			printf("123\r\n");
			flag=0;
			HAL_TIM_Base_Start_IT(&TIM3_Handler);
			
		}
		
		delay_ms(1000);   
		
	}
}
