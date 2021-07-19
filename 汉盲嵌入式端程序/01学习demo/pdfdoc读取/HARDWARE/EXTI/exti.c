#include "exti.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "readwrite.h"
#include "usart.h"
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
FRESULT res;
u32 filelength=0;
u8 readbuf[100]="";
void EXTI_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOH_CLK_ENABLE();               //����GPIOHʱ��
    __HAL_RCC_GPIOC_CLK_ENABLE();
    
    GPIO_Initure.Pin=GPIO_PIN_2|GPIO_PIN_3;     //PH2,3
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;     //�½��ش���
    GPIO_Initure.Pull=GPIO_PULLUP;
    
    
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);
	
	
    GPIO_Initure.Pin=GPIO_PIN_13;
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);
    //�ж���2-PH2
    HAL_NVIC_SetPriority(EXTI2_IRQn,2,0);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ0
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);             //ʹ���ж���2
    
    //�ж���3-PH3
    HAL_NVIC_SetPriority(EXTI3_IRQn,2,1);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ1
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);             //ʹ���ж���3
	
	HAL_NVIC_SetPriority(EXTI15_10_IRQn,2,2);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ2
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);             //ʹ���ж���4
    
}


//�жϷ�����


void EXTI2_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);//�����жϴ����ú���
}

void EXTI3_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);//�����жϴ����ú���
}

void EXTI15_10_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);//�����жϴ����ú���
}

//�жϷ����������Ҫ��������
//��HAL�������е��ⲿ�жϷ�����������ô˺���
//GPIO_Pin:�ж����ź�
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    delay_ms(100);      //����
	int cnt=0;
    switch(GPIO_Pin)
    {
        case GPIO_PIN_2:
            if(KEY1==0)  
            {
                res=times_Read("0:/����.doc");
				if(res==0)
				{
					printf("Doc Length:%d\r\n",filelength);
					for(cnt=0;cnt<filelength;cnt++)
						printf("Doc Content:%2x\r\n",readbuf[cnt]);
				}	
            }
            break;
        case GPIO_PIN_3:
            if(KEY0==0)  
            {
                res=times_Read("0:/����.pdf");
				if(res==0)
				{
					printf("PDF Length:%d\r\n",filelength);
					for(cnt=0;cnt<filelength;cnt++)
						printf("PDF Content:%2x\r\n",readbuf[cnt]);
				}	
            }
            break;
		case GPIO_PIN_13:
            if(KEY2==0)  
            {
                res=times_Read("0:/����.txt");
				if(res==0)
				{
					printf("TXT Length:%d\r\n",filelength);
					for(cnt=0;cnt<filelength;cnt++)
						printf("TXT Content:%2x\r\n",readbuf[cnt]);
				}	
            }
            break;
    }
}
