/***************************飞音云电子****************************
**  工程名称：YS-XFS5152语音合成配套程序
**	CPU: STC89LE52
**	晶振：22.1184MHZ
**	波特率：9600 bit/S
**	配套产品信息：YS-XFS5051语音合成模块
**                http://yuesheng001.taobao.com
**  作者：zdings
**  联系：751956552@qq.com
**  修改日期：2012.12.23
**  说明：用户在使用程序时，只需要编写好 串口发送函数PrintCom()；即可，
         直接调用本文件进行播放即可，在编写程序时，注意判断语音合成模
				 块的返回值，根据返回值进行下一次播放，如不接收返回值则无法进
				 行下一次播放。
/***************************飞音云电子******************************/
#include "config.h"
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

sbit SDA=P2^3;//定义数据线
sbit SCL=P2^2;//定义时钟线
bit flag;
//uint idata ucSendBuffer[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
//uint idata ucReceData;
//uint idata ucReceiveBuffer[8];//从器件中读出的多字节数据暂存区
void delay();
//void delay_10ms();
//void ACK();
//void NoACK();
/* ********************************************************
**名称：I2C_Start
**功能：启动I2C
**输入：无
**返回：无
******************************************************* */
void I2C_Start()
{
  SDA=1;
  _nop_();
  SCL=1;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  SDA=0;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  SCL=0;//钳位I2C总线，准备发送数据

}
/**********************************************************
**名称：I2C_Stop
**功能：停止I2C
**输入：无
**返回：无
**********************************************************/
void I2C_Stop()
{
  SDA=0;
    _nop_();
	 _nop_();
  SCL=1;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
   SDA=1;

}

/********************************************************
**名称：Test_Ack()
**功能：检测应答位
*********************************************************/
bit Test_Ack()
{ 
  SCL=0;
  delay();
  SDA=1;//读入数据
  delay();
  SCL=1;
  delay();
  if(SDA==0)
  flag=1;
  else flag=0;
  SCL=0;
  return(flag);
}

/********************************************************
**名称：SendData()  
**功能：发送一字节数据
**输入：buffer
**返回：
*******************************************************/
void SendData(uint8_t buffer)
{
  uint BitCnt=8;//一字节8位
  uint temp=0;
  do
  {
	  temp=buffer;
	  SCL=0;
	  //delay();
	  if((temp&0x80)==0) //判断最高位是0还是1
	  {
	  	SDA=0;
	  }
	  else
	  {
	  	SDA=1;
	  }
	   delay();
	   delay();
	  SCL=1;
	  //delay();
	  temp=buffer<<1;
	  buffer=temp;
	  BitCnt--;
  }
  while(BitCnt);
  SCL=0;  
}
/************************************************************************
功能描述： 	发送多字节数据
入口参数：	DAT:带发送的数据
返 回 值： 	none
其他说明：suba-数据地址，*s-写入的数据，n-写入的字节数
**************************************************************************/
uint8_t I2CSendData(uint8_t s[],uint8_t n)
{
  uint i;
  I2C_Start();//启动I2C
  SendData(0x80);//发送器件地址

  Test_Ack();
  if(flag==0) return(0);

  for(i=0;i<n;i++)
  {
  	SendData(s[i]);
    Test_Ack();
  	if(flag==0) return(0);
  }
  I2C_Stop();
  return(1);
}


void delay()
{
  uint i;
  for(i=10;i>0;i--)
  {
  	_nop_();
  }	 
}
