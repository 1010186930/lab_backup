#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h"  
#include "key.h"     
#include "malloc.h"
#include "sdio_sdcard.h"  
#include "w25qxx.h"    
#include "ff.h"  
#include "exfuns.h"   
#include "text.h"
#include "htptb.h"
#include "suocun.h"
#include<stdlib.h>
#include<string.h>
#define MAXDIR 20
 
/************************************************

 ��äת����ʾ ʵ�� 
 by Xuanjianqiang
    ������ʵʵ����
		10����ˢ��һ��
************************************************/
#define INITMENU 0
#define TESTMENU 1
#define FILDIRMENU 2
#define TESTMODE 3
#define READMODE 4
u8 filecnt,keys,keyi,keyf,keyt;//keyi �����˵����������  keyt ����˵����������  keyf sd�ļ�Ŀ¼���������  filecnt����sd�ļ����� 
u16 tlct=0;//tlctΪ�ļ���λָ��		
u8 keyi=1,keyt=1,keyf=1;//�˵��µ�����־��������ʼ��Ϊָ������
	u8 initmenu[3][23]={"��ӭʹ��ä���Ķ�ϵͳ","����DEMO","�����Ķ�Ŀ¼"};		
 u8 testmenu[7][23]={"����ģʽ","�շ�����","��������","ƴ����ʾ","������ʾ","������ʾ","��ʫ��ʾ"};			
char YSsym[10][13]={"110000000000","111100000000","101100000000","110100000000","100110000000","001010000000","010001000000","101001000000","001011000000","010010000000"};
char YSsz[10][13]={"001111010111","001111100000","001111110000","001111100100","001111100110","001111100010","001111110100","001111110110","001111110010","001111010110"};
char YSwz[21]={"������ѧ������ʵ��"}; 
char TS[21]={"��ǰ���¹����Ƶ���˪"};
char  Dirname[MAXDIR][30];	
void initUI(void);
void testUI(void);
void fildirUI(void);
void UIfun(u8 level);
void test_act(u8 line);
void read_act(char *filename);
//����ƶ�����
//	void highlight(u8 line){
//			LCD_Fill(15,50,30,220,WHITE);//���ԭ��λ�ã���ɫ���	
//	LCD_Fill(15,30+20*line,30,40+20*line+8,BLUE);
//}

	void highlight1(u8 line){
	LCD_Fill(35,60,50,300,WHITE);//���ԭ��λ�ã���ɫ���	
	LCD_Fill(35,44+31*line,45,36+31*line+18,BLUE);
}
		void highlight(u8 line){
//			LCD_Fill(15,50,30,220,WHITE);//���ԭ��λ�ã���ɫ���	
//	LCD_Fill(15,30+20*line,30,40+20*line+8,BLUE);
					LCD_Fill(30,90,50,300,WHITE);//���ԭ��λ�ã���ɫ���	
	LCD_Fill(30,74+31*line,45,66+31*line+18,BLUE);
}

//key0�¼�����ʱ��ִ�еĺ���   ȷ��
void e0_event_function(u8 *nxt_state){   
    u8 cur_state;   
	cur_state = *nxt_state;   
    switch(cur_state)
    {       
			case INITMENU: //����0���˵�״̬ʱ ����keyi�л�״̬����   
					*nxt_state=keyi;
					UIfun(*nxt_state);//״̬�л�
			break;
			case TESTMENU: //����1״̬ʱ; �л���ĩ���˵�
					*nxt_state=TESTMODE; 
		    	UIfun(*nxt_state);//״̬�л�
				break;
			case FILDIRMENU://����2Ŀ¼�˵����л����ı��Ķ�
					*nxt_state=READMODE;
					read_act(Dirname[keyf-1]);//20�ֽ�Ϊ��λ�Ķ�����λ�ı�־����20�����书��
				break;
}
}
//key1�¼�����ʱ��ִ�еĺ���,	���µ�����ť   ����
void e1_event_function(u8 *nxt_state)
{   
    u8 cur_state;   
    cur_state = *nxt_state;   
    switch(cur_state)
    {       
        case INITMENU: //���˵�״̬�µ�key1���°�����������      
            //ִ�й���ƶ�������״̬�����л�
					keyi=keyi%2+1;//����־�����仯
				  highlight(keyi);
				  break;
				case TESTMENU://�Ӳ˵�1
				  keyt=keyt%6+1;
				  highlight(keyt);
				  break;
				case FILDIRMENU://�Ӳ˵�2
					keyf=keyf%filecnt+1;
				  highlight(keyf);
				  break;
				case TESTMODE://����ģʽ���ޱ仯
					;
				break;
				case READMODE://�Ķ�ģʽ�£�ʵ�ַ�ҳ�����Ķ�����
					read_act(Dirname[keyf-1]);
				  break;				
    }
}
//keyup ��������ʱ��ִ�еĺ���       ����
	void e2_event_function(u8 *nxt_state){
				u8 cur_state;   
				cur_state = *nxt_state; 
		
switch(cur_state)
{
	case TESTMENU:
	case FILDIRMENU:
		*nxt_state=INITMENU;
	  UIfun(*nxt_state);
	break;
	case INITMENU:
		;
	break;
	default:
		if(keyi==1)//����ĩ�ε����˵�������ťkeyf�б��������ĸ���Ŀ¼�˵�
	  *nxt_state=TESTMENU;
		else{
		*nxt_state=FILDIRMENU;
		tlct=0;//�˳��Ķ����ļ���λָ������
		//Ҳ��дΪ UIfun(keyi)
		}
		UIfun(*nxt_state);
	break;
	}
}

int main(void)
{	 u8 key_v,state=0;
	delay_init();	    	 //��ʱ������ʼ��	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		      //�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200	
 	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();					  //��ʼ������
	LCD_Init();			   		//��ʼ��LCD   
	W25QXX_Init();				//��ʼ��W25Q128
 	my_mem_init(SRAMIN);	//��ʼ���ڲ��ڴ��
	exfuns_init();				//Ϊfatfs��ر��������ڴ�  
	SUOCUN_init();//��������ʼ��
	font_init();
UIfun(state);
	f_mount(fs[0],"0:",1); 
while(1){
		key_v=KEY_Scan(0);	
	switch(key_v){
		case 1:
			e0_event_function(&state);
		break;
		case 2:
			e1_event_function(&state);
		break;
		case 3:
			e2_event_function(&state);
		dis(0);//�շ���ʾ
		break;
	}	
		
}	
		
}		
//0���˵���I,II��III���˵��Ľ�����ʾ����
void UIfun(u8 level){
							LCD_Clear(WHITE);//�����л�ǰ��������
							POINT_COLOR=RED;
								Show_Str(10,20,320,32,initmenu[0],32,0);//��д24�ű���
	            POINT_COLOR=BLUE;
					switch(level){	
						case 0://��ʾ���˵�Ŀ¼
							keyi=1;//��Ӧ����־������ʼ��
							Show_Str(60,70,320,24,initmenu[1],24,0);
			    	 	Show_Str(60,110,320,24,initmenu[2],24,1);
						  highlight1(1);//״̬�л��󣬹��λ�ñ���λ������
						break;
						case 1://��ʾ����˵����溯��
							keyt=1;
							Show_Str(40,70,500,24,testmenu[0],24,0);
							Show_Str(60,100,500,24,testmenu[1],24,0);
							Show_Str(60,130,500,24,testmenu[2],24,0);
 							Show_Str(60,160,500,24,testmenu[3],24,0);
							Show_Str(60,190,500,24,testmenu[4],24,0);
							Show_Str(60,220,500,24,testmenu[5],24,0);
							Show_Str(60,250,500,24,testmenu[6],24,0);
						  highlight(1);//״̬�л��󣬹��λ�ñ���λ������
						break;
						case 2://��ʾSD���ļ�Ŀ¼�˵�����
							keyf=1;
						fildirUI();
						highlight(1);//״̬�л��󣬹��λ�ñ���λ������
						break;
						case 3://����ģʽ
							test_act(keyt);
						break;
					};
	}
	//Ŀ¼�˵���ʾ����				
void fildirUI(void){								
		//֧������ļ�Ŀ¼��
	//FATFS *fs;
//	char *fn;
	DIR dir;
	FIL fil;
	FILINFO f_info;
	u8 maxdir=0,s=0;//s:Ŀ¼���ļ�������line���������λ��0ΪĬ�ϵ�һ��
	f_mount(fs[0],"0:",1); 		//����SD��	��0;�޴���	
	while(SD_Init())			//���SD��
	{
			LCD_ShowString(30,70,200,16,16,"SD Card Failed!check it");
			delay_ms(200);
			LCD_Fill(30,70,200+30,70+16,WHITE);
			LED0=!LED0;//DS0��˸
			delay_ms(200);		    
	}			
	POINT_COLOR=RED;
  if((f_opendir(&dir,(const TCHAR*)"0:"))!=FR_OK)		//��SD��������0����Ŀ¼
				Show_Str(20,50,200,24,(u8 *)"PATH ERRO!! CHECK ",24,1);//������
        memset(Dirname[0],0,13*MAXDIR);
while(1)//����Ŀ¼
 {
     if(f_readdir(&dir,&f_info)==FR_OK)
     {
         if(f_info.fname[0]==0)break;
     }
     else break;
     if(f_info.fattrib & AM_ARC)        // Ŀ¼if(f_readdir(&dir, &fno) == FR_OK) 
     {
         if(maxdir<MAXDIR)
         {
             strncpy(Dirname[maxdir],f_info.fname,13);
             maxdir++;
          }
     }	
}
    filecnt=maxdir;//���SD�����ļ���	
		for(s=0;s<maxdir;s++)
		Show_Str(30,50+20*s,200,16,(u8 *)Dirname[s],16,1);//һҳ�����ʾ10��
 	}										
					
void test_act(u8 tline){
		 LCD_Clear(WHITE);//�����л�ǰ��������
		//Show_Str(30,20,320,32,initmenu[0],32,1);//��д24�ű���
		Show_Str(30,60,320,24,testmenu[0],24,1);
		Show_Str(60,90,320,24,testmenu[tline],24,1);
		 switch(tline){
			 case 1://�շ�����
				 dis(0);
			break;
			 case 2:		//��������
				 dis(1);
			 break;
			 case 3:		//ƴ����ʾ
			 Show_Str(30,120,800,32," b  p  m  f   d  a  o  u  en  un",32,1);
			// Show_Str(15,160,200,24,"a  o  u  en  un ",24,1);
			 LCD_ShowBraille(28,240,YSsym);//LCD������ä�ĵ������ʾ
			 DX_ShowBraille(YSsym);//���������ä�ĵ���
			 break;
			 case 4:		//������ʾ
  		Show_Str(30,120,800,32," 0  1   2  3  4 5  6   7  8  9",32,1); 
			//Show_Str(10,160,200,24," 5  6   7  8  9",24,1); 
			LCD_ShowBraille(28,240,YSsz);//��ʾ����λͼ�����
			DX_ShowBraille(YSsz);//���������
			//memset(btmp,'\0',sizeof(btmp));
			 break;
			 case 5:		//��ʾ�����㽭����ѧʵ����
				memset(btmp,'\0',sizeof(btmp));
		    Show_Str(30,120,800,32," �� �� �� �� ѧ �� �� �� ʵ ��",32,1);//��һ����ʾ5����
				//Show_Str(8,170,200,24," �� �� �� ʵ ��",24,0);//��һ����ʾ5���֣���������80����ʾ��һ�����ֵ�ä��
			 text2b_lcd(YSwz);
			 LCD_ShowBraille(28,240,btmp);//LCD������ä�ĵ������ʾ
			 DX_ShowBraille(btmp);//���������ä�ĵ���
			 memset(btmp,'\0',sizeof(btmp));
			 break;
			 case 6:
 		  Show_Str(30,120,800,32," �� ǰ �� �� �� �� �� �� �� ˪",32,1);//��һ����ʾ5����
			//Show_Str(8,170,200,24," �� �� �� �� ˪",24,0);//��һ����ʾ5���֣���������80����ʾ��һ�����ֵ�ä��
			 text2b_lcd(TS);
			LCD_ShowBraille(28,240,btmp);//LCD������ä�ĵ������ʾ
			 DX_ShowBraille(btmp);//���������ä�ĵ���
			 memset(btmp,'\0',sizeof(btmp));
			 			 break; 
  
             
	 }
 }
void read_act(char *filename){	//�ı��Ķ�--�ı����
		FIL fil_0; 
		UINT rd;
  char ltmp[11]="\0";//�洢tftlcdһ��5���ֵ����ݣ��ó�ʼ��\0�Ǳ�֤strncpy��ĩβ�н�����ʶ����ʹ�����ݴ���û���쳣
	      char buffer[60];	
		    memset(btmp,'\0',sizeof(btmp));		
		   LCD_Clear(WHITE); 
		POINT_COLOR=RED; 
		 	  if(!f_open(&fil_0,filename,FA_READ)){       //�򿪳ɹ�	
				Show_Str(10,40,220,16,Dirname[keyf-1],12,0);//ע���±��ļ�
				Show_Str(40,40,220,16,"�򿪳ɹ���key1��ȡ����",12,0);/*��ʾ���*/
				f_lseek(&fil_0,tlct);//�ƶ���λ�ļ�ָ�뵽���ļ���ʼ��tlct���ֽڵ�λ�ã�Ϊ��д�ļ�����
				f_read(&fil_0,buffer,20,&rd);//һ�ζ�ȡ20���ֽڣ�10���֡�
				f_close(&fil_0);
			//����ת��Ϊֱ�۵�ä�ĵ������У�12λһ������һ���ֱ��浽�ַ�����btmp[10][13]�У�10����Դ洢10���֡�
				text2b_lcd(buffer);
 	 	  //��ʼ���		
		  	memset(ltmp,'\0',sizeof(ltmp));	
				POINT_COLOR=RED; 
				Show_Str(10,60,200,16,"���ּ���Ӧä��",16,0);
				POINT_COLOR=BLUE; 
				Show_Str(30,80,200,16,(u8 *)strncpy(ltmp,buffer,10),16,0);//��һ����ʾ5����
				Show_Str(30,160,200,16,strcpy(ltmp,buffer+10),16,0);//��һ����ʾ5���֣���������80����ʾ��һ�����ֵ�ä��
				POINT_COLOR=BLACK; 
				LCD_ShowBraille(30,100,btmp);//LCD������ä�ĵ������ʾ
				DX_ShowBraille(btmp);//���������ä�ĵ���
		    memset(btmp,'\0',sizeof(btmp));
				tlct=tlct+20;//ָ��tcltƫ��20Ϊ�´ζ�׼��
					if(!(rd==20)){
					POINT_COLOR=BLACK; 
					Show_Str(30,220,200,16,"��ȡ���,������ͷ��ʼ",16,0);
					tlct=0;
				}	
	   }
		    else
			    Show_Str(10,150,200,16,"��ʧ�ܣ����sd���ļ�",16,0);
}