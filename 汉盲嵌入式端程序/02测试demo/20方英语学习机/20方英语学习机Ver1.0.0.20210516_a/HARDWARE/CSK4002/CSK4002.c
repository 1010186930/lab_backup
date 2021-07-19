#include "string.h"
#include "usart.h"
#include "CSK4002.h"
/****************************************************************************

* Copyright (C), 2021-2022,֮��ʵ����

* �ļ���: CSK4002.c

* ���ݼ�����Ӣ��ѧϰ��Ver1.0.0.20210516_a��CSK4002�����ϳɵĹ���ʵ��

* ʵ����������������ʼ�ϳɺ�״̬��ѯ

* ͨ������3�����ϳɵ��ı����͵�CSK4002������2����CSK4002�ķ���ֵ�����͸���λ������usart.c�Ĵ���3���жϷ�����ʵ�֣�

* �ļ���ʷ��

* �汾�� ���� ���� ˵��

* 1.0.0.20210516_a 2021-05-17 �¿��� �������ļ�

*/
u8 CSK4002_STA=UNKNOWN_STA;

/**
  * @name   CSK4002_Start
  *
  * @brief  CSK4002�Ŀ�ʼ�ϳɺ���
  *
  * @param  command��CSK4002���´�����֡ [����������]
  *	@param  page��CSK4002��ʼ�����еĴ���ҳ [PAGE]
  *	@param  Inputbuf��CSK4002���ϳ��ı������뻺�壬���200-2�ֽ�

  * @retval ��
  */
void CSK4002_Start(CONTROL_COMMAND command,PAGE page,u8* Inputbuf)
{
    u8 TransmitText[USART_REC_LEN]= {0x00};
    u8 Inputbuf_length=strlen((const char*)Inputbuf);
    TransmitText[0]=FLAG;
    TransmitText[1]=0x00;
    TransmitText[2]=Inputbuf_length+2;
    TransmitText[3]=command;
    TransmitText[4]=page;
    memcpy(&TransmitText[5],Inputbuf,Inputbuf_length);
    HAL_UART_Transmit(&UART3_Handler,(uint8_t*)TransmitText,Inputbuf_length+2,1000);
    while(__HAL_UART_GET_FLAG(&UART3_Handler,UART_FLAG_TC)!=SET);
}



/**
  * @name   CSK4002_QueryState
  *
  * @brief  CSK4002��״̬��ѯ����
  *
  * @param  ��

  * @retval ��
  */
void CSK4002_QueryState()
{
    u8 TransmitText[COMMON_FRAME_LENGTH]= {0x00};
    TransmitText[0]=FLAG;
    TransmitText[1]=0x00;
    TransmitText[2]=0X01;
    TransmitText[3]=QUERY;
    HAL_UART_Transmit(&UART3_Handler,(uint8_t*)TransmitText,COMMON_FRAME_LENGTH,1000);
    while(__HAL_UART_GET_FLAG(&UART3_Handler,UART_FLAG_TC)!=SET);
}
