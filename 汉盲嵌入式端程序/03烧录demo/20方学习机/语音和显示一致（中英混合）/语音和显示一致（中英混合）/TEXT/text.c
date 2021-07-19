#include "sys.h"
#include "fontupd.h"
#include "w25qxx.h"
#include "lcd.h"
#include "text.h"
#include "string.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK��ӢSTM32������V3
//������ʾ ��������
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/1/20
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

//code �ַ�ָ�뿪ʼ
//���ֿ��в��ҳ���ģ
//code �ַ����Ŀ�ʼ��ַ,GBK��
//mat  ���ݴ�ŵ�ַ (size/8+((size%8)?1:0))*(size) bytes��С
//size:�����С
void Get_HzMat(unsigned char *code,unsigned char *mat,u8 size)
{
    unsigned char qh,ql;
    unsigned char i;
    unsigned long foffset;
    u8 csize=(size/8+((size%8)?1:0))*(size);//�õ�����һ���ַ���Ӧ������ռ���ֽ���
    qh=*code;
    ql=*(++code);
//	printf("%XH\r\n",qh);
//  printf("%XH\r\n",ql);
    if(qh<0x81||ql<0x40||ql==0xff||qh==0xff)//�� ���ú���
    {
        for(i=0; i<csize; i++)*mat++=0x00; //�������
        return; //��������
    }
    if(ql<0x7f)ql-=0x40;//ע��!
    else ql-=0x41;
    qh-=0x81;
    foffset=((unsigned long)190*qh+ql)*csize;	//�õ��ֿ��е��ֽ�ƫ����
//	printf("ƫ������%ld\r\n",foffset);
    switch(size)
    {
    case 12:
        W25QXX_Read(mat,foffset+ftinfo.f12addr,csize);
        break;
    case 16:
        W25QXX_Read(mat,foffset+ftinfo.f16addr,csize);
        break;
    case 24:
        W25QXX_Read(mat,foffset+ftinfo.f24addr,csize);
        break;
    case 32:
        W25QXX_Read(mat,foffset+ftinfo.f32addr,csize);
        break;

    }
}
//��ʾһ��ָ����С�ĺ���
//x,y :���ֵ�����
//font:����GBK��
//size:�����С
//mode:0,������ʾ,1,������ʾ
void Show_Font(u16 x,u16 y,u8 *font,u8 size,u8 mode)
{
    u8 temp,t,t1;
    u16 y0=y;
    u8 dzk[256];
    u8 csize=(size/8+((size%8)?1:0))*(size);//�õ�����һ���ַ���Ӧ������ռ���ֽ���
    if(size!=12&&size!=16&&size!=24&&size!=32)return;	//��֧�ֵ�size
    Get_HzMat(font,dzk,size);	//�õ���Ӧ��С�ĵ�������
//	for(q=0;q<256;q++)
//	printf("%XH\r\n",dzk[q]);
    for(t=0; t<csize; t++)
    {
        temp=dzk[t];			//�õ���������
        for(t1=0; t1<8; t1++)
        {
            if(temp&0x80)LCD_Fast_DrawPoint(x,y,POINT_COLOR);
            else if(mode==0)LCD_Fast_DrawPoint(x,y,BACK_COLOR);
            temp<<=1;
            y++;
            if((y-y0)==size)
            {
                y=y0;
                x++;
                break;
            }
        }
    }
}
//��ָ��λ�ÿ�ʼ��ʾһ���ַ���
//֧���Զ�����
//(x,y):��ʼ����
//width,height:����
//str  :�ַ���
//size :�����С
//mode:0,�ǵ��ӷ�ʽ;1,���ӷ�ʽ
void Show_Str(u16 x,u16 y,u16 width,u16 height,u8*str,u8 size,u8 mode)
{
    u16 x0=x;
    u16 y0=y;
    u8 bHz=0;     //�ַ���������  abort
//printf("%d,%d",*str,*(++str));
    while(*str!=0)//����δ����
    {
        if(!bHz)
        {
            if(*str>0x80)bHz=1;//����
            else              //�ַ�
            {
                if(x>(x0+width-size/2))//����
                {
                    y+=size;
                    x=x0;
                }
                if(y>(y0+height-size))break;//Խ�緵��
                if(*str==13)//���з���
                {
                    y+=size;
                    x=x0;
                    str++;
                }
                else LCD_ShowChar(x,y,*str,size,mode);//��Ч����д��
                str++;
                x+=size/2; //�ַ�,Ϊȫ�ֵ�һ��
            }
        } else//����
        {
            bHz=0;//�к��ֿ�
            if(x>(x0+width-size))//����
            {
                y+=size;
                x=x0;
            }
            if(y>(y0+height-size))break;//Խ�緵��
            Show_Font(x,y,str,size,mode); //��ʾ�������,������ʾ
						if(*str==0xA8)
            {
                if(*(str+1)>=0xA1&&*(str+1)<=0xB9)
                {
                    str+=2;
                    x+=size/2;
                }
            }

            else
            {
                str+=2;
                x+=size;//��һ������ƫ��
            }
        }
    }
}
//��ָ����ȵ��м���ʾ�ַ���
//����ַ����ȳ�����len,����Show_Str��ʾ
//len:ָ��Ҫ��ʾ�Ŀ��
void Show_Str_Mid(u16 x,u16 y,u8*str,u8 size,u8 len)
{
    u16 strlenth=0;
    strlenth=strlen((const char*)str);
    strlenth*=size/2;
    if(strlenth>len)Show_Str(x,y,lcddev.width,lcddev.height,str,size,1);
    else
    {
        strlenth=(len-strlenth)/2;
        Show_Str(strlenth+x,y,lcddev.width,lcddev.height,str,size,1);
    }
}
//LCD��,ä�ĵ��LCD��ʾ������
// x,yΪ���Ͻ����ꡣ������ʾ

void LCD_DLBraille(u16 x,u16 y,char braille[20][7]) {
    char k,l;//K:����10���֣�0-9��l���ֵĵ���0-12��12�����ʾ����һ����
    for(k=0; k<20; k++)
        for(l=0; l<6; l++)
//				LCD_Draw_Circle(x+32*(k%5)+8*(l/3)-1*(l/6),y+100*(k/5)+8*(l%3),2*(braille[k][l]-48));//�ú���ʵ��12���ͳһ������Ų���
            LCD_Draw_Circle(x+20*(k%10)+8*(l/3)-1*(1/6),y+80*(k/10)+8*(l%3),2*(braille[k][l]-48));//�ú���ʵ��12���ͳһ������Ų���

}
//Բ��뾶Ϊ2,һ�����﷽�뷽�ļ��7��ʹ�ÿ�������ֱ�ۣ�һ��������ͳһΪ8����������ɵ�ä��֮����Ϊ9��
void LCD_PriBraille(u16 x,u16 y,char braille[10][13]) {
    char k,l;//K:����10���֣�0-9��l���ֵĵ���0-12��12�����ʾ����һ����
    for(k=0; k<10; k++)
        for(l=0; l<12; l++)
//				LCD_Draw_Circle(x+32*(k%5)+8*(l/3)-1*(l/6),y+100*(k/5)+8*(l%3),2*(braille[k][l]-48));//�ú���ʵ��12���ͳһ������Ų���
            LCD_Draw_Circle(x+40*(k%5)+8*(l/3)-1*(1/6),y+80*(k/5)+8*(l%3),2*(braille[k][l]-48));//�ú���ʵ��12���ͳһ������Ų���

}

//ä�ĵ㵥����ʾ,ä�Ļ���ѧϰ
void LCD_PriOLBraille(u16 x,u16 y,char braille[10][13]) {
    char k,l;//K:����10���֣�0-9��l���ֵĵ���0-12��12�����ʾ����һ����
    for(k=0; k<10; k++)
        for(l=0; l<12; l++)
            LCD_Draw_Circle(x+40*(k%10)+8*(l/3)-1*(l/6),y+8*(l%3),2*(braille[k][l]-48));//�ú���ʵ��12���ͳһ������Ų���

}
//С˵������ʾ
void LCD_OLBraille(u16 x,u16 y,char braille[20][7]) {
    char k,l;//K:����10���֣�0-9��l���ֵĵ���0-12��12�����ʾ����һ����
    for(k=0; k<20; k++)
        for(l=0; l<6; l++)
            LCD_Draw_Circle(x+20*(k%20)+8*(l/3)+1*(l/6),y+8*(l%3),2*(braille[k][l]-48));//�ú���ʵ��12���ͳһ������Ų���

}
//WС˵������ʾ
void LCD_WShowBraille(int n,u16 x,u16 y,char braille[][7]) {
    char k,l;//K:����10���֣�0-9��l���ֵĵ���0-12��12�����ʾ����һ����
    int x0,y0;
    for(k=0; k<n; k++)
        for(l=0; l<6; l++)
        {
            //x0=x+14*(l/3)+2*(l/6)+74*k;
            //y0=y+150*(k/10)+25*(l%3);

            x0=x+16*(l/3)+32*k+5*k;
            y0=y+25*(l%3)+150*(k/n);

            //x0=x+16*(l/3)+32*k+5*k;
            //y0=y+25*(l%3)+150*(k/20);
            if(braille[k][l]=='1')
                gui_fill_circle(x0,y0,3,BLUE);
            else LCD_Draw_Circle(x0,y0,2);
        }

}
//Wä�Ļ���ѧϰ
void LCD_ShowBraille(u16 x,u16 y,char braille[10][13]) {
    char k,l;//K:����10���֣�0-9��l���ֵĵ���0-12��12�����ʾ����һ����
    int x0,y0;
    for(k=0; k<10; k++)
        for(l=0; l<12; l++)
        {

            x0=x+14*(l/3)+2*(l/6)+74*k;   //��һ������������x����74��һ�����0���3���14�� ÿ�����16
            y0=y+150*(k/10)+25*(l%3);
            if(braille[k][l]=='1')
                gui_fill_circle(x0,y0,3,BLUE);
            else LCD_Draw_Circle(x0,y0,2);
        }

}




























