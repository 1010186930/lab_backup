#include "exti.h"
#include "delay.h"
#include "led.h"
#include "key.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F429������
//�ⲿ�ж���������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2016/1/5
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

//�ⲿ�жϳ�ʼ��
void EXTI_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOA_CLK_ENABLE();               //����GPIOAʱ��
    __HAL_RCC_GPIOC_CLK_ENABLE();               //����GPIOCʱ��
    __HAL_RCC_GPIOH_CLK_ENABLE();               //����GPIOHʱ��
    
    GPIO_Initure.Pin=GPIO_PIN_10|GPIO_PIN_9;                //PA0
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;      //�����ش���
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);
    
//    GPIO_Initure.Pin=GPIO_PIN_13;               //PC13
//    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;     //�½��ش���
//    GPIO_Initure.Pull=GPIO_PULLUP;
//    HAL_GPIO_Init(GPIOC,&GPIO_Initure);
    
//    GPIO_Initure.Pin=GPIO_PIN_2|GPIO_PIN_3;     //PH2,3
//    HAL_GPIO_Init(GPIOH,&GPIO_Initure);
    
    //�ж���0-PA0
    HAL_NVIC_SetPriority(EXTI0_IRQn,2,0);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ0
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);             //ʹ���ж���0
    
    //�ж���2-PH2
    HAL_NVIC_SetPriority(EXTI2_IRQn,2,1);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ1
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);             //ʹ���ж���2
    
    //�ж���3-PH3
    HAL_NVIC_SetPriority(EXTI9_5_IRQn,2,2);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ2
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);             //ʹ���ж���2
    
    //�ж���13-PC13
    HAL_NVIC_SetPriority(EXTI15_10_IRQn,2,3);   //��ռ���ȼ�Ϊ2�������ȼ�Ϊ3
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);         //ʹ���ж���13  
}

void EXTI_DeInit(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOA_CLK_ENABLE();               //����GPIOAʱ��
    __HAL_RCC_GPIOC_CLK_ENABLE();               //����GPIOCʱ��
    __HAL_RCC_GPIOH_CLK_ENABLE();               //����GPIOHʱ��
    
    GPIO_Initure.Pin=GPIO_PIN_10|GPIO_PIN_9;                //PA0
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;      //�����ش���
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);
    
//    GPIO_Initure.Pin=GPIO_PIN_13;               //PC13
//    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;     //�½��ش���
//    GPIO_Initure.Pull=GPIO_PULLUP;
//    HAL_GPIO_Init(GPIOC,&GPIO_Initure);
    
//    GPIO_Initure.Pin=GPIO_PIN_2|GPIO_PIN_3;     //PH2,3
//    HAL_GPIO_Init(GPIOH,&GPIO_Initure);
    
    //�ж���0-PA0
    HAL_NVIC_SetPriority(EXTI0_IRQn,2,0);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ0
    HAL_NVIC_DisableIRQ(EXTI0_IRQn);             //ʹ���ж���0
    
    //�ж���2-PH2
    HAL_NVIC_SetPriority(EXTI2_IRQn,2,1);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ1
    HAL_NVIC_DisableIRQ(EXTI2_IRQn);             //ʹ���ж���2
    
    //�ж���3-PH3
    HAL_NVIC_SetPriority(EXTI9_5_IRQn,2,2);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ2
    HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);             //ʹ���ж���2
    
    //�ж���13-PC13
    HAL_NVIC_SetPriority(EXTI15_10_IRQn,2,3);   //��ռ���ȼ�Ϊ2�������ȼ�Ϊ3
    HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);         //ʹ���ж���13  
}
//�жϷ�����
void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);//�����жϴ����ú���
}

void EXTI2_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);//�����жϴ����ú���
}

void EXTI3_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);//�����жϴ����ú���
}
void EXTI9_5_IRQHandler(void)
{
   HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);//�����жϴ����ú���
}
void EXTI15_10_IRQHandler(void)
{
    
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);//�����жϴ����ú���
}

//�жϷ����������Ҫ��������
//��HAL�������е��ⲿ�жϷ�����������ô˺���
//GPIO_Pin:�ж����ź�
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
//    delay_ms(100);      //����
    switch(GPIO_Pin)
    {
        case GPIO_PIN_0:
           
				LED1=!LED1;//����LED0,LED1�������
				LED0=!LED1;
           
            break;
        case GPIO_PIN_9:
            
                LED0=!LED0;   
            
            break;
        case GPIO_PIN_3:
            
                LED0=!LED0;
				LED1=!LED1;
            
            break;

        case GPIO_PIN_10:
            
				LED0=!LED0;//����LED0��ת
            
            break;
    }
}
