/***************************飞音云电子****************************
**  工程名称：YS-XFS5152语音合成测试程序
**	CPU: STC89LE52
**	晶振：22.1184MHZ
**	波特率：9600 bit/S
**	配套产品信息：YS-语音识别模块
**                http://yuesheng001.taobao.com
**  作者：zdings
**  联系：751956552@qq.com
**  修改日期：2012.8.25
**  说明：本程序 具备语音合成功能
				 用户在使用程序时，只需要编写好 串口发送函数PrintCom()；即可，
         直接调用本文件进行播放即可，在编写程序时，注意判断语音合成模
				 块的返回值，根据返回值进行下一次播放，如不接收返回值则无法进
				 行下一次播放。
/*****************************飞音云电子*******************************/

#include "config.h"

void MCU_init(); 
extern void XFS_FrameInfo(uint8_t Music,uint8_t *HZdata);
/***********************************************************
* 名    称： void  main(void)
* 功    能： 主函数	程序入口
* 入口参数：  
* 出口参数：
* 说    明： 					 
* 调用方法： 
**********************************************************/ 
void  main(void)
{
	MCU_init();
	UartIni(); /*串口初始化*/

	XFS_FrameInfo("感谢您使用飞音云电子产品") ;
   while(1)
   {
  
			
	}// while

}
/***********************************************************
* 名    称： void MCU_init()
* 功    能： 单片机初始化
* 入口参数：  
* 出口参数：
* 说    明： 					 
* 调用方法： 
**********************************************************/ 
void MCU_init()
{
	P0 = 0xff;
	P1 = 0xff;
	P2 = 0xff;
	P3 = 0xff;

}






