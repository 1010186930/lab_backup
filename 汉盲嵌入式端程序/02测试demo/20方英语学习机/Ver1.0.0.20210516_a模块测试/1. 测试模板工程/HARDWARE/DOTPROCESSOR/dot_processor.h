#ifndef _DOT_PROCESSOR_H
#define _DOT_PROCESSOR_H
/****************************************************************************

* Copyright (C), 2021-2022,֮��ʵ����

* �ļ���: dot_processor.h

* ���ݼ�����Ӣ��ѧϰ��Ver1.0.0.20210516_a��20�������Ƶ������ݵĴ���������

*

* �ļ���ʷ��

* �汾�� ���� ���� ˵��

* 1.0.0.20210516_a 2021-05-19 �¿��� �������ļ�

*/
#define BRAILLE_CELL_NUM		20
#define CELL_DOT_NUM			6
#define LATCH_NUM				15

/*ä�Ķ����Ƶ�������*/

void Process_BrailleBinary(unsigned char* InputBraille,unsigned char InputBraille_Length,unsigned char InputToIO[LATCH_NUM]);
void Inverse_BrailleCell(unsigned char InputBrailleGroup[BRAILLE_CELL_NUM][CELL_DOT_NUM+1]);
void Change_DotSequence(unsigned char InputBrailleGroup[BRAILLE_CELL_NUM][CELL_DOT_NUM+1],unsigned char IO_Input[LATCH_NUM]);
unsigned char Binary_To_Dec(unsigned char* InputBinary);
unsigned char Dec_To_Bit(unsigned char dec,unsigned char bit);
#endif
