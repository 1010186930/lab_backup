#ifndef _KEY_H
#define _KEY_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F429������
//KEY��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/1/6
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

//����ķ�ʽ��ͨ��λ��������ʽ��ȡIO
//#define KEY0        PHin(3) //KEY0����PH3
//#define KEY1        PHin(2) //KEY1����PH2
//#define KEY2        PCin(13)//KEY2����PC13
//#define WK_UP       PAin(0) //WKUP����PA0


//����ķ�ʽ��ͨ��ֱ�Ӳ���HAL�⺯����ʽ��ȡIO
#define KEY0        HAL_GPIO_ReadPin(GPIOH,GPIO_PIN_3)  //KEY0����PH3
#define KEY1        HAL_GPIO_ReadPin(GPIOH,GPIO_PIN_2)  //KEY1����PH2
#define KEY2        HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13) //KEY2����PC13
#define WK_UP       HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)  //WKUP����PA0

#define KEY0_PRES 	1
#define KEY1_PRES	2
#define KEY2_PRES	3
#define WKUP_PRES   4

extern unsigned char key_0_status;
extern unsigned char key_wkup_status;


/** 
  * @brief ע�ᰴ��������
  */
#define Key_Num_Max		6


/** 
  * @brief ��������ģʽ״̬ö��
  */
typedef enum
{
	N_Trig = 0, 																				/*!< 0 �� */		
	L_Trig ,																						/*!< 1 �͵�ƽ���� */			
	H_Trig,																							/*!< 2 �ߵ�ƽ���� */
}Trig_Mode_TypeDef;

/** 
  * @brief ����ģʽ״̬ö��
  */
typedef enum
{
	N_Click = 0,																				/*!< 0 �� */	
	S_Click ,																						/*!< 1 ���� */			
	D_Click,																						/*!< 2 ˫�� */
	L_Press,																						/*!< 3 ���� */
}Key_Mode_TypeDef;


/** 
  * @name   Init_Key_Struct
  *
  * @brief  ��ʼ������
  *
  * @param  Update_Key_CallBack�����°���״̬
  * @param  Debug_CallBack����ӡ����������Ϣ
  *
  * @retval 0���ɹ���
	*					1��Update_Key_CallBack == NULL��
  */
char Init_Key_Struct(void (*Update_Key_CallBack)(void),void (*Debug_CallBack)(unsigned char *debug_mess));

/** 
  * @name   Reg_Key
  *
  * @brief  ���ע�ᰴ����ע����������Ѿ�ע�������ô�ٴ�ע��Ḳ��֮ǰע�������ͬ�İ�����
  *
  * @param  key_s������״̬
  * @param  count����������
  * @param  Trig_Mode_E����������ģʽ
  * @param  Key_Mode_E������ģʽ
  * @param  Key_Click_CallBack�����������ص�
  *
  * @retval 0���ɹ���
	*					1��Key_Click_CallBack == NULL��
	*					2��Key.Reg_Key_Num > Key_Num_Max��
  */
char Reg_Key(unsigned char *key_s,const unsigned short count, 
	Trig_Mode_TypeDef Trig_Mode_E, Key_Mode_TypeDef  Key_Mode_E, void (*Key_Click_CallBack)(void));

/** 
  * @name   Key_Detect
  *
  * @brief  �������
  *
  * @param  ��
  *
  * @retval 0���ɹ���
	*					1��Key.Update_Key_CallBack == NULL��
  */
char Key_Detect(void);

/** 
  * @name   Get_Version_Mess
  *
  * @brief  ��ӡKey_Detect����汾��Ϣ
  *
  * @param  ��
  *
  * @retval ��Key_Detect����汾��Ϣ
  */
char *Get_Version_Mess(void);
void Key_Registration(void);
void key0_S_CallBack(void);
void key0_D_CallBack(void);
void key0_L_CallBack(void);
void keywkup_S_CallBack(void);
void keywkup_D_CallBack(void);
void keywkup_L_CallBack(void);


void KEY_Init(void);
u8 KEY_Scan(u8 mode);
#endif
