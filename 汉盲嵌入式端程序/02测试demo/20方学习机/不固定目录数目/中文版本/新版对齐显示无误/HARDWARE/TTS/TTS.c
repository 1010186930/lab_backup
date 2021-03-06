 /*	 
 引脚链接用的串口3
 
 VCC--+5V
 GND--GND
 
 BUSY--PD2
 
 RXD--PB10
 TXD--PB11
 
 喇叭按电路图正负接

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

//发声程序
#define LEN_OFFSET    2  //长度字节的偏移量（本例中长度不超过255字节，因此只使用1字节长度）

//数据包头（0xFD + 2字节长度 + 1字节命令字 + 1字节命令参数)
unsigned char head[] = {0xfd,0x00,0x17,0x01,0x00};
//命令参数：0，设置文本为GB2312编码格式；1，设置文本为GBK编码格式
//3，设置文本为UNICODE编码格式
    /****/	 

/*void TTS_Init(void)
{
	  
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	 //使能PD端口时钟
	
 GPIO_InitStructure.GPIO_Pin =GPIO_Pin_2;				 //
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOD, &GPIO_InitStructure);					 //根据设定参数初始化GPIOD.6		
 		
}

void Speech(unsigned char *buf, unsigned char len)
{
	//TTS_Init();
	int i = 0;          //循环计数变量
	char xor = 0x00;     //校验码初始化
			
	head[LEN_OFFSET] = len + 3;  //计算正文长度（1命令字 + 1命令参数 + 文字长度 + 1校验位）

	//发送数据包头（0xFD + 2字节长度 + 1字节命令字 + 1字节命令参数)
	for(i = 0; i < 5; i++)
	{
		xor ^= head[i];
	//	UART3_SendByte(head[i]);
		UART3_SendByte(head[i]);
		//UART2_SendByte(head[i]);
		
		delay_ms(2);
   	}

	//发送文字内容
	for(i = 0; i < len; i++)
	{
		xor ^= buf[i];
		UART3_SendByte(buf[i]);
		delay_ms(2);
	}

 UART3_SendByte(xor);        //发送校验位
}//发送完语句后要加入发送是否完成的判断程序，
//可以通过查询或者中断方式进行判断当前芯片的工作状态，然后才能发送下一个数据。
*/


void SPeech(char *buf)
{
  unsigned char len[100];
	unsigned int buflen;
	buflen=strlen(buf);
	//固定配置信息,包头
	len[0]=0xFD;
	len[1]=0x00;
	len[2]=buflen+2;
	len[3]=0x01;
	len[4]=0x01;
//发送数据	
	
	memcpy(&len[5],buf,buflen);
	PrintCom(len,5+buflen);
//	int i;
//	for(i=0;i<5+buflen;i++)
//	{
// USART_SendData(USART3,*len++);
//		while(USART_GetFlagStatus(USART3_FLAG_TC)==RESET);
	
}
void SPeechUni(u16* buf)
{
	u8 cnt = 0;
	u8 realcnt = 0;
	u8 len[128] = {0x00};
	u8 i = 0;
	u8 high = 0x00;
	u8 low = 0x00;
	u16* p=buf ;
	//固定配置信息,包头
	while (*buf != 0x00)
	{
		cnt++;
		buf++;
	}
		
	realcnt = cnt * 2;
	len[0] = 0xFD;
	len[1] = 0x00;
	len[2] = realcnt + 2;
	len[3] = 0x01;
	len[4] = 0x03;
	//发送数据	
	
	
	for (i = 0; i < cnt; i++)
	{
		high = *p >> 8;
		low = *p & 0xFF;
		len[5 + i*2]=low;
		len[6 + i*2]=high;
		
		
		p++;
	}
	PrintCom(len,5+realcnt);
}
