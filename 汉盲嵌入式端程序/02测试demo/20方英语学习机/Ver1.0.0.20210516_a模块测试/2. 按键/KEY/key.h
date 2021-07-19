#ifndef _KEY_H
#define _KEY_H
#include "sys.h"
/****************************************************************************

* Copyright (C), 2021-2022,֮��ʵ����

* �ļ���: key.h

* ���ݼ�����Ӣ��ѧϰ��Ver1.0.0.20210516_a�İ����궨��

*

* �ļ���ʷ��

* �汾�� ���� ���� ˵��

* 1.0.0.20210516_a 2021-05-16 �¿��� �������ļ�

*/



//����ķ�ʽ��ͨ��ֱ�Ӳ���HAL�⺯����ʽ��ȡIO
#define KEY_ENTER        HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_5)  	//KEY_ENTER����PE5
#define KEY_RETURN       HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_4)  	//KEY_RETURN����PE4
#define KEY_PREVIOUS     HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_3) 	//KEY_PREVIOUS����PE3
#define KEY_NEXT    	 HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_6)  	//KEY_NEXT����PE6
#define KEY_BOOKMARK     HAL_GPIO_ReadPin(GPIOI,GPIO_PIN_10)  	//KEY_BOOKMARK����PI10

#define KEY_ENTER_PRESS			1
#define KEY_RETURN_PRESS		2
#define KEY_PREVIOUS_PRESS		3
#define KEY_NEXT_PRESS			4
#define KEY_BOOKMARK_PRESS		5	

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
