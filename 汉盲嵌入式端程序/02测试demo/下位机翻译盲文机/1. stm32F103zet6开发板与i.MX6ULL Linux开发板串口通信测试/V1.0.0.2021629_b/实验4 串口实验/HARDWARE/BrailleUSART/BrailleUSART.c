#include "sys.h"
#include "usart.h"	
#include "BrailleUSART.h"
//���ջ�����
u8 USART2_RX_BUFF[RX_MAXSIZE]="";  	//���ջ���,���126���ֽ�.
//���ͻ�����
u8 USART2_TX_BUFF[TX_MAXSIZE]="";	//���ͻ���,���69���ֽ�.
//���յ������ݳ���
u8 USART2_RX_CNT=0;
//���͵����ݳ���
u8 USART2_TX_CNT=0;

void BraillieUSART_Init(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIOA
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	//PA2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //����
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2,ENABLE);//��λ����2
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2,DISABLE);//ֹͣ��λ

    USART_InitStructure.USART_BaudRate = bound;//����������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8λ���ݳ���
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;///��żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�շ�ģʽ

    USART_Init(USART2, &USART_InitStructure);  //��ʼ������
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; //ʹ�ܴ���2�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //��ռ���ȼ�2��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; //�����ȼ�2��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure); //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
	
	USART_ClearITPendingBit(USART2,USART_IT_RXNE);
    USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���2
}

void USART2_IRQHandler(void)
{
    u8 res;
	u8 err;
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
	{
		if(USART_GetFlagStatus(USART2,USART_FLAG_NE|USART_FLAG_FE|USART_FLAG_PE)) err=1;//��⵽������֡�����У�����
		else err=0;
		res=USART_ReceiveData(USART2); //�����յ����ֽڣ�ͬʱ��ر�־�Զ����

		if((USART2_RX_CNT<RX_MAXSIZE)&&(err==0))
		{
				USART2_RX_BUFF[USART2_RX_CNT]=res;
				USART2_RX_CNT++;

				TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//�����ʱ������ж�
				TIM_SetCounter(TIM3,0);//�����յ�һ���µ��ֽڣ�����ʱ��3��λΪ0�����¼�ʱ���൱��ι����
				TIM_Cmd(TIM3,ENABLE);//��ʼ��ʱ
		}
	}
}
