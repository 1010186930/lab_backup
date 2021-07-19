#include "timer.h"
#include "led.h"
#include "key.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK��ӢSTM32������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 

//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
u8 USART2_FrameFlag=0;
u8 Master_Status=2;
u16 timer2_cnt=0; 
extern int countdown;
void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���


	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx					 
}
//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
		{
			if(KEY_Scan(0)==0)
			{
		    TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
				countdown++;
			}
			else
			{
				 TIM_ClearITPendingBit(TIM3, TIM_IT_Update ); 
				 countdown=0;
			}
		
		}
}


void TIM4_Init(u16 per,u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//ʹ��TIM3ʱ��

    TIM_TimeBaseInitStructure.TIM_Period=per;   //�Զ�װ��ֵ
    TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //��Ƶϵ��
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //�������ϼ���ģʽ
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);

    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //������ʱ���ж�
    TIM_ClearITPendingBit(TIM4,TIM_IT_Update);

    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;//��ʱ���ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//�����ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);

//    TIM_Cmd(TIM4,ENABLE); //ʹ�ܶ�ʱ��
}
/*******************************************************************************
* �� �� ��         : TIM4_IRQHandler
* ��������		   : TIM4�жϺ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void TIM4_IRQHandler(void)
{                                                                   
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);//����жϱ�־
		TIM_Cmd(TIM4,DISABLE);//ֹͣ��ʱ��
		USART2_FrameFlag=1;//��λ֡�������
	}
}



void TIM2_Init(u16 per,u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//ʹ��TIM3ʱ��

    TIM_TimeBaseInitStructure.TIM_Period=per;   //�Զ�װ��ֵ
    TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //��Ƶϵ��
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //�������ϼ���ģʽ
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);

    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //������ʱ���ж�
    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;//��ʱ���ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//�����ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);

//    TIM_Cmd(TIM2,ENABLE); //ʹ�ܶ�ʱ��
}
/*
	0->NRDY
	1->RDY
*/
void TIM2_IRQHandler(void)
{                                                                   
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//����жϱ�־
		timer2_cnt++;
		if(USART2_FrameFlag==1)
		{
			TIM_Cmd(TIM2,DISABLE);//ֹͣ��ʱ��
			Master_Status=1;
			timer2_cnt=0;
		}
		
		if(timer2_cnt==1000)//4s
		{
			TIM_Cmd(TIM2,DISABLE);//ֹͣ��ʱ��
			Master_Status=0;
			if(USART2_FrameFlag==0)//û��Ϣ�����֮��USART2_FrameFlag��0��
			{
				Master_Status=0;
				timer2_cnt=0;
			}
		}
	}
}










