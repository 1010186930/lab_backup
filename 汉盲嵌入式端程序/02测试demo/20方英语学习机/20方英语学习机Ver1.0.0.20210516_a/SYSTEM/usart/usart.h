#ifndef _USART_H
#define _USART_H
#include "sys.h"
#include "stdio.h"	
/****************************************************************************

* Copyright (C), 2021-2022,֮��ʵ����

* �ļ���: usart.h

* ���ݼ�����Ӣ��ѧϰ��Ver1.0.0.20210516_a�Ĵ���2��TX:PA2,RX:PA3)������3(TX:PB10,RX:PB11)�Ķ���

*

* �ļ���ʷ��

* �汾�� ���� ���� ˵��

* 1.0.0.20210516_a 2021-05-17 �¿��� �������ļ�

*/	 	
#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART2_RX 			1		//ʹ�ܣ�1��/��ֹ��0������2����
#define EN_USART3_RX 			1		//ʹ�ܣ�1��/��ֹ��0������3����
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	
extern UART_HandleTypeDef UART2_Handler; //UART2���
extern UART_HandleTypeDef UART3_Handler; //UART3���

#define RXBUFFERSIZE   1 //�����С
extern u8 aRxBuffer[RXBUFFERSIZE];//HAL��USART����Buffer

//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 bound);


#endif
