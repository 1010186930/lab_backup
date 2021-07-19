#include "sys.h"
#include "delay.h" 
#include "led.h"  
#include "usart.h" 
#include "lcd.h" 
#include "ltdc.h"   
#include "sdram.h"    
#include "malloc.h" 
#include "usmart.h"  
#include "w25qxx.h"  
#include "pcf8574.h"    
#include "sdio_sdcard.h"
#include "ff.h"  
#include "exfuns.h"  
#include "text.h"
#include "usbh_usr.h"
#include "key.h"
#include "readwrite.h"
#include "text.h"
#include "exti.h"
#include "timer.h"
#include "fattester.h"
/************************************************
 ALIENTEK ������STM32F429������ʵ��57
 USB U��(Host)ʵ��-HAL�⺯����
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com  
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

USBH_HOST  USB_Host;
USB_OTG_CORE_HANDLE  USB_OTG_Core;
FIL fil;
u8 demo=0;
u8 path[512]="3:";
int key_v;
//�û�����������
//����ֵ:0,����
//       1,������
u8 USH_User_App(void)
{  
	u32 total,free;
	u8 res=0;
	Show_Str(30,140,250,48,"�豸���ӳɹ�!.",32,0);	 
  	res=f_mount(fs[3],(const TCHAR*)"3:",1); 	//���¹���U��
	
	printf("f_mount res:%d\r\n",res);
	res=exf_getfree("3:",&total,&free);
	Scan_Directory(path);
	if(res==0)
	{
		POINT_COLOR=BLUE;//��������Ϊ��ɫ	   
		LCD_ShowString(30,190,250,48,32,"FATFS OK!");	
		LCD_ShowString(30,240,400,48,32,"U Disk Total Size:     MB");	 
		LCD_ShowString(30,290,400,48,32,"U Disk  Free Size:     MB"); 	    
		LCD_ShowNum(320,240,total>>10,5,32);//��ʾU�������� MB
		LCD_ShowNum(320,290,free>>10,5,32);	
		
	} 
	
	while(HCD_IsDeviceConnected(&USB_OTG_Core))//�豸���ӳɹ�
	{	
		LED1=!LED1;
		delay_ms(500);
	}
	LED1=1;				//�ر�LED1 
 	f_mount(0,(const TCHAR*)"3:",1); 	//ж��U��
	printf("dis f_mount\r\n");
	POINT_COLOR=RED;//��������Ϊ��ɫ	   
	Show_Str(30,140,250,48,"�豸������...",32,0);
	LCD_Fill(30,180,500,500,WHITE); 
	return res;
} 
int main(void)
{
    Stm32_Clock_Init(384,25,2,8);   //����ʱ��,192Mhz   
    delay_init(192);                //��ʼ����ʱ����
    uart_init(115200);              //��ʼ��USART
//    usmart_dev.init(96);
	KEY_Init();
   	LED_Init();					//��ʼ����LED���ӵ�Ӳ���ӿ�
	SDRAM_Init();				//��ʼ��SDRAM 
	LCD_Init();					//��ʼ��LCD 
	W25QXX_Init();				//��ʼ��W25Q256 
	PCF8574_Init();				//��ʼ��PCF8574
 	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ��
	my_mem_init(SRAMEX);		//��ʼ���ⲿ�ڴ��
	my_mem_init(SRAMCCM);		//��ʼ��CCM�ڴ�� 
	exfuns_init();				//Ϊfatfs��ر��������ڴ�  
	EXTI_Init();                //�ⲿ�жϳ�ʼ��
//	TIM3_Init(100-1,9600-1);
 	f_mount(fs[0],(const TCHAR*)"0:",1); 		//����SD�� 
 	f_mount(fs[1],(const TCHAR*)"1:",1); 		//����SPI FLASH. 
 	f_mount(fs[2],(const TCHAR*)"2:",1); 		//����NAND FLASH. 
	POINT_COLOR=RED;      
 	while(font_init()) 				//����ֿ�
	{	    
		LCD_ShowString(60,50,200,16,32,"Font Error!");
		delay_ms(200);				  
		LCD_Fill(60,50,240,66,WHITE);//�����ʾ	     
		delay_ms(200);				  
	}
	Show_Str(30,140,250,48,"�豸������...",32,0);			 		
	//��ʼ��USB����
  	USBH_Init(&USB_OTG_Core,USB_OTG_FS_CORE_ID,&USB_Host,&USBH_MSC_cb,&USR_cb); 
	while(1)
	{
		USBH_Process(&USB_OTG_Core, &USB_Host);
//		Key_Detect();
		delay_ms(1);
	}	
}

