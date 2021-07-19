#include "exti.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "usart.h"
#include "dot_driver.h"
/****************************************************************************

* Copyright (C), 2021-2022,֮��ʵ����

* �ļ���: exti.c

* ���ݼ�����Ӣ��ѧϰ��Ver1.0.0.20210516_a�İ����жϳ�ʼ���Ͱ����жϷ�����

*

* �ļ���ʷ��

* �汾�� ���� ���� ˵��

* 1.0.0.20210516_a 2021-05-16 �¿��� �������ļ�

*/

//�ⲿ�жϳ�ʼ��

void EXTI_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOE_CLK_ENABLE();           //����GPIOEʱ��
    __HAL_RCC_GPIOI_CLK_ENABLE();           //����GPIOIʱ��
    
    GPIO_Initure.Pin=GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;            //PE3��PE4��PE5��PE6
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;     //�½��ش���
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);
    
    
    GPIO_Initure.Pin=GPIO_PIN_10;           //PI10
    HAL_GPIO_Init(GPIOI,&GPIO_Initure);
    
    //�ж���3-PE3
    HAL_NVIC_SetPriority(EXTI3_IRQn,2,0);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ0
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);             //ʹ���ж���3
    
    //�ж���4-PE4
    HAL_NVIC_SetPriority(EXTI4_IRQn,2,1);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ1
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);             //ʹ���ж���4
    
    //�ж���5��6-PE5��PE6
    HAL_NVIC_SetPriority(EXTI9_5_IRQn,2,2);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ2
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);             //ʹ���ж���5���ж���6
    
    //�ж���10-PI10
    HAL_NVIC_SetPriority(EXTI15_10_IRQn,2,3);   //��ռ���ȼ�Ϊ2�������ȼ�Ϊ3
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);         //ʹ���ж���10
	
    
}


void EXTI_DeInit(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOE_CLK_ENABLE();           //����GPIOEʱ��
    __HAL_RCC_GPIOI_CLK_ENABLE();           //����GPIOIʱ��
    
    GPIO_Initure.Pin=GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;            //PE3��PE4��PE5��PE6
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;     //�½��ش���
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);
    
    
    GPIO_Initure.Pin=GPIO_PIN_10;           //PI10
    HAL_GPIO_Init(GPIOI,&GPIO_Initure);
    
    //�ж���3-PE3
    HAL_NVIC_SetPriority(EXTI3_IRQn,2,0);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ0
    HAL_NVIC_DisableIRQ(EXTI3_IRQn);             //ʹ���ж���3
    
    //�ж���4-PE4
    HAL_NVIC_SetPriority(EXTI4_IRQn,2,1);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ1
    HAL_NVIC_DisableIRQ(EXTI4_IRQn);             //ʹ���ж���4
    
    //�ж���5��6-PE5��PE6
    HAL_NVIC_SetPriority(EXTI9_5_IRQn,2,2);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ2
    HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);             //ʹ���ж���5���ж���6
    
    //�ж���10-PI10
    HAL_NVIC_SetPriority(EXTI15_10_IRQn,2,3);   //��ռ���ȼ�Ϊ2�������ȼ�Ϊ3
    HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);         //ʹ���ж���10
	
    
}

//�жϷ�����
void EXTI3_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);//�����жϴ����ú���
}

void EXTI4_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);//�����жϴ����ú���
}

void EXTI9_5_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);//�����жϴ����ú���
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);//�����жϴ����ú���
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
	static int i=0;
    switch(GPIO_Pin)
    {
        case GPIO_PIN_3:
            if(KEY_PREVIOUS==0) 
            {
				Dot_Control(ALLDOWN);
            }
            break;
        case GPIO_PIN_4:
            if(KEY_RETURN==0)  //LED1��ת
            {
                Dot_Control(ALLUP);	
            }
            break;
        case GPIO_PIN_5:
            if(KEY_ENTER==0)  //ͬʱ����LED0,LED1��ת 
            {
				Dot_Control(ALLUP);
				delay_ms(100);
                LE8=1;
				Reset_DataPort();
				LE8=0;
            }
            break;
		case GPIO_PIN_6:
			if(KEY_NEXT==0)  //ͬʱ����LED0,LED1��ת 
			{
				delay_ms(100);
//				LE8=1;
//				Reset_DataPort();
//				LE8=0;
				Disable_Latch();
				i++;
				if(i==16)
					i=0;
				
				switch(i)
				{
					
					case 1:
					{
//						LE0=1;
						D0=0;
						D1=1;
						D2=1;
						D3=1;
						D4=1;
						D5=1;
						D6=1;
						D7=1;
//						LE0=0;
						break;
					}
					case 2:
					{
						LE1=1;
						Set_DataPort();
						LE1=0;
						break;
					}
					case 3:
					{
						LE2=1;
						Set_DataPort();
						LE2=0;
						break;
					}
					case 4:
					{
						LE3=1;
						Set_DataPort();
						LE3=0;
						break;
					}
					case 5:
					{
						LE4=1;
						Set_DataPort();
						LE4=0;
						break;
					}
					case 6:
					{
						LE5=1;
						Set_DataPort();
						LE5=0;
						break;
					}
					case 7:
					{
						LE6=1;
						Set_DataPort();
						LE6=0;
						break;
					}
					case 8:
					{
						LE7=1;
						Set_DataPort();
						LE7=0;
						break;
					}
					case 9:
					{
						LE8=1;
						Set_DataPort();
						LE8=0;
						break;
					}
					case 10:
					{
						LE9=1;
						Set_DataPort();
						LE9=0;
						break;
					}
					case 11:
					{
						LE10=1;
						Set_DataPort();
						LE10=0;
						break;
					}
					case 12:
					{
						LE11=1;
						Set_DataPort();
						LE11=0;
						break;
					}
					case 13:
					{
						LE12=1;
						Set_DataPort();
						LE12=0;
						break;
					}
					case 14:
					{
						LE13=1;
						Set_DataPort();
						LE13=0;
						break;
					}
					case 15:
					{
						LE14=1;
						Set_DataPort();
						LE14=0;
						break;
					}
					default:
						break;
					
						
				}
			}
			break;
        case GPIO_PIN_10:
            if(KEY_BOOKMARK==0)  
            {
				Dot_Control(ALLDOWN);
            }
            break;
    }
}
