#include "dot_processor.h"
#include "string.h"
/****************************************************************************

* Copyright (C), 2021-2022,֮��ʵ����

* �ļ���: dot_processor.c

* ���ݼ�����Ӣ��ѧϰ��Ver1.0.0.20210516_a��20�������Ƶ������ݵĴ�����ʵ��

*

* �ļ���ʷ��

* �汾�� ���� ���� ˵��

* 1.0.0.20210516_a 2021-05-19 �¿��� �������ļ�

*/

/** 
  * @name   Dec_To_Bit
  *
  * @brief  ��ʮ��������λ��ʾ
  *
  * @param  dec��8λ�޷���ʮ������
  * @param  bit��Ҫ��ʾ��λ��ֵ����1��8

  * @retval ����ĳһλ��ֵ��0��1
  */
unsigned char Dec_To_Bit(unsigned char dec,unsigned char bit)
{
	return (dec>>(bit-1)&1);
}


/** 
  * @name   Binary_To_Dec
  *
  * @brief  8λ������ת��Ϊʮ����
  *
  * @param  InputBinary�����8λ�������ַ���

  * @retval ���ض����ƶ�Ӧ��ʮ������
  */
unsigned char Binary_To_Dec(unsigned char* InputBinary)
{
	unsigned char index,dec=0;
	const unsigned char set[]={1,2,4,8,16,32,64,128};
	for(index=8;index>=1;index--)
	{
		if(*InputBinary=='1')
			dec+=set[index-1];
		InputBinary++;
	}
	return dec;
	
}


/** 
  * @name   Change_DotSequence
  *
  * @brief  ��������123456ת��Ϊ321654��ת����ÿ�λ�ȡ8������ת��Ϊʮ���ƺ����IO_Input
  *
  * @param  InputBrailleGroup[BRAILLE_CELL_NUM][CELL_DOT_NUM+1]��ת��Ϊ20~1����ä�Ķ����Ƶ���
  * @param  IO_Input[LATCH_NUM]�����15�����뵽IO��ʮ����ֵ

  * @retval ��
  */
void Change_DotSequence(unsigned char InputBrailleGroup[BRAILLE_CELL_NUM][CELL_DOT_NUM+1],unsigned char IO_Input[LATCH_NUM])
{
	unsigned char i,j,k=0;
	unsigned char value=0;
	unsigned char Braille_Get[9]="";
	for(i=0;i<BRAILLE_CELL_NUM;i+=4)
	{
		for(j=i;j<i+4;j++)
		{
			value=InputBrailleGroup[j][2];
			InputBrailleGroup[j][2]=InputBrailleGroup[j][0];
			InputBrailleGroup[j][0]=value;
			value=InputBrailleGroup[j][5];
			InputBrailleGroup[j][5]=InputBrailleGroup[j][3];
			InputBrailleGroup[j][3]=value;
		}
		strncpy((char*)Braille_Get,(const char*)InputBrailleGroup[i],6);
		strncat((char*)Braille_Get,(const char*)InputBrailleGroup[i+1],2);
		Braille_Get[8]='\0';
		IO_Input[k]=Binary_To_Dec(Braille_Get);
		memset(Braille_Get,'\0',sizeof(Braille_Get));
		strncpy((char*)Braille_Get,(const char*)InputBrailleGroup[i+1]+2,4);
		strncat((char*)Braille_Get,(const char*)InputBrailleGroup[i+2],4);
		Braille_Get[8]='\0';
		IO_Input[k+1]=Binary_To_Dec(Braille_Get);
		memset(Braille_Get,'\0',sizeof(Braille_Get));
		strncpy((char*)Braille_Get,(const char*)InputBrailleGroup[i+2]+4,2);
		strncat((char*)Braille_Get,(const char*)InputBrailleGroup[i+3],6);
		Braille_Get[8]='\0';
		IO_Input[k+2]=Binary_To_Dec(Braille_Get);
		memset(Braille_Get,'\0',sizeof(Braille_Get));
		k+=3;
	}
}


/** 
  * @name   Inverse_BrailleCell
  *
  * @brief  ��1~20��ä��ת��Ϊ20~1��ä��
  *
  * @param  InputBrailleGroup[BRAILLE_CELL_NUM][CELL_DOT_NUM+1]���ֹ����ä����

  * @retval ��
  */
void Inverse_BrailleCell(unsigned char InputBrailleGroup[BRAILLE_CELL_NUM][CELL_DOT_NUM+1])
{
	unsigned char i,j=0;
	unsigned char value=0;
	for(i=0;i<BRAILLE_CELL_NUM/2;i++)
	{
		for(j=0;j<CELL_DOT_NUM;j++)
		{
			value=InputBrailleGroup[i][j];
			InputBrailleGroup[i][j]=InputBrailleGroup[BRAILLE_CELL_NUM-1-i][j];
			InputBrailleGroup[BRAILLE_CELL_NUM-1-i][j]=value;
		}
	}
}

/** 
  * @name   Process_BrailleBinary
  *
  * @brief  ���������󣬵���Inverse_BrailleCell��Change_DotSequence
  *
  * @param  InputBraille�������ä�Ķ����Ƶ���
  * @param  InputBraille_Length������ĳ���
  * @param  InputToIO[LATCH_NUM]�����15���������

  * @retval ��
  */
void Process_BrailleBinary(unsigned char* InputBraille,unsigned char InputBraille_Length,unsigned char InputToIO[LATCH_NUM])
{
    unsigned char BrailleGroup[BRAILLE_CELL_NUM][CELL_DOT_NUM+1]= {""};
    unsigned char cnt=0;
    unsigned char i=0;
    cnt=InputBraille_Length/CELL_DOT_NUM;
    for(i=0; i<cnt; i++)
        memcpy(BrailleGroup[i],InputBraille+CELL_DOT_NUM*i,CELL_DOT_NUM);
	Inverse_BrailleCell(BrailleGroup);
	Change_DotSequence(BrailleGroup,InputToIO);
}
