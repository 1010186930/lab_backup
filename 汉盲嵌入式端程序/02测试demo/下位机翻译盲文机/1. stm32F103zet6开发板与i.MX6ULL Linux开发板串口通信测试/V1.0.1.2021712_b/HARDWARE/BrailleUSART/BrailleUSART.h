#ifndef __BRAILLEUSART_H
#define __BRAILLEUSART_H
#include "sys.h"

#endif

#define RX_MAXSIZE 126
#define TX_MAXSIZE 69
	  		  	
extern u8 USART2_RX_BUFF[RX_MAXSIZE]; 		//���ջ���,���64���ֽ�
extern u8 USART2_TX_BUFF[TX_MAXSIZE]; 		//���ͻ���,���64���ֽ�
extern u8 USART2_RX_CNT;   			//���յ������ݳ���
extern u8 USART2_TX_CNT;   			//���͵����ݳ���
extern u8 USART2_FrameFlag;			//֡�������
void BraillieUSART_Init(u32 bound);
