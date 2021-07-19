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
#include "suocun.h"
#include "tts.h"
#include<stdlib.h>
#include<string.h>
#define MAXDIR 20

/************************************************

  ��ä�Ķ�ϵͳ����ʵ�� 
 by 		WangWenfei
    ä��ѧϰ С˵�Ķ�
************************************************/
 
#define INITMENU 0
#define PRIMENU 1
#define NOVELMENU 2
#define POEMENU 3
#define PRIMODE 4
#define NOVELMODE 5
#define POEMODE 6
#define TITLEMENU 0
#define TITLEMODE 1
#define CATAMENU 7
  FIL  fil_0;   
 FIL  fil_1;
 FIL  fil_2;
 FIL  fil_3;
	char SDbtmp[10][13]={""};
		char FCbtmp[20][7]={""};	
 char shuru1[16];
 char shuru2[16];
 char SMbuf[200];	
 char PMbuf[200];			
 char  nbuf[200]=""; 
 char  BUF[121];
 DWORD P[100];
 //DWORD Ptext[100];	
 DWORD Pdata;
u32 Tqt[120];
u32 Trmd[120];
u32 Dqt[120];
	u32 Drmd[120];
 u8 list[120][70];
		u8 yuyin[120];
int cata_page=0;
	int cata_num=0;
int count_s,i;
	int s;
		int pin;
int j,back_flag=0,contents_back=0,read_back=0;	
		int chang;
 int page;
u8 filecnt,keys,keyi,keyf,keyt;//keyi �����˵����������  keyt ����˵����������  keyf sd�ļ�Ŀ¼���������  filecnt����sd�ļ����� 
u16 tlct=0;//tlctΪ�ļ���λָ��		
u8 keyi=1,keyt=1,keyf=1,keys=1,Tkey=1;//�˵��µ�����־��������ʼ��Ϊָ������
	//u8 initmenu[4][23]={"��ӭʹ��ä���Ķ�ϵͳ","ä�Ļ���ѧϰ","С˵�Ķ�","��ʫ�δ�"};		
	u8 initmenu[3][23]={"��ӭʹ��ä���Ķ�ϵͳ","ä�Ļ���ѧϰ","С˵�Ķ�"};	
 u8 testmenu[7][23]={"��ĸ��ĸ","��������","���ּ����","Ӣ����ĸ"};	
 //u8 novelmenu[5][23]={"��������������","��ķ�������ռ�","�����","��������ִʰ�","Ѩλ��Ħ֪ʶ"};
  u8 novelmenu[2][23]={"��������������","��ķ�������ռ�"};
 // u8 poemenu[5][23]={"����ȸ¥","��ɪ","��ū��"};
u16 emptmp[15]={0x00};
  u16 fultmp[15]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
char  Dirname[MAXDIR][30];	
void initUI(void);
void testUI(void);
void fildirUI(void);
void UIfun(u8 level);
void prim_learn(u8 line);
void novel_read(u8 line);
void poet_read(u8 line);	
void Dividtxt(const TCHAR* path1,const TCHAR* path2,const TCHAR* path3,const TCHAR* path4,const TCHAR* path5);
void Dis_primary(void);
void Page_turn(void);
	 void Dis_novel(u8 *str,u8 r1 , u8 r2);
 void NPage_turn(u8*str,const TCHAR* path,DWORD P1,DWORD P2,u8 r1,u8 r2,u8 r);
	void	CdlNum_Gets(int TLnum,const TCHAR* path1,const TCHAR* path2,const TCHAR* path3,const TCHAR* path4,const TCHAR* path5);
/* void Dis_novel(u8 *str);
 void NPage_turn(u8*str,const TCHAR* path,DWORD P1,DWORD P2);
	 void Dis_FCtest(u8 *str);
 void FCPage_turn(u8*str,const TCHAR* path,DWORD P1,DWORD P2); */
//����ƶ�����
//����ƶ�����
	void highlight(u8 line){
//			LCD_Fill(15,50,30,220,WHITE);//���ԭ��λ�ã���ɫ���	
//	LCD_Fill(15,30+20*line,30,40+20*line+8,BLUE);
					LCD_Fill(35,60,50,300,WHITE);//���ԭ��λ�ã���ɫ���	
	LCD_Fill(35,44+31*line,45,36+31*line+18,BLUE);
}
		void highlight2(u8 line){
//			LCD_Fill(15,50,30,220,WHITE);//���ԭ��λ�ã���ɫ���	
//	LCD_Fill(15,30+20*line,30,40+20*line+8,BLUE);
					LCD_Fill(35,60,50,300,WHITE);//���ԭ��λ�ã���ɫ���	
	LCD_Fill(35,44+38*line,45,36+38*line+18,BLUE);
}


		void highlight1(u8 line){

					LCD_Fill(35,40,50,300,WHITE);//���ԭ��λ�ã���ɫ���	
	LCD_Fill(35,40+38*line,45,32+38*line+18,BLUE);
}
		void T_highlight(u8 line){
			LCD_Fill(5,15,15,460,WHITE);//���ԭ��λ�ã���ɫ���	
	LCD_Fill(5,30.5*line,15,10+30.5*line,BLUE);
}
//		void T_highlight(u8 line){
//	LCD_Fill(35,10,50,20,WHITE);//���ԭ��λ�ã���ɫ���		
//			LCD_Fill(35,20*line,50,10+20*line,BLUE);
//}

//key0�¼�����ʱ��ִ�еĺ���
void e0_event_function(u8 *nxt_state){   
    u8 cur_state;   
	cur_state = *nxt_state;   
    switch(cur_state)
    {       
			case INITMENU: //����0���˵�״̬ʱ ����keyi�л�״̬����   
					*nxt_state=keyi;
					UIfun(*nxt_state);//״̬�л�
							
		  
			break;
			case PRIMENU: //����1״̬ʱ; �л���ĩ���˵�
					*nxt_state=PRIMODE; 
		    	UIfun(*nxt_state);//״̬�л�
				break;
			case NOVELMENU://����2Ŀ¼�˵����л����ı��Ķ�
					*nxt_state=NOVELMODE;
				   UIfun(*nxt_state);//	read_act(Dirname[keyf-1]);//20�ֽ�Ϊ��λ�Ķ�����λ�ı�־����20�����书��
			cata_num=0;
				break;
}
}
//key1�¼�����ʱ��ִ�еĺ���,	���µ�����ť
void e1_event_function(u8 *nxt_state)
{   
    	
u8 cur_state;   
    cur_state = *nxt_state;   
    switch(cur_state)
    {       
        case INITMENU: //���˵�״̬�µ�key1���°�����������      
            //ִ�й���ƶ�������״̬�����л�
				//	keyi=keyi%3+1;//����־�����仯
							keyi=keyi%2+1;//����־�����仯
				  highlight2(keyi);
				           SPeech(initmenu[keyi]);   //���÷�������������ָ���������� 

//while(TTS_Busy==1){};���û����䣬����Ҫ����busy������
 delay_ms(1);    //��ͣ�ٱȽϺã�������������                  
				  
				  break;
				case PRIMENU://�Ӳ˵�1
				  keyt=keyt%4+1;
				  highlight(keyt);
					  
	 SPeech(testmenu[keyt-1]);   //���÷�������������ָ����������  
//while(TTS_Busy==1){};
 delay_ms(1);
				  break;
				case NOVELMENU://�Ӳ˵�2
					keyf=keyf%2+1;
				  highlight(keyf);
						 SPeech(novelmenu[keyf-1]);   //���÷�������������ָ���������� 
             delay_ms(1);
				  break;			
				case PRIMODE://����ģʽ���ޱ仯
;
				break;
				case NOVELMODE://�Ķ�ģʽ�£�ʵ�ַ�ҳ�����Ķ�����
					;//read_act(Dirname[keyf-1]);
				  break;	
	
    }
}
//keyup ��������ʱ��ִ�еĺ���
	void e2_event_function(u8 *nxt_state){
				u8 cur_state;   
				cur_state = *nxt_state; 
		//dis(0);
switch(cur_state)
{
	case PRIMENU:
	case NOVELMENU:
	//	case POEMENU:
		*nxt_state=INITMENU;
	  UIfun(*nxt_state);
	break;
	case INITMENU:
		;
	break;
	default:
		if(keyi==1)//����ĩ�ε����˵�������ťkeyf�б��������ĸ���Ŀ¼�˵�
	//keyi=1����Ǵ���ä�Ļ����Ķ�ģʽ��
			
	  *nxt_state=PRIMENU;
		else{
		if(keyi==2){
			//keyi=2����Ǵ���С˵�Ķ�ģʽ��
		  *nxt_state=NOVELMENU;
		}

		}

		UIfun(*nxt_state);
	break;
	}
}
	
u8 key_v;
int main(void)
{	
	
 	u8 state=0;
		delay_init();	    	 //��ʱ������ʼ��	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		      //�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ115200	
 	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();					  //��ʼ������
	LCD_Init();			   		//��ʼ��LCD   
	W25QXX_Init();				//��ʼ��W25Q128
	
		//TTS_Init();
 	my_mem_init(SRAMIN);	//��ʼ���ڲ��ڴ��
	exfuns_init();				//Ϊfatfs��ر��������ڴ�  
	SUOCUN_init();//��������ʼ��
		font_init();
 	f_mount(fs[0],"0:",1); 		//����SD��	��0;�޴���	
	POINT_COLOR=RED;
		while(SD_Init())			//���SD��
	{
			LCD_ShowString(30,70,200,16,16,"SD Card Failed!check it");
			delay_ms(200);
			LCD_Fill(30,70,200+30,70+16,WHITE);
			LED0=!LED0;//DS0��˸
			delay_ms(200);		    
	}			
			
		UIfun(state);
		dis(0);
while(1){
		key_v=KEY_Scan(0);	
	if(key_v==1)
			e0_event_function(&state);
else if(key_v==4)
			e1_event_function(&state);
	else	if(key_v==5||back_flag==1||contents_back==1){
			dis(0);
		cata_page=0;cata_num=0;Tkey=1;
			back_flag=0;contents_back=0;read_back=0;
						e2_event_function(&state);	
}		
	}
}

void CdlNum_Gets(int TLnum,const TCHAR* path1,const TCHAR* path2,const TCHAR* path3,const TCHAR* path4,const TCHAR* path5){
	Tqt[0]=0;	Trmd[0]=0;
  Dqt[0]=0; Drmd[0]=0;
  	f_open(&fil_2,path1,FA_READ);	
			 for(i=1;i<TLnum;i++){
		f_read(&fil_2, &Tqt[i], sizeof (Tqt[i]), &br);
				 }
	f_close(&fil_2);
				 	f_open(&fil_2,path2,FA_READ);	
			 for(i=1;i<TLnum;i++)
					f_read(&fil_2, &Trmd[i], sizeof (Trmd[i]), &br);	
f_close(&fil_2);				 
	 f_open(&fil_2,path3,FA_READ);	
			 for(i=1;i<TLnum;i++){
	
				 f_read(&fil_2, &Dqt[i], sizeof (Dqt[i]), &br);
			 }
f_close(&fil_2);	
					 	f_open(&fil_2,path4,FA_READ);	
			 for(i=1;i<TLnum;i++)
					f_read(&fil_2, &Drmd[i], sizeof (Drmd[i]), &br);	
f_close(&fil_2);	
memset(list,'\0',sizeof(list));			 
	 f_open(&fil_2,path5,FA_READ);
		for(i=0;i<TLnum;i++)	{
	 f_gets(SMbuf,70,&fil_2);
			memcpy(list[i],SMbuf,sizeof(SMbuf));	
	}
	f_close(&fil_2);	
}

//Ŀ¼�˵���ʾ���ܹ���Ŀ¼����Ϊ All_num����ҳ��ʾ����Ϊ One_num
void Dis_Catamenu(int One_num,int All_num,const TCHAR* path1,const TCHAR* path2){
								 LCD_Clear(WHITE);	
								for(i=0;i<One_num;i++)
													Show_Str(20,30*(i+1),400,24,list[One_num*cata_page+i],24,1); 
								 T_highlight(Tkey);
					//	SPeech(list[cata_page*One_num+cata_num],sizeof(list[cata_page*One_num+cata_num]));  
	
	SPeech(list[cata_page*One_num+cata_num]);
	
            delay_ms(1);  
		while(1){
		key_v=KEY_Scan(0);	
	if(key_v==1){ 
		f_open(&fil_3,path1,FA_READ);
		f_open(&fil_1,path2,FA_READ);
		if(Tkey==cata_num+1){ 
s=One_num*cata_page+cata_num;			
  f_lseek(&fil_3,Tqt[s]*100+Trmd[s]);
	f_lseek(&fil_1,Dqt[s]*1000+Drmd[s]);	
			novel_read(keyf);
		if(read_back==1)
		{	 UIfun(NOVELMODE); }//ÿ�½��Ķ��귵��֮���ӿ�ͷ�½�Ŀ¼ѡ���ӵ�ǰ���ڵ��½�Ŀ¼ѡ��
	}
		}
		else if(key_v==2){//�½�Ŀ¼ѡ���
						cata_num++; Tkey=Tkey%One_num+1;//����־�����仯
			 T_highlight(Tkey);
			//	Speech(list[cata_page*One_num+cata_num],sizeof(list[cata_page*One_num+cata_num]));
SPeech(list[cata_page*One_num+cata_num]);			
       delay_ms(1);
		//	}
				if(cata_num==One_num){  cata_page++; cata_num=0; LCD_Clear(WHITE);	T_highlight(Tkey);
							          	for(i=0;i<One_num;i++)
													Show_Str(20,30*(i+1),400,24,list[One_num*cata_page+i],24,1); }
			if(One_num*cata_page+cata_num==All_num){ Tkey=1; cata_page=0;cata_num=0;LCD_Clear(WHITE);	T_highlight(Tkey);
								          for(i=0;i<One_num;i++)
													Show_Str(20,30*(i+1),400,24,list[One_num*cata_page+i],24,1);}//ѡ��ĩ�½����ִӿ�ͷ�½ڿ�ʼѡ��	
							 }
    else if(key_v==5||read_back==1)
		{				contents_back=1;read_back=0;
		
		break;		}
		}	
	}
//0���˵���I,II��III���˵��Ľ�����ʾ����
void UIfun(u8 level){    
	          							LCD_Clear(WHITE);//�����л�ǰ��������
							POINT_COLOR=BLUE;

					switch(level){
						case 0://��ʾ���˵�Ŀ¼
							
						
						//	keyi=1;//��Ӧ����־������ʼ��
							 SPeech(initmenu[keyi]);   //���÷�������������ָ���������� 
             delay_ms(1);
						
							Show_Str(60,70,320,32,initmenu[1],32,1);
			    	 	Show_Str(60,110,320,32,initmenu[2],32,1);//for(u8 i=0;i<3;i++)
						  //Show_Str(60,150,320,32,initmenu[3],32,1);
						  highlight2(keyi);//״̬�л��󣬹��λ�ñ���λ������
						break;
						case 1://��ʾ����˵����溯��
							//keyt=1;
						 SPeech(testmenu[keyt-1]);   //���÷�������������ָ���������� 
             delay_ms(1);
							Show_Str(60,70,500,24,testmenu[0],24,1);
							Show_Str(60,100,500,24,testmenu[1],24,1);
							Show_Str(60,130,500,24,testmenu[2],24,1);
 							Show_Str(60,160,500,24,testmenu[3],24,1);
						//	Show_Str(40,220,200,24,testmenu[0],24,1);
						  highlight(keyt);//״̬�л��󣬹��λ�ñ���λ������
						break;
						case 2://��ʾSD���ļ�Ŀ¼�˵�����
						 SPeech(novelmenu[keyf-1]);   //���÷�������������ָ���������� 
             delay_ms(1);
							Show_Str(60,70,500,24,novelmenu[0],24,1);
							Show_Str(60,100,200,24,novelmenu[1],24,1);
						  highlight(keyf);//״̬�л��󣬹��λ�ñ���λ������
						break;
								
						case 4://����ģʽ
						prim_learn(keyt);						
						break;
						
						case 5:
							if(keyf==1){ 
CdlNum_Gets(58,"0:/С˵/��������������/Toffqt.dat","0:/С˵/��������������/Toffrmd.dat","0:/С˵/��������������/Doffqt.dat","0:/С˵/��������������/Doffrmd.dat","0:/С˵/��������������/list.txt");	
	Dis_Catamenu(14,58,"0:/С˵/��������������/text.txt","0:/С˵/��������������/data.txt");
}
						else 						
							if(keyf==2){	
CdlNum_Gets(36,"0:/С˵/��ķ�������ռ�/Toffqt.dat","0:/С˵/��ķ�������ռ�/Toffrmd.dat","0:/С˵/��ķ�������ռ�/Doffqt.dat","0:/С˵/��ķ�������ռ�/Doffrmd.dat","0:/С˵/��ķ�������ռ�/list.txt");								
			Dis_Catamenu(14,36,"0:/С˵/��ķ�������ռ�/text.txt","0:/С˵/��ķ�������ռ�/data.txt");
							}
							else			
							novel_read(keyf);
						break;					
					};
	}
										
					
void prim_learn(u8 tline){

		 switch(tline){
			 case 1:		//ƴ����ʾ
//Dividtxt("0:/ä�Ļ���ѧϰ/ƴ��/��ĸ��ĸ/��ĸ��ĸ.txt","0:/ä�Ļ���ѧϰ/ƴ��/��ĸ��ĸ/smym.txt","0:/ä�Ļ���ѧϰ/ƴ��/��ĸ��ĸ/data.txt","0:MWOFFSET1.dat","0:PGMEMORY1.dat");
pin=1;
	SPeech("[i1]");
			 
			 f_open(&fil_2, "0:MWOFFSET1.dat", FA_READ);
			 count_s=0;
while(1)	{		 
				f_read(&fil_2, &P[count_s], sizeof (P[count_s]), &br); 
count_s++;
if(f_tell(&fil_2)==f_size(&fil_2))
break;}
f_close(&fil_2);	
				 f_open(&fil_2, "0:PGMEMORY1.dat", FA_READ);
				f_read(&fil_2, &page, sizeof (page), &br);
f_read(&fil_2, &Pdata, sizeof (Pdata), &br);
f_close(&fil_2);
	 		f_open(&fil_0,"0:/ä�Ļ���ѧϰ/ƴ��/��ĸ��ĸ/data.txt",FA_READ);	
  	f_open(&fil_1,"0:/ä�Ļ���ѧϰ/ƴ��/��ĸ��ĸ/smym.txt",FA_READ);	
			 Dis_primary(); 
			 Page_turn();
			 break;
			 case 2:		//������ʾ
//Dividtxt("0:/ä�Ļ���ѧϰ/ƴ��/�Գ����ڼ�����/��������.txt","0:/ä�Ļ���ѧϰ/ƴ��/�Գ����ڼ�����/yjsd.txt","0:/ä�Ļ���ѧϰ/ƴ��/�Գ����ڼ�����/data.txt","0:MWOFFSET2.dat","0:PGMEMORY2.dat");
pin=2;	 SPeech("[i1]");
			 f_open(&fil_2, "0:MWOFFSET2.dat", FA_READ);
			 count_s=0;
while(1)	{		 
				f_read(&fil_2, &P[count_s], sizeof (P[count_s]), &br); 
count_s++;
if(f_tell(&fil_2)==f_size(&fil_2))
break;}


f_close(&fil_2);	
				 f_open(&fil_2, "0:PGMEMORY2.dat", FA_READ);
				f_read(&fil_2, &page, sizeof (page), &br);
f_read(&fil_2, &Pdata, sizeof (Pdata), &br);
f_close(&fil_2);
	 		f_open(&fil_0,"0:/ä�Ļ���ѧϰ/ƴ��/�Գ����ڼ�����/data.txt",FA_READ);	
  	f_open(&fil_1,"0:/ä�Ļ���ѧϰ/ƴ��/�Գ����ڼ�����/yjsd.txt",FA_READ);	
Dis_primary(); 
			 Page_turn();
			 break;
			 case 3:		//��ʾ�����㽭����ѧʵ����
//Dividtxt("0:/ä�Ļ���ѧϰ/���ּ����/���ּ����.txt","0:/ä�Ļ���ѧϰ/���ּ����/numpunc.txt","0:/ä�Ļ���ѧϰ/���ּ����/data.txt","0:MWOFFSET3.dat","0:PGMEMORY3.dat");
pin=3;		 SPeech("[i1]");	

			 f_open(&fil_2, "0:MWOFFSET3.dat", FA_READ);
			 count_s=0;
while(1)	{		 
				f_read(&fil_2, &P[count_s], sizeof (P[count_s]), &br); 
count_s++;
if(f_tell(&fil_2)==f_size(&fil_2))
break;}
f_close(&fil_2);	
				 f_open(&fil_2, "0:PGMEMORY3.dat", FA_READ);
				f_read(&fil_2, &page, sizeof (page), &br);
f_read(&fil_2, &Pdata, sizeof (Pdata), &br);
f_close(&fil_2);
	 		f_open(&fil_0,"0:/ä�Ļ���ѧϰ/���ּ����/data.txt",FA_READ);	
  	f_open(&fil_1,"0:/ä�Ļ���ѧϰ/���ּ����/numpunc.txt",FA_READ);	
Dis_primary(); 
		Page_turn();
			 break;
			 case 4:
//Dividtxt("0:/ä�Ļ���ѧϰ/Ӣ����ĸ/Ӣ����ĸ.txt","0:/ä�Ļ���ѧϰ/Ӣ����ĸ/A-Z.txt","0:/ä�Ļ���ѧϰ/Ӣ����ĸ/data.txt","0:MWOFFSET4.dat","0:PGMEMORY4.dat");
 pin=4;    SPeech("[d]"); 	
			 f_open(&fil_2, "0:MWOFFSET4.dat", FA_READ);
			 count_s=0;
while(1)	{		 
				f_read(&fil_2, &P[count_s], sizeof (P[count_s]), &br); 
count_s++;
if(f_tell(&fil_2)==f_size(&fil_2))
break;}
f_close(&fil_2);	
				 f_open(&fil_2, "0:PGMEMORY4.dat", FA_READ);
				f_read(&fil_2, &page, sizeof (page), &br);
f_read(&fil_2, &Pdata, sizeof (Pdata), &br);
f_close(&fil_2);
	 		f_open(&fil_0,"0:/ä�Ļ���ѧϰ/Ӣ����ĸ/data.txt",FA_READ);	
  	f_open(&fil_1,"0:/ä�Ļ���ѧϰ/Ӣ����ĸ/A-Z.txt",FA_READ);	
Dis_primary();
	Page_turn();
			break; 
	 }
 }


void novel_read(u8 tline){

		 switch(tline){
			 case 1://�շ�����
	 
 		memset(SDbtmp,'\0',sizeof(SDbtmp));	
Dis_novel("��������������",20,20);
NPage_turn("��������������","0:/С˵/��������������/OFFSET.dat",P[0],P[1],20,20,40);
			 break;
			 case 2:		//��������
memset(SDbtmp,'\0',sizeof(SDbtmp));	
Dis_novel("��ķ�������ռ�",20,20);
NPage_turn("��ķ�������ռ�","0:/С˵/��ķ�������ռ�/OFFSET.dat",P[2],P[3],20,20,40);			
			 break;
		 }
}

void Dis_primary(){
LCD_Clear(WHITE);	
Show_Str(10,15,200,24,"ä�Ļ���ѧϰ",24,1);	
	 SPeech("[i1]");  
	memset(nbuf,'\0',sizeof(nbuf));	
	memset(SMbuf,'\0',sizeof(SMbuf));
for(count_s=0;count_s<10;count_s++){
	f_gets(BUF,128,&fil_0);
  memcpy(SDbtmp[count_s],BUF,12);		 
	f_gets(BUF,128,&fil_1);	
	memcpy(nbuf,BUF,strlen(BUF)-2);
		strcat(SMbuf,nbuf); 

	switch(strlen(nbuf)){
		case 1:
	       strncat(SMbuf,"    ",4);break;
		case 2:
			 strncat(SMbuf,"   ",3);break;
		case 3:
			 strncat(SMbuf,"  ",2);break;
		case 4:
			 strncat(SMbuf," ",1);break;
	}
	
		if(strlen(nbuf))
	{strcat(PMbuf,nbuf);
	switch(keyt)
	{
		case 1 :{ SPeech("[i1]");	strcat(PMbuf,"1");} break; 
		case 2 :{SPeech("[i1]"); if(!strcmp(nbuf,"��ƽ")||!strcmp(nbuf,"��ƽ")||!strcmp(nbuf,"����")||!strcmp(nbuf,"ȥ��"))  ;else strcat(PMbuf,"1");} break;
		case 3 : SPeech("[i1]");	break;
		case 4 :   SPeech("[d]");	break;
	}
strncat(PMbuf,"[p500]",1);
}
	memset(nbuf,'\0',sizeof(nbuf));	
if(count_s==9){	
	Show_Str(18,180,800,32,(u8 *)SMbuf,32,1);	
	SPeech((u8 *)PMbuf); 
	memset(SMbuf,'\0',strlen(SMbuf));
	memset(PMbuf,'\0',strlen(PMbuf));
	LCD_ShowBraille(28,240,SDbtmp);
	DX_ShowBraille(SDbtmp);
		memset(SDbtmp,'\0',sizeof(SDbtmp));	
		 }

    } 
	}

void Page_turn(){
	 while(1){
	key_v=KEY_Scan(0);
						if(key_v==2){		//�·���������
if(f_tell(&fil_0)!=Pdata*10*page){//�����дָ��û��ָ���ļ�ĩβ
f_lseek(&fil_0,f_tell(&fil_0));
f_lseek(&fil_1,f_tell(&fil_1));
	}
else{
	f_lseek(&fil_0,0);
f_lseek(&fil_1,0);
	}
Dis_primary();					
					}
		else
if(key_v==3){		//�Ϸ���������
	if(f_tell(&fil_1)!=P[1]){//	�����дָ��û��ָ���ļ���ͷ
	j=f_tell(&fil_0)/(Pdata*10)-1;
	f_lseek(&fil_0,Pdata*10*(j-1));
	f_lseek(&fil_1,P[j-1]);}
	else{
	f_lseek(&fil_0,Pdata*10*(page-1));//��ʾ���һҳ
	f_lseek(&fil_1,P[page-1]);	}	
	Dis_primary();	
         }
else 
if(key_v==5){

	back_flag=1;
	f_close(&fil_0);
	f_close(&fil_1);break;}
           }	
				 }


				 void Dis_novel(u8*str , u8 r1 , u8 r2){          //LCD��һ����ʾr1���ֽڣ��ڶ�����ʾr2���ֽ�
					LCD_Clear(WHITE);		
				 	POINT_COLOR=RED;
	Show_Str(10,15,200,24,str,24,1);	
	POINT_COLOR=BLUE;
	f_gets(shuru1,r1+r2+1,&fil_3);
	 Show_Str(20,180,800,32,(u8 *)shuru1,32,1);
			SPeech(shuru1);			 
			   delay_ms(1);		 

		f_gets(BUF,121,&fil_1);	
	 for(count_s=0;count_s<20;count_s++)
  memcpy(FCbtmp[count_s],BUF+count_s*6,6);	
		
LCD_WShowBraille(30,240,FCbtmp);
		DX_FCBraille(FCbtmp);
		memset(SDbtmp,'\0',sizeof(SDbtmp));		
 
	}

void NPage_turn(u8*str,const TCHAR* path,DWORD P1,DWORD P2,u8 r1,u8 r2,u8 r){ //LCDһҳ��ʾr���ֽ�
	while(1){
	key_v=KEY_Scan(0);
						if(key_v==2){		//�·���������
if(f_tell(&fil_3)!=f_size(&fil_3)){//�����дָ��û��ָ���ļ�ĩβ
f_lseek(&fil_3,f_tell(&fil_3));
f_lseek(&fil_1,f_tell(&fil_1));
	}
else{
	f_lseek(&fil_3,0);
f_lseek(&fil_1,0);
	}
		P1=f_tell(&fil_3);
	P2=f_tell(&fil_1);
	 f_open(&fil_2,path, FA_WRITE | FA_OPEN_ALWAYS);
	 f_write(&fil_2,&P1, sizeof(P1), &bw);
		 f_write(&fil_2,&P2, sizeof(P2), &bw);
		f_close(&fil_2);
Dis_novel(str,r1,r2);
	
					}
//	Show_Str(30,20*(count_s+1),200,16,(u8 *)buf,16,0);	 			
		//��ʾä�ĵ����Ӧ����	
		else
if(key_v==3){		//�Ϸ���������
	if(f_tell(&fil_3)!=r){//	�����дָ��û��ָ���ļ���ͷ
//	j=f_tell(&fil_1)/120-1;
	f_lseek(&fil_1,f_tell(&fil_1)-240); 
	f_lseek(&fil_3,f_tell(&fil_3)-2*r);}
	else{
	f_lseek(&fil_1,f_size(&fil_1)-120);//��ʾ���һҳ
	f_lseek(&fil_3,f_size(&fil_3)-r);}
			P1=f_tell(&fil_3);
	P2=f_tell(&fil_1);
	 f_open(&fil_2, path, FA_WRITE | FA_OPEN_ALWAYS);
	 f_write(&fil_2,&P1, sizeof(P1), &bw);
		 f_write(&fil_2,&P2, sizeof(P2), &bw);
		f_close(&fil_2);
	Dis_novel(str,r1,r2);	
         }
else
	if(key_v==4){
f_open(&fil_2, path, FA_READ);
	f_read(&fil_2, &P1, sizeof (P1), &br);
	f_read(&fil_2, &P2, sizeof (P2), &br);			 
f_close(&fil_2);		
		f_lseek(&fil_3,P1);
f_lseek(&fil_1,P2);
	Dis_novel(str,r1,r2);}	
else 
if(key_v==5){
	dis(0);
	back_flag=1;read_back=1;
		f_close(&fil_3);
	f_close(&fil_1);
break;}
           }    
				 }				 
 
