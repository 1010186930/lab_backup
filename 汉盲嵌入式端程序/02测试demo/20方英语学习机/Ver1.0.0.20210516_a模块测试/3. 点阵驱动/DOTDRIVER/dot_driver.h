#ifndef _DOT_DRIVER_H
#define _DOT_DRIVER_H
#include "sys.h"
#include "dot_processor.h"
/****************************************************************************

* Copyright (C), 2021-2022,֮��ʵ����

* �ļ���: dot_driver.h

* ���ݼ�����Ӣ��ѧϰ��Ver1.0.0.20210516_a��CSK4002�����ϳ�оƬ����������������74HC573D0~D7��LE0~LE14�ĺ궨��

*

* �ļ���ʷ��

* �汾�� ���� ���� ˵��

* 1.0.0.20210516_a 2021-05-18 �¿��� �������ļ�

*/

/* ������74HC573����������D0~D7 */
 
#define D0		PIout(2)
#define D1		PIout(1)
#define D2		PIout(0)
#define D3		PHout(15)
#define D4		PHout(14)
#define D5		PHout(13)
#define D6		PCout(9)
#define D7		PCout(8)

/* ������74HC573��Latch LE0~LE14 */

#define LE0		PIout(7)
#define LE1		PIout(5)
#define LE2		PJout(14)
#define LE3		PJout(12)
#define LE4		PJout(13)
#define LE5		PDout(7)
#define LE6		PDout(3)
#define LE7		PGout(7)
#define LE8		PGout(3)
#define LE9		PJout(7)
#define LE10	PBout(13)
#define LE11	PBout(15)
#define LE12	PHout(12)
#define LE13	PHout(10)
#define LE14	PHout(6)

/* Control Command */
typedef enum {
	ALLDOWN=	0X00,
	ALLUP=		0X01
} Control_Command;

/* ������ƺ��� */
extern unsigned char InputBraille_IO[LATCH_NUM];
void DOT_Init(void);
void Disable_Latch(void);
void Enable_Latch(void);
void Reset_DataPort(void);
void Set_DataPort(void);
void Dot_Control(Control_Command command);
void Braille_Display(unsigned char* InputBraille,unsigned char InputBraille_Length,unsigned char InputToIO[LATCH_NUM]);
void Cell_Control(unsigned char num);
#endif
