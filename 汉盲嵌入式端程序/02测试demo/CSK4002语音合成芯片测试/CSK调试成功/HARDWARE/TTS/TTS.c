 /*	 
 ���������õĴ���3
 
 VCC--+5V
 GND--GND
 
 BUSY--PD2
 
 RXD--PB10
 TXD--PB11
 
 ���Ȱ���·ͼ������

 */
#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "tts.h"



void PrintCom(u8 *DAT,u8  num)
{
  u8 i;
	for(i=0;i<num;i++)
	{
	  USART_SendData(USART2,DAT[i]);
//		delay_ms(2);//2ms�ӳ�̫���ˣ�
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);
	}
}
void Status_Query()
{
	u8 t;
  u8 len[4]={0xFD,0x00,0x01,0x21};
	for(t=0;t<4;t++)
	{
		USART_SendData(USART2, len[t]);//�򴮿�1��������
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
	}
}

void SPeech(u8 *buf)
{
  u8 len[100]={0x00};
	u8 buflen;
	buflen=strlen(buf);
	len[0]=0xFD;
	len[1]=0x00;
	len[2]=buflen+0x02;
	len[3]=0x01;
	len[4]=0x01;
	memcpy(&len[5],buf,buflen);
	PrintCom(len,5+buflen);	
}






