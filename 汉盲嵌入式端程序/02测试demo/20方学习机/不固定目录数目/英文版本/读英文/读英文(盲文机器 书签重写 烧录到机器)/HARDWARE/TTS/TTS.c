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



void PrintCom(uint8_t *DAT,uint8_t len)
{
  uint8_t i;
	for(i=0;i<len;i++)
	{
	  USART_SendData(USART3,*DAT++);
			delay_ms(2);
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET);
		
	}
}

/*

//��������
#define LEN_OFFSET    2  //�����ֽڵ�ƫ�����������г��Ȳ�����255�ֽڣ����ֻʹ��1�ֽڳ��ȣ�

//���ݰ�ͷ��0xFD + 2�ֽڳ��� + 1�ֽ������� + 1�ֽ��������)
unsigned char head[] = {0xfd,0x00,0x17,0x01,0x00};
//���������0�������ı�ΪGB2312�����ʽ��1�������ı�ΪGBK�����ʽ
//3�������ı�ΪUNICODE�����ʽ
    /****/	 

/*void TTS_Init(void)
{
	  
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	 //ʹ��PD�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin =GPIO_Pin_2;				 //
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOD, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOD.6		
 		
}

void Speech(unsigned char *buf, unsigned char len)
{
	//TTS_Init();
	int i = 0;          //ѭ����������
	char xor = 0x00;     //У�����ʼ��
			
	head[LEN_OFFSET] = len + 3;  //�������ĳ��ȣ�1������ + 1������� + ���ֳ��� + 1У��λ��

	//�������ݰ�ͷ��0xFD + 2�ֽڳ��� + 1�ֽ������� + 1�ֽ��������)
	for(i = 0; i < 5; i++)
	{
		xor ^= head[i];
	//	UART3_SendByte(head[i]);
		UART3_SendByte(head[i]);
		//UART2_SendByte(head[i]);
		
		delay_ms(2);
   	}

	//������������
	for(i = 0; i < len; i++)
	{
		xor ^= buf[i];
		UART3_SendByte(buf[i]);
		delay_ms(2);
	}

 UART3_SendByte(xor);        //����У��λ
}//����������Ҫ���뷢���Ƿ���ɵ��жϳ���
//����ͨ����ѯ�����жϷ�ʽ�����жϵ�ǰоƬ�Ĺ���״̬��Ȼ����ܷ�����һ�����ݡ�
*/


void SPeech(char *buf)
{
  unsigned char len[100];
	unsigned int buflen;
	buflen=strlen(buf);
	//�̶�������Ϣ,��ͷ
	len[0]=0xFD;
	len[1]=0x00;
	len[2]=buflen+2;
	len[3]=0x01;
	len[4]=0x01;
//��������	
	
	memcpy(&len[5],buf,buflen);
	PrintCom(len,5+buflen);
//	int i;
//	for(i=0;i<5+buflen;i++)
//	{
// USART_SendData(USART3,*len++);
//		while(USART_GetFlagStatus(USART3_FLAG_TC)==RESET);
	
}
