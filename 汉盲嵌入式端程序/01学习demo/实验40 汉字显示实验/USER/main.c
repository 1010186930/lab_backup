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
#include "timer.h"
#include "touni.h"
#include "stdio.h"
#include "string.h"
/************************************************
 ALIENTEKս��STM32������ʵ��40
 ������ʾ ʵ�� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/


 int main(void)
 {	
	u16 univalue;
	u8 high;
	u8 low;
	u32 fontcnt;		  
	u8 i,j;
	u8 fontx[2]="";//gbk��
	u8 key,t;   	    
//	u16 unibuf[64]={0x0000};
	//u8 utfscr[] = {0x20,0xe6,0xa0,0x87,0xe9,0xa2,0x98,0x20,0x3c,0x3c,0xe6,0x97,0xa7,0xe9,0x9b,0xa8,0xe6,0xa5,0xbc,0xc2,0xb7,0xe5,0x8f,0xa4,0xe9,0xbe,0x99,0xe3,0x80,0x8a,0xe7,0x99,0xbd,0xe7,0x8e,0x89,0xe9,0x9b,0x95,0xe9,0xbe,0x99,0xe3,0x80,0x8b,0x3e,0x3e };
//	u8 utfscr[]="你好我叫林栋";
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	usmart_dev.init(72);		//��ʼ��USMART		
 	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();					//��ʼ������
	LCD_Init();			   		//��ʼ��LCD   
	W25QXX_Init();				//��ʼ��W25Q128
	TIM3_Int_Init(4999,7199);//10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms  
//	 LCD_ShowString(30,70,200,16,32,"Erase Start");
//		W25QXX_Erase_Chip();
//	while(1)
//	{
//		
//		LCD_ShowString(30,70,200,16,32,"Erase OK");
//	}
 	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ��
	exfuns_init();				//Ϊfatfs��ر��������ڴ�  
 	f_mount(fs[0],"0:",1); 		//����SD�� 
// 	f_mount(fs[1],"1:",1); 		//����FLASH.
	while(font_init()) 			//����ֿ�
	{
UPD:    
		LCD_Clear(WHITE);		   	//����
 		POINT_COLOR=RED;			//��������Ϊ��ɫ	   	   	  
		
		while(SD_Init())			//���SD��
		{
			LCD_ShowString(30,80,240,32,32,"SD Card Failed!");
			delay_ms(200);
			LCD_Fill(30,80,270,112,WHITE);
			delay_ms(200);		    
		}								 						    
		LCD_ShowString(30,80,240,32,32,"SD Card OK");
		LCD_ShowString(30,112,256,32,32,"Font Updating...");
		key=update_font(30,144,32,"0:");//�����ֿ�
		while(key)//����ʧ��		
		{			 		  
			LCD_ShowString(30,112,200,32,32,"Font Update Failed!");
			delay_ms(200);
			LCD_Fill(30,112,230,110,WHITE);
			delay_ms(200);		       
		} 		  
		LCD_ShowString(30,112,200,32,32,"Font Update Success!   ");
		delay_ms(1500);	
		LCD_Clear(WHITE);//����	       
	}  
//	POINT_COLOR=RED;       
//	Show_GBKStr(30,176,200,32,"��KEY0,�����ֿ�",32,0);
// 	POINT_COLOR=BLUE;  
//	Show_GBKStr(30,208,200,32,"������ֽ�:",32,0);				    	 
//	Show_GBKStr(30,240,200,32,"������ֽ�:",32,0);				    	 
//	Show_GBKStr(30,272,200,32,"���ּ�����:",32,0);
//	Show_GBKStr(30,304,290,32,"��Ӧ����(32*32)Ϊ:",32,0); 
	POINT_COLOR=RED;       
//	Show_UTF8Str(0,176,500,32,utfscr,unibuf,32,sizeof(utfscr)/sizeof(u8),0);
 	POINT_COLOR=BLUE;  
	Show_GBKStr(30,208,200,32,"������ֽ�:",32,0);				    	 
	Show_GBKStr(30,240,200,32,"������ֽ�:",32,0);				    	 
	Show_GBKStr(30,272,200,32,"���ּ�����:",32,0);
	Show_GBKStr(30,304,290,32,"��Ӧ����(32*32)Ϊ:",32,0); 		 
	while(1)
	{
		fontcnt=0;
		for(univalue=0x4e00;univalue<=0x9FFF;univalue++,fontcnt++)
		{
			high=(univalue>>8);
			low=univalue&0xFF;
			sprintf((char*)fontx,"%x",high);
			LCD_ShowString(222,208,100,32,32,fontx);
			sprintf((char*)fontx,"%x",low);
//			LCD_ShowNum(222,208,univalue>>8,3,32);		//��ʾ������ֽ�
			LCD_ShowString(222,240,100,32,32,fontx);
//			LCD_ShowNum(222,240,univalue&0xFF,3,32);	//��ʾ������ֽ�	 
			LCD_ShowNum(222,272,fontcnt,5,32);//���ּ�����ʾ	
			Show_UNIStr(318,304,100,32,&univalue,32,0);
			t=200;
			while(t--)//��ʱ,ͬʱɨ�谴��
			{
				delay_ms(1);
				key=KEY_Scan(0);
				if(key==KEY0_PRES)goto UPD;
			}
				LED0=!LED0;
		}
//		fontcnt=0;
//		for(i=0x81;i<0xff;i++)
//		{		
//			fontx[0]=i;
//			LCD_ShowNum(222,208,i,3,32);		//��ʾ������ֽ�    
//			for(j=0x40;j<0xfe;j++)
//			{
//				if(j==0x7f)continue;
//				fontcnt++;
//				LCD_ShowNum(222,240,j,3,32);	//��ʾ������ֽ�	 
//				LCD_ShowNum(222,272,fontcnt,5,32);//���ּ�����ʾ	 
//			 	fontx[1]=j;
//				Show_GBKFont(318,304,fontx,32,0);	  
//				Show_GBKStr(318,340,100,32,fontx,32,0);
//				Show_GBKStr(318,380,100,32,test,32,0);
//				t=200;
//				while(t--)//��ʱ,ͬʱɨ�谴��
//				{
//					delay_ms(1);
//					key=KEY_Scan(0);
//					if(key==KEY0_PRES)goto UPD;
//				}
//				LED0=!LED0;
//			}   
//		}	
	} 
}

















