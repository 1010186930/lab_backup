#include "sys.h"
#include "delay.h"
#include "usart.h" 		 	 
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
#include "timer.h"
#include<stdlib.h>
#include<string.h>
#define MAXSIZE 10//�����С����
#define MAXBK 10//��ǩ��Ŀ
#define MAXDR 10//��ҳ��ʾ����Ŀ¼��Ŀ
const char yue[]="2 3 4 5 6��  ��ĸ ����               ";
const char yue3[]="����  ����  ����                        ";
const char yuan[]="1 2 3 4 6�� ��ĸ ����n               ";
const char yuan3[]="��ĸ ����n  ��n  i��ng               ";
const char yue6[]="��ĸ u�� u��i u�� u�� ���� ��r       ";
const char ext[]=".c";//��ǩ����չ��
void k3_last(u8 n);//Ŀ¼�˺��ı��˵���һ��
void move_Bookmarkcursor_Last(u16 n);//ѡ����һ����ǩ
void selectSort(char(*pt)[50], int n);//��ǩ������
void select_Bookmark(u16 index);//ѡ��Ҫ�򿪵���ǩ����ȷ�ϼ��Ĺ�������
void move_Bookmarkcursor_Next(u16 n);//ѡ����һ����ǩ
FRESULT bookmark_Read(const u8*path,u8*buf_Read);
int display_Bookmark();//���������е�.c�ļ����Ұ�����ǩ1~10��˳������
u32 path_Change(u32 cnt1,u16 cnt2);//�õ�Ҫ�滻��ǩ�����ִ�������Ҫ�滻��ǩ1 XXX���õ��ִ���ǩ1
FRESULT create_New(const u8*path,const u8*path2,UINT nums);//path���ļ���·����path2��д����ַ�����,��дtext��дdata���д�ı����ڵ�·��
FRESULT times_Init(const u8*path);//��ʼ�� ��������.txt(nums.txt)����ʼֵΪ0��д��ɹ��󷵻�ֵΪ0
void Int_To_Str(int x, char* Str);//ʮ����ת�����ַ���
u32 times_Read(const u8*path);//�� ��������.txt(nums.txt)��ȡ������ǩ�Ĵ���
FRESULT times_Write(const u8*path);//д ��������.txt(nums.txt)�����Ӵ�����ǩ�Ĵ�����д��ɹ��󷵻�ֵΪ0
u16 scan_Bookmark (const u8* path,int num);//��ȡ��ǩ����Ŀ���ҽ�Ҫ�滻����ǩ����ֵ��nameReplaced
void findExt( char* file_name, char* name, char* ext);//�ó��ļ�������չ�����ļ���
u8 s_files(u8*);
void highlight( u8 );
int mouse=0;
int countdown;
int flag=0;
u8 k1_event(u8);
u8 k2_event();
void k3_event(u8);
int curplace=0;
u16 bkplace=0;//��ǩ��λ����Ϣ
u8 buf_Read[100]="";//�����ǩ�����ĵ�ַ
u8 path[200]={""};//ȫ�ֱ�������ŵ�ǰ��ַ
u8 nameReplaced[100]="";//Ҫ�滻����ǩ��
u8*pshu=0;
void k4_event();
void k5_event();
void k6_event();
char buffer1[38];
char buffer2[121]="";
FIL fil1,fil2;//fil3ɾ��
u8*pathtxt=0;
u8*pathdata=0;
int demo=1;
void dis_txt();
void play();
void reco();
DWORD P1,P2;//P1��text��λ�ã�P2��data��λ��
DWORD P3,P4;//P3�Ƕ�����text��λ�ã�P4�Ƕ�����data��λ��
u8 path_c[6*MAXSIZE]="";//�����ĵط�	

FRESULT res;
BYTE buffer[20*MAXSIZE]="";//����gb2312���룬һ�����������ֽ�
char filename[50][50]={{""}};//���fn�Ķ�ά����
char midname[50]="";//��Ҫ����������
char bookmarkname[10][50]={{""}};//�����ǩ���Ķ�ά����
char bkmidname[50]="";//�޸ĺ���Ҫ����������
int main()
{
	
	
	FRESULT res1;
	int key_v;
	u8 menu=0;
	int n_files;
	int bk_nums;
	delay_init();	    	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		
	uart_init(115200);	  	
	KEY_Init();				
	LCD_Init();//5510��width480 height800	
	W25QXX_Init();		
	my_mem_init(SRAMIN);	
	exfuns_init();				
	SUOCUN_init();
	font_init();
	f_mount(fs[0],"0:",1); 	
	POINT_COLOR=RED;
	TIM3_Int_Init(99,7199);//0.01s	
	times_Init("0:/nums.txt");
//	while(1)
//	{
////		key_v=KEY_Scan(0);
////		if(key_v==1&&demo==1)
//		Show_Str(60,90,800,32,"��",32,0);
//	}
//	return 0;
//	
//}
	//n_files=display_Bookmark("0:");
//	n_files=s_files("0:");
	strcpy((char*)path,"0:");
	
//д��ǩ��dir �� fil�������ڴ��������ģ�
//	while(1)
//	{
//		key_v=KEY_Scan(0);
//		if(key_v==1&&demo==1)
//		{
//			mouse=0;
//		  n_files=k1_event(curplace);
//		}
//		else if(key_v==2&&demo==0)
//		{
//			n_files=k2_event();
//			cnt1=times_Read("0:/num.txt");
//		  cnt2=scan_Bookmark("0:");//������ǩ�ĸ���
//			path_Change(cnt1,cnt2);
//			res1=create_New((const u8*)path_c,buffer,cnt3);
//			if(res1==FR_OK)
//				times_Write("0:/num.txt");
//			demo=1;
//		}
//		else if(key_v==2&&demo==1)
//		{
//			n_files=k2_event();
//		}
//		else if(key_v==3&&demo==1)
//		{
//		 k3_event(n_files);
//		}
//	}

//д��ǩ��dir��filͨ�������ڴ棩
//while(1)
//	{
//		key_v=KEY_Scan(0);
//		if(key_v==1&&demo==1)
//		{
//			mouse=0;
//		  n_files=k1_event(curplace);
//		}
//		else if(key_v==2)
//		{
//			n_files=k2_event();
//		}
//		else if(key_v==3)
//			bk_nums=display_Bookmark();//��ʾ��ǩ
//	}
//return 0;
//}
//����ǩ
//while(1)
//	{
//		key_v=KEY_Scan(0);
//		if(key_v==1&&demo==1)
//		{
//			mouse=0;
//		  n_files=k1_event(curplace);
//		}
//		else if(key_v==2)
//			n_files=k2_event();
//		else if(key_v==3&&demo==1)
//		 k3_event(n_files);
//		else if(key_v==4)
//		  k4_event();
//    else if(key_v==5)
//		  k5_event();
//		else if(key_v==6)
//		{
//			bk_nums=display_Bookmark();
//		}
//		else if(key_v==1&&demo==2)
//		{
//			select_Bookmark(bkplace);
//		}
//		else if(key_v==3&&demo==2)
//		 move_Bookmarkcursor_Next(bk_nums);
//	}
//	return 0;
//}
//��������+��ҳ+��ǩ
//while(1)
//	{
//		key_v=KEY_Scan(0);
//		if(key_v==1&&demo==1)
//		{
//			mouse=0;
//		  n_files=k1_event(curplace);
//		}
//		else if(key_v==2&&demo==1)
//			 k3_event(n_files);//Ŀ¼����һ��
//		else if(key_v==3&&demo==1)
//			k3_last(n_files);//Ŀ¼����һ��
//		else if(key_v==3&&demo==0)
//			k5_event();//�ı�����һҳ
//		else if(key_v==2&&demo==0)
//			 k4_event();//�ı�����һҳ
////		else if(key_v==4)
////		  k4_event();
//    else if(key_v==5)
//			n_files=k2_event();//��һ��
//		else if(key_v==6)
//			bk_nums=display_Bookmark();//��ʾ��ǩ
//		else if(key_v==1&&demo==2)
//			select_Bookmark(bkplace);//��ǩ��ȷ��
//		else if(key_v==3&&demo==2)
//			move_Bookmarkcursor_Last(bk_nums);//��ǩ����һ��
//		else if(key_v==2&&demo==2)
//			move_Bookmarkcursor_Next(bk_nums);//��ǩ����һ��
//		if(countdown==30000)
//		{
//			dis(0);
//			LCD_LED=0;
//			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,DISABLE);
//		}
//	}
//	return 0;
//}
//��ҳ���ܲ���
while(1)
	{
//		key_v=KEY_Scan(0);
//		if(key_v==1&&demo==1)
//		{
//			mouse=0;
//	   n_files=k1_event(curplace);
//		}
//			else if(key_v==2&&demo==1)
//			 k3_event(n_files);//Ŀ¼����һ��
//			else if(key_v==2&&demo==0)
//				n_files=k2_event();//��һ��
//		else if(key_v==3&&demo==0)
//			k4_event();//�ı�����һҳ
////		else if(key_v==1&&demo==0)
////			k5_event();//�ı�����һҳ
//		else if(key_v==1&&demo==0)
//			bk_nums=display_Bookmark();//��ʾ��ǩ
//		else if(key_v==2&&demo==2)
//			select_Bookmark(bkplace);//��ǩ��ȷ��
//		else if(key_v==1&&demo==2)
//			move_Bookmarkcursor_Last(bk_nums);//��ǩ����һ��
//		else if(key_v==3&&demo==2)
//			move_Bookmarkcursor_Next(bk_nums);//��ǩ����һ��
	Show_Str(60,32,800,32,"1234\r567891011121",32,0);
	}
	return 0;
}

//����ǩ����
//	while(1)
//	{
//		key_v=KEY_Scan(0);
//		if(key_v==1)
//		{
//			bk_nums=display_Bookmark();
//		}
//		else if(key_v==2&&demo==2)
//		{
//			select_Bookmark(bkplace);
//		}
//		else if(key_v==3&&demo==2)
//		{
//			 move_Bookmarkcursor(bk_nums);
//		}
//		
//	}
//	return 0;
//}
////			cnt1=times_Read("0:/num.txt");
//			printf("%d\r\n",cnt1);
//			LCD_Clear(WHITE);
//			display_Bookmark("0:");
//		}
//		else if(key_v==2)
//		{
//			times_Write("0:/num.txt");
//			bookmark_Read("0:/bookmark2.c",buf_Read);
//			printf("��¼������%s\r\n",buf_Read);
//		}
//		else if(key_v==3)
//		{
//			printf("����֮ǰ��ǩ�����Ĵ���  %d\r\n",cnt1);
//			cnt2=scan_Bookmark("0:");//������ǩ�ĸ���
//			printf("����֮ǰ��ǩ�ĸ���     %d\r\n",cnt2);
//			path_Change(cnt1,cnt2);
//			res1=create_New((const u8*)path_c,buffer,cnt3);
//			if(res1==FR_OK)
//				times_Write("0:/num.txt");
//			else
//				printf("����ʧ��\r\n");
//			cnt1=times_Read("0:/num.txt");
//			printf("����֮����ǩ�����Ĵ���  %d\r\n",cnt1);
//			cnt2=scan_Bookmark("0:");//������ǩ�ĸ���
//			printf("����֮����ǩ�ĸ���     %d\r\n",cnt2);
			
			
//			cnt2=scan_Bookmark("0:");//������ǩ�ĸ���
//			printf("����֮ǰ��ǩ�ĸ���     %d\r\n",cnt2);
//			path_Change(cnt1,cnt2);
//			res1=create_New((const u8*)path_c,buffer,cnt3);
//			if(res1==FR_OK)
//				times_Write("0:/num.txt");
//			else
//				printf("����ʧ��\r\n");
//			LCD_Clear(WHITE);
//			s_files("0:/01ä�Ļ���ѧϰ");
//		}
//	}
	

//ʦ��Ĳ���
//		while(1)
//	{
//	  key_v=KEY_Scan(0);
//		if(key_v==1&&demo==1)
//		{
//			mouse=0;
//		  n_files=k1_event(curplace);
//		}
//		 else if(key_v==3&&demo==1)
//			 k3_event(n_files);
//		else if(key_v==2)
//		  n_files=k2_event();
//	  else if(key_v==4&&demo==0)
//		  k4_event();
//    else if(key_v==5&&demo==0)
//		    k5_event();
//		else if(key_v==6&&demo==0)
//		    k6_event();
//		if(countdown==30000)
//		{
//			LCD_LED=0;
//			flag=1;
//		}
//		if(flag==1&&KEY_Scan(0)!=0)
//		{
//			countdown=0;
//			LCD_LED=1;
//		}
//	}
//	return 0;
//}


u8 s_files(u8*path)
{
	u8 res=0;
	DIR*dir=0;
	FILINFO*finfo=0;
	u8*fn=0;
	u8*pathp=0;
	int i=0;
	int j=0;//��Ļ��ʾλ�ã���������
	BYTE buffer[20*MAXSIZE]="";
	SPeech("[d]");
  dir=(DIR*)mymalloc(SRAMIN,sizeof(DIR));
	finfo =(FILINFO*)mymalloc(SRAMIN,sizeof(FILINFO));
	finfo->lfsize=_MAX_LFN*2+1;          
	finfo->lfname= mymalloc(SRAMIN,finfo->lfsize); 
  //ע�⣬����������finfo.lfanme֮ǰ����Ϊfinfo�����ڴ棬�ٲŻ���Ϊfinfo.lfname�����ڴ�
	//dir=(DIR*)mymalloc(SRAMIN,sizeof(DIR));
	//finfo =(FILINFO*)mymalloc(SRAMIN,sizeof(FILINFO));
	pathp=mymalloc(SRAMIN,511);
	pathp[0]=0;
	mymemset(pathp,0,511);
	memset(&filename[0][0],0,sizeof(char)*50*50);
	highlight(0);
	strcat((char*)pathp,(const char*)path);
  res=f_opendir(dir,(const TCHAR*)pathp);
	if(res==0)
	{
	  while(1)
		{
      res=f_readdir(dir,finfo);
      fn=(u8*)(*finfo->lfname?finfo->lfname:finfo->fname);		
		  if(!finfo->fname[0]||res!=FR_OK) break;
			if(finfo->fattrib==AM_DIR)
			{
				strcpy((u8*)filename[i],(u8*)fn);
				i++;
			}
		}
		if(i>MAXDR)
		{
			for(j=0;j<MAXDR;j++)
			Show_Str(60,32+42*j,800,42,(u8*)filename[j]+2,32,0);
		}
		else
		{
			for(j=0;j<i;j++)
			Show_Str(60,32+42*j,800,42,(u8*)filename[j]+2,32,0);
		}
		memset(midname,'\0',sizeof(midname));
		strncpy(midname,filename[0]+2,strlen(filename[0])-2);
		SPeech(midname);
	}	
	f_closedir(dir);
	myfree(SRAMIN,finfo->lfname);
	myfree(SRAMIN,dir);
  myfree(SRAMIN,finfo);
	myfree(SRAMIN,pathp);
	return i;
}


u8 k1_event(u8 curfiles)
{
  u8 res=0;
	DIR*dir=0;
	FILINFO*finfo=0;
	u8*fn=0;
	u8*pathp=0;
	int i=0;
	int j=0;
	u8 red=0;
	u8 ret=0;
  LCD_Clear(WHITE);
	SPeech("[i1][n1][s3]");
	dir=(DIR*)mymalloc(SRAMIN,sizeof(DIR));
	finfo =(FILINFO*)mymalloc(SRAMIN,sizeof(FILINFO));
	finfo->lfsize=_MAX_LFN*2+1;          
	finfo->lfname= mymalloc(SRAMIN,finfo->lfsize);
	pathp=mymalloc(SRAMIN,511);
  pathp[0]=0;
	strcat((char*)pathp,(char*)path);
	memset(path,0,200);
	memset(&filename[0][0],0,sizeof(char)*50*50);
	res=f_opendir(dir,(const TCHAR*)pathp);
	if(res==0)
	{
	  while(1)
		{
			res=f_readdir(dir,finfo);
		  fn=(u8*)(*finfo->lfname?finfo->lfname:finfo->fname);		
		  if(!finfo->fname[0]||res!=FR_OK) break;
			if(finfo->fattrib==AM_DIR)
			{
				if(i==curfiles) break;
				i++;
			}
		}
	}
  strcat((char*)pathp,"/");
	strcat((char*)pathp,(char*)fn);
	strcpy((char*)path,(char*)pathp);
	f_closedir(dir);
	i=0;
	res=f_opendir(dir,(const TCHAR*)pathp);
	if(res==0)
	{
		while(1)
		{
			res=f_readdir(dir,finfo);
			fn=(u8*)(*finfo->lfname?finfo->lfname:finfo->fname);		
			if(!finfo->fname[0]||res!=FR_OK) break;
			if(finfo->fattrib==AM_DIR)
			{
				strcpy((u8*)filename[i],(u8*)fn);
				i++;
			}
			else
			{
				demo=0;
				break;
			}
		}
		if(demo==1)
		{
			if(i>MAXDR)
			{
				for(j=0;j<MAXDR;j++)
				Show_Str(60,32+42*j,800,42,(u8*)filename[j]+2,32,0);
			}
			else
			{
				for(j=0;j<i;j++)
				Show_Str(60,32+42*j,800,42,(u8*)filename[j]+2,32,0);
			}
			memset(midname,'\0',sizeof(midname));
			strncpy(midname,filename[0]+2,strlen(filename[0])-2);
			SPeech(midname);
		}
	}
	f_closedir(dir);
	myfree(SRAMIN,finfo->lfname);
	myfree(SRAMIN,dir);
	myfree(SRAMIN,finfo);
	myfree(SRAMIN,pathp);
	curplace=0;
	if(demo==1)
	{
	  highlight(mouse);
	}
	else if(demo==0)
	{
		pathtxt=mymalloc(SRAMIN,511);
		pathdata=mymalloc(SRAMIN,511);
		pathtxt[0]=pathdata[0]=0;
		mymemset(pathtxt,0,511);
		mymemset(pathdata,0,511);
		strcat((char*)pathtxt,(char*)path);
		strcat((char*)pathdata,(char*)path);
		strcat((char*)pathtxt,"/text.txt"); 
		strcat((char*)pathdata,"/data.txt");
		ret=f_open(&fil1,(char*)pathtxt,FA_READ);
		red=f_open(&fil2,(char*)pathdata,FA_READ); 
		if(red==FR_OK&&ret==FR_OK)
			dis_txt();
	}
	return i;
}

u8 k2_event()
{
	FRESULT res=0;
	DIR*dir=0;
	FILINFO*finfo=0;
	u8*fn=0;
  u8*pathp=0;
	u8*patht=0;
	char*p=0;
	char*q=0;
	int i=0;
	int l=0;//��ʾ����
	int j;//�ļ����������ʼ����ֹλ��
	int k;//��Ŀ¼��־
	u8 fnt[100]={""};
	u8 bkname[100]={""};
	u32 cnt1;//������ǩ�Ĵ���
  u16 cnt2;//������ǩ�ĸ���
  u32 cnt3;//Ҫд���ı���ַ�ĳ���
	int index;//Ҫ�½�����ǩ���
	SPeech("[i1][n1][s3]");
	LCD_Clear(WHITE);
	dir=(DIR*)mymalloc(SRAMIN,sizeof(DIR));
	finfo =(FILINFO*)mymalloc(SRAMIN,sizeof(FILINFO));
	finfo->lfsize=_MAX_LFN*2+1;          
	finfo->lfname= mymalloc(SRAMIN,finfo->lfsize);
	memset(&filename[0][0],0,sizeof(char)*50*50);
	pathp=mymalloc(SRAMIN,511);
  pathp[0]=0;
	strcat((char*)pathp,(char*)path);
	memset(fnt,0,100);
	memset(bkname,0,100);//�ĵ�����������
	memset(path_c,0,6*MAXSIZE);
	memset(buffer,0,20*MAXSIZE);//Ҫд���ַ��·��
	if(demo==0)
	{
		f_close(&fil1);
		f_close(&fil2);
		myfree(SRAMIN,pathtxt);
		myfree(SRAMIN,pathdata);
		strcpy((char*)buffer,(const char*)path);
		cnt3=strlen((const char*)buffer);
		cnt1=times_Read("0:/nums.txt");
		cnt2=scan_Bookmark("0:",-1);//������ǩ�ĸ���
		index=path_Change(cnt1,cnt2);
		scan_Bookmark("0:",index);
		if(*nameReplaced!=NULL)
		{
			f_unlink((char*)nameReplaced);
		}
		q=strrchr((const char*)pathp,'/');
		strcpy((char*)bkname,q?q+3:pathp);//�����ֺ�'/'ȥ��
		strcat(path_c,bkname);
		strcat(path_c,ext);
		res=create_New((const u8*)path_c,buffer,cnt3);
		if(res==FR_OK)
			times_Write("0:/nums.txt");
		q=NULL;
	}
	demo=1;	
	p=strrchr((const char*)pathp,'/');
	strcpy(fnt,p?p+1:pathp);
	if(p!=NULL)
	{
		*p='\0';
		//pathp[(u8)p]='\0';//?
	}
	memset(path,0,200);
	strcpy((char*)path,(char*)pathp);
	res=f_opendir(dir,(const TCHAR*)pathp);//���޸Ĺ���·��
	if(res==0)
	{
	  while(1)
		{
		  res=f_readdir(dir,finfo);
		  fn=(u8*)(*finfo->lfname?finfo->lfname:finfo->fname);		
		  if(!finfo->fname[0]||res!=FR_OK) break;
			if(finfo->fattrib==AM_DIR)
			{
				strcpy((u8*)filename[i],(u8*)fn);
				if(!strcmp(fnt,fn))
					k=i;
				i++;
			}
		}
		if(i>MAXDR)
		{
			for(j=(k/MAXDR)*MAXDR;j<(k/MAXDR)*MAXDR+MAXDR;j++,l++)
			Show_Str(60,32+42*l,800,42,(u8*)filename[j]+2,32,0);
		}
		else
		{
			for(j=0;j<i;j++)
			Show_Str(60,32+42*j,800,42,(u8*)filename[j]+2,32,0);
		}
		memset(midname,'\0',sizeof(midname));
		strncpy(midname,filename[k]+2,strlen(filename[k])-2);
		if(!strcmp(midname,"��ʮһ�� u�� u��i u�� u�� ���� ��r"))
		{
			printf("=====================11OK=====================\r\n");
			SPeech("��ʮһ�� u�� u��i u�� u�� v�� ��r");
		}
		else if(!strcmp(midname,"��ʮ��� ����n ��n i��ng"))
		{
			printf("=====================15OK=====================\r\n");
			SPeech("��ʮ��� v��n ��n i��ng");
		}	
		else
			SPeech(midname);
		curplace=k;
		if(curplace>=MAXDR)
		{
			mouse=curplace%MAXDR;
			highlight(mouse);
		}
		else
		{
			mouse=curplace;
			highlight(mouse);
		}
	}
	f_closedir(dir);
	myfree(SRAMIN,finfo->lfname);
	myfree(SRAMIN,dir);
  myfree(SRAMIN,finfo);
	myfree(SRAMIN,pathp);
	return i;
}	


void k3_event(u8 n)  
{
	int j=0;
	int l=0;
	int curplace2;
	curplace=(curplace+1)%n;
	if(n>MAXDR)
	{
		if(curplace%MAXDR==0&&n>(curplace/MAXDR)*MAXDR+MAXDR)
		{
			LCD_Clear(WHITE);
			for(j=(curplace/MAXDR)*MAXDR;j<(curplace/MAXDR)*MAXDR+MAXDR;j++,l++)
			Show_Str(60,32+42*l,800,42,(u8*)filename[j]+2,32,0);
		}
		if(curplace%MAXDR==0&&n<=(curplace/MAXDR)*MAXDR+MAXDR)
		{
			LCD_Clear(WHITE);
			for(j=(curplace/MAXDR)*MAXDR;j<n;j++,l++)
			Show_Str(60,32+42*l,800,42,(u8*)filename[j]+2,32,0);
		}	
	}
	curplace2=curplace%MAXDR;
	mouse=curplace2;
	highlight(mouse);
	memset(midname,'\0',sizeof(midname));
	delay_ms(1);
	strncpy(midname,filename[curplace]+2,strlen(filename[curplace])-2);
	if(!strcmp(midname,"��ʮһ�� u�� u��i u�� u�� ���� ��r"))
	{
		printf("=====================11OK=====================\r\n");
		SPeech("��ʮһ�� u�� u��i u�� u�� v�� ��r");
	}
	else if(!strcmp(midname,"��ʮ��� ����n ��n i��ng"))
	{
		printf("=====================15OK=====================\r\n");
		SPeech("��ʮ��� v��n ��n i��ng");
	}
	else	
		SPeech(midname);
}
void k3_last(u8 n)
{
	int j=0;
	int l=0;
	int curplace2;
	curplace=(curplace-1)%n;
	if(n>MAXDR)
	{
		if(curplace<0)
		{
			LCD_Clear(WHITE);
			curplace=n-1;
			for(j=(curplace/MAXDR)*MAXDR;j<n;j++,l++)
			Show_Str(60,32+42*l,800,42,(u8*)filename[j]+2,32,0);
		}
		if((curplace+1)%MAXDR==0&&(curplace+1)!=0)
		{
			LCD_Clear(WHITE);
			for(j=(curplace/MAXDR)*MAXDR;j<(curplace/MAXDR)*MAXDR+MAXDR;j++,l++)
			Show_Str(60,32+42*l,800,42,(u8*)filename[j]+2,32,0);
		}
	}
	else 
	{
		if(curplace<0)
			curplace=n-1;
	}
	curplace2=curplace%MAXDR;
	mouse=curplace2;
	highlight(mouse);
	memset(midname,'\0',sizeof(midname));
	delay_ms(1);
	strncpy(midname,filename[curplace]+2,strlen(filename[curplace])-2);
	if(!strcmp(midname,"��ʮһ�� u�� u��i u�� u�� ���� ��r"))
	{
		printf("=====================11OK=====================\r\n");
		SPeech("��ʮһ�� u�� u��i u�� u�� v�� ��r");
	}
	else if(!strcmp(midname,"��ʮ��� ����n ��n i��ng"))
	{
		printf("=====================15OK=====================\r\n");
		SPeech("��ʮ��� v��n ��n i��ng");
	}
	else	
		SPeech(midname);
}
void k4_event()
{
	if(f_tell(&fil1)==f_size(&fil1))
		{	
			f_lseek(&fil2,0);
			f_lseek(&fil1,0);
		}
	P1=f_tell(&fil1);
	P2=f_tell(&fil2);
	LCD_Clear(WHITE);
	f_gets((char*)buffer2,121,&fil2);
	f_gets((char*)buffer1,38,&fil1);
	play();
}

void k5_event()
{ 
  if(f_tell(&fil1)==f_size(&fil1))
		{
			if(f_size(&fil1)%37==0)
				{
					f_lseek(&fil1,f_size(&fil1)-74);	
					f_lseek(&fil2,f_size(&fil2)-240);
				}
			else
				{
				  f_lseek(&fil1,f_size(&fil1)-f_size(&fil1)%37-37);	
				  f_lseek(&fil2,f_size(&fil2)-f_size(&fil2)%120-120);
				}		
		}			 
	else if(f_tell(&fil1)==37)
		{
			if(f_size(&fil1)%37==0)
				{
					f_lseek(&fil1,f_size(&fil1)-37);	
					f_lseek(&fil2,f_size(&fil2)-120);	
				}
			else
				{
					f_lseek(&fil1,f_size(&fil1)-f_size(&fil1)%37);	
					f_lseek(&fil2,f_size(&fil2)-f_size(&fil2)%120);	
				}
		}		
	else
		{				
			 f_lseek(&fil1,f_tell(&fil1)-74);	
			 f_lseek(&fil2,f_tell(&fil2)-240);	
		}
		P1=f_tell(&fil1);
		P2=f_tell(&fil2);
		LCD_Clear(WHITE);
	  f_gets(buffer2,121,&fil2);
	  f_gets(buffer1,38,&fil1);	
	  play();
}
void highlight(const u8 line)
{
	LCD_Fill(35,45,45,800,WHITE);//���ԭ��λ�ã���ɫ���	
	LCD_Fill(35,45+42*line,45,55+42*line,BLUE);
}

void dis_txt()
 {
	f_lseek(&fil1,0);
	f_lseek(&fil2,0);
	f_gets(buffer2,121,&fil2);
	f_gets(buffer1,38,&fil1);
  play();
 }


void play()
{
	int m;
	int l;
	char btmp[20][7]={""};
	LCD_Clear(WHITE);
	SPeech("[i1][n1]");
	delay_ms(10);
	printf("buffer1:%s\r\n",buffer1);
	if(strstr((const char*)path,"��ĸ"))
	{
		Show_Str(18,80,800,32,(u8*)buffer1,32,1);
		if(strstr(buffer1,"��e"))
			SPeech("ve1 2 3 4 5 6��");
		else if(strstr(buffer1,"��an"))
			SPeech("van1 1 2 3 4 6��");
		else if(strstr(buffer1,"��n"))
			SPeech("vn1 4 5 6��");
		else if(strstr(buffer1,"��"))
			SPeech("v1 3 4 6��");
		else
			SPeech(buffer1);
	}
	else if(strstr((const char*)path,"11��ʮһ�� u�� u��i u�� u�� ���� ��r"))
	{
		Show_Str(18,80,800,32,(u8*)buffer1,32,1);
		if(!strcmp(buffer1,yue6))
		{
			printf("=====================yue6OK=====================\r\n");
			SPeech("��ĸ u�� u��i u�� u�� v�� ��r");
		}	
		else if(!strcmp(buffer1,yue))
		{
			printf("=====================yueOK=====================\r\n");
			SPeech("2 3 4 5 6��  ��ĸ v��");
		}
			
		else if(strstr((const char*)buffer1,"����"))
		{
			printf("=====================����OK=====================\r\n");
			SPeech("v�� v�� v��");
		}
			
//		else if(strstr((const char*)buffer1,"����")&&strstr((const char*)buffer1,"u��"))
//		else if(!strcmp(buffer1,"��ĸ u��  u��i  u��  u��  ����  ��r   "))
//		{
//			printf("=====================OK=====================");
//			SPeech("��ĸ u�� u��i u�� u�� v�� ��r");
//		}	
		else		
		SPeech(buffer1);
	}
	else if(strstr((const char*)path,"15��ʮ��� ����n ��n i��ng"))
	{
		Show_Str(18,80,800,32,(u8*)buffer1,32,1);
		if(!strcmp(buffer1,yuan))
		{
			printf("=====================yuanOK=====================\r\n");
			SPeech("1 2 3 4 6�� ��ĸ v��n");
		}	
		else if(strstr((const char*)buffer1,"����n"))
		{
			printf("=====================����nOK=====================\r\n");
			SPeech("v��n v��n van3 v��n");
		}
		else if(!strcmp(buffer1,yuan3))
		{
			printf("=====================yuan3OK=====================\r\n");
			SPeech("��ĸ v��n ��n i��ng");
		}
		else		
		SPeech(buffer1);
	}
	else
	{
		Show_Str(18,80,800,32,(u8*)buffer1,32,1);		
		SPeech(buffer1);
	}	
	delay_ms(1);
	for(l=0;l<strlen(buffer2);l++)
	buffer2[l]=buffer2[l];
	buffer2[l]='\0';
m=strlen(buffer2)/6;
	    for(l=0;l<m;l++)
	    memcpy(btmp[l],buffer2+6*l,6);
		LCD_WShowBraille(m,30,240,btmp);
	  DX_FCBraille(btmp);
	memset(btmp,'\0',sizeof(btmp));
}
//void reco()
//{
// f_write(&fil3,&P1, sizeof(P1), &bw);
// f_write(&fil3,&P2, sizeof(P2), &bw);
//}

u16 scan_Bookmark (const u8* path,int num)//��ȡ��ǩ����Ŀ���ҽ�Ҫ�滻����ǩ����ֵ��nameReplaced
{
	u16 cnt=0;
	FRESULT res;
	DIR *dir;
	FILINFO *fno;
	u8*fn;
	char buf[10];//�洢fn
	char numtostr[5]="";
	memset(nameReplaced,0,100);
	memset(nameReplaced,0,50);
	dir=(DIR*)mymalloc(SRAMIN,sizeof(DIR));
	fno =(FILINFO*)mymalloc(SRAMIN,sizeof(FILINFO));
	fno->lfsize=_MAX_LFN*2+1;          
	fno->lfname= mymalloc(SRAMIN,fno->lfsize); 
	res = f_opendir(dir, (const TCHAR*)path);
	if(res==FR_OK&&fno->lfname!=NULL)
		{
			while(1)//��ѯ�ܵ���Ч�ļ���
			{
				res=f_readdir(dir,fno);       		//��ȡĿ¼�µ�һ���ļ�
				fn=(u8*)(*fno->lfname?fno->lfname:fno->fname);				
				if(res!=FR_OK||fno->fname[0]==0)break;	//������/��ĩβ��,�˳�		   
					res=f_typetell(fn);	
				if((res&0XFF)==0X31)//ȡ����λ,�����ǲ���.C��ǩ�ļ�
					{
						strncpy(buf,fn,6);
						if(num==MAXBK)
						{
							sprintf(numtostr, "%d", num);
							if(strstr(buf,"10"))
							{
								strcpy(nameReplaced,"0:/");
								strcat(nameReplaced,fn);
							}
						}
						else if(num>0)
						{
							sprintf(numtostr, "%d", num);
							if(strstr(buf,numtostr)!=NULL&&strstr(buf,"0")==NULL)
							{
								strcpy(nameReplaced,"0:/");
								strcat(nameReplaced,fn);
							}
						}
						cnt++;//��Ч�ļ�������1
					}								
			 }  
		} 
	f_closedir(dir);
	myfree(SRAMIN,fno->lfname);
	myfree(SRAMIN,dir);
	myfree(SRAMIN,fno);
	return cnt;
}
void findExt( char* file_name, char* name, char* ext)
{
		char* end;
		char* ptr = file_name;
		while (*ptr != '\0')
		{
			ptr++;//�Ƶ��ļ���ĩβ
		}
		end = ptr;//��һ��
		while(*ptr!='.')
		{
			ptr--;//�Ӻ���ǰ�ƶ���.��λ��
		}
		memcpy(name, file_name,  (ptr-file_name)*sizeof(char));
		memcpy(ext, ptr+1, (end - ptr ) * sizeof(char));
}
u32 times_Read(const u8*path)//�� ��������.txt(nums.txt)��ȡ������ǩ�Ĵ���
{
	DIR *dir;
	FIL *fil;
	FRESULT res;
	u32 cnt=0;
	dir=(DIR*)mymalloc(SRAMIN,sizeof(DIR));
	fil=(FIL*)mymalloc(SRAMIN,sizeof(FIL));
	res=f_opendir(dir,"0:");
	res=f_open(fil,(const TCHAR*)path,FA_READ);
	if(!res)
	{
		while(!res)
		{
			f_read(fil,&cnt,4,&br);
			if (res || br < 4) 
				break;
		}				
	}
	f_close(fil);
	f_closedir(dir);
	myfree(SRAMIN,dir);
	myfree(SRAMIN,fil);
	return cnt;	
}
FRESULT times_Write(const u8*path)//д ��������.txt(nums.txt)�����Ӵ�����ǩ�Ĵ�����д��ɹ��󷵻�ֵΪ0
{
	DIR *dir;
	FIL *fil;
	FRESULT res;
	u32 cnt=times_Read(path);
	dir=(DIR*)mymalloc(SRAMIN,sizeof(DIR));
	fil=(FIL*)mymalloc(SRAMIN,sizeof(FIL));
	res=f_opendir(dir,"0:");
	if(!res)
	{
		res=f_open(fil,(const TCHAR*)path,FA_READ|FA_WRITE);
		if(!res)
		{
			cnt=cnt+1;
			do
			{
				res = f_write(fil,&cnt,4,&bw);
				if(res)
					break;
			}
			while (bw <sizeof(cnt));
		}		
	}
	f_close(fil);
	f_closedir(dir);
	myfree(SRAMIN,fil);
	myfree(SRAMIN,dir);
	return res;	
}
FRESULT times_Init(const u8*path)//��ʼ�� ��������.txt(nums.txt)����ʼֵΪ0��д��ɹ��󷵻�ֵΪ0
{
	DIR *dir;
	FIL *fil;
	FRESULT res;
	u32 cnt=0;
	dir=(DIR*)mymalloc(SRAMIN,sizeof(DIR));
	fil=(FIL*)mymalloc(SRAMIN,sizeof(FIL));
	res=f_opendir(dir,"0:");
	if(!res)
	{
		res=f_open(fil,(const TCHAR*)path,FA_CREATE_NEW|FA_WRITE);
			if(!res)
				res=f_write(fil,&cnt,4,&bw);
	}
	f_close(fil);
	f_closedir(dir);
	myfree(SRAMIN,fil);
	myfree(SRAMIN,dir);
	return res;	
}
void Int_To_Str(int x, char* Str)//����ת���ַ���
{
	int t;
	char* Ptr, Buf[5];
	int i = 0;
	Ptr = Str;
	if (x < 10)  // ������С��10��ת��Ϊ0x��ʽ 
	{
		*Ptr++ = x + 0x30;
	}
	else
	{
		while (x > 0)
		{
			t = x % 10;
			x = x / 10;
			Buf[i++] = t + 0x30; // ͨ����������ֱ��ASCII����ʽ  
		}
		i--;
		for (; i >= 0; i--)   // ���õ����ַ�������  
		{
			*(Ptr++) = Buf[i];
		}
	}
	*Ptr = '\0';
}
FRESULT create_New(const u8*path,const u8*path2,UINT nums)//path���ļ���·����path2��д����ַ�����,��дtext��дdata���д�ı����ڵ�·��
{
	DIR *dir;
	FIL *fil;
	FRESULT res;
	dir=(DIR*)mymalloc(SRAMIN,sizeof(DIR));
	fil=(FIL*)mymalloc(SRAMIN,sizeof(FIL));
	res=f_opendir(dir,"0:");
	if(!res)
	{
		res=f_open(fil,(const TCHAR*)path,FA_READ|FA_WRITE|FA_CREATE_ALWAYS);//�����½�д�룬Ҳ���������ļ�����д��
		res = f_write(fil,&P1,sizeof(P1),&bw);
		res = f_write(fil,&P2,sizeof(P2),&bw);
		if(!res)
		{
			do
			{
				res = f_write(fil,path2,nums,&bw);
				if(res)
					break;
			}
			while (bw <nums);
		}		
	}
	f_close(fil);
	f_closedir(dir);
	myfree(SRAMIN,fil);
	myfree(SRAMIN,dir);
	return res;	
}
u32 path_Change(u32 cnt1,u16 cnt2)
/*cnt1�Ǵ�����ǩ�Ĵ�����cnt2��������ǩ���� ���cnt2С��10������cnt2+1Ȼ��ת�����ַ�����
���cnt2=10����ʱ��cnt1+1������10�����滻��10����ǩ�����������ڣ�cnt1+1��%10����ǩ
ԭ�������10����ǩ��cnt1��ȻΪ10.������11����ǩ�൱���滻�ڣ�cnt1+1��%10����ǩ�����cnt1+1Ϊ����10����������cnt1=19.�������Ϊ20
���滻���ǵ�10����ǩ*/
{
	char idx[MAXSIZE]="";
	char bk[3*MAXSIZE]="��ǩ";
	char *str=idx;
	memset(path_c,0,6*MAXSIZE);
	strcpy((char*)path_c,"0:/");
	if(cnt2<=MAXBK-1)
	{
		cnt2++;
		Int_To_Str((int)cnt2, str);
		strcat(bk,str);
		strcat(bk," ");
		strcat(path_c,bk);
		return 0;
	}
	else if(cnt2==MAXBK)
	{
		if ((cnt1 + 1) % (MAXBK) == 0)
		{
			Int_To_Str(MAXBK, str);
			strcat(bk, str);
			strcat(bk," ");
			strcat(path_c, bk);
			return MAXBK;
		}
		else
		{
			cnt1 = (cnt1 + 1) % (MAXBK);
			Int_To_Str((int)cnt1, str);
			strcat(bk, str);
			strcat(bk," ");
			strcat(path_c, bk);
			return cnt1;
		}
	}
}
int display_Bookmark()//���������е�.c�ļ����Ұ�����ǩ1~10��˳������
{
	FRESULT res;
	int i=0;
	int line=0;
	int num=0;//��ǩ����
	DIR *bkdir;
	FILINFO *bkfileinfo;//�ļ���Ϣ
	u8 *fn;   			//���ļ���
	char *q=NULL;
	char speechname[50]="";
	char processedname[50]="";//�ļ���������չ��
	char extension[3]="";
	memset(processedname,0,50);
	memset(speechname,0,50);
	memset(&bookmarkname[0][0],0,sizeof(char)*10*50);
	LCD_Clear(WHITE);
	SPeech("[i1][n1][s3]");
	bkdir=(DIR*)mymalloc(SRAMIN,sizeof(DIR));
  bkfileinfo =(FILINFO*)mymalloc(SRAMIN,sizeof(FILINFO));
	bkfileinfo->lfsize=_MAX_LFN*2+1;          
	bkfileinfo->lfname= mymalloc(SRAMIN,bkfileinfo->lfsize);
	demo=2;
	bkplace=0;//��¼������ǩ����Ŀ¼��λ��
	highlight(0);
	memset(path,0,200);
	strcpy((char*)path,"0:");
//	num=scan_Bookmark("0:");
//	if(num==0)
//	{
//		LCD_Clear(WHITE);
//		Show_Str(60,242,500,42,"û����ǩ�ļ���",32,0);
//		SPeech("û����ǩ�ļ�");
//	}
	res=f_opendir(bkdir,(const char*)path);
	if(res==FR_OK)
	{
		while(1)//ȫ����ѯһ��
		{
			res=f_readdir(bkdir,bkfileinfo);//��ȡĿ¼�µ�һ���ļ�
			if(res!=FR_OK||bkfileinfo->fname[0]==0)break;	//������/��ĩβ��,�˳�		  
			fn=(u8*)(*bkfileinfo->lfname?bkfileinfo->lfname:bkfileinfo->fname);			 
			res=f_typetell(fn);	
			if((res&0XFF)==0X31)//�Ƿ�Ϊ��ǩ�ļ�	
			{
				findExt( (char*)fn, processedname, extension);
				strcpy((u8*)bookmarkname[line],processedname);
				line++;
				memset(processedname,0,50);
			}	    
		}
		selectSort(bookmarkname, line); 
		for(i=0;i<line;i++)
		Show_Str(60,32+42*i,800,42,(u8*)bookmarkname[i],32,0);
		memset(bkmidname,'\0',sizeof(bkmidname));
		strcpy(bkmidname,bookmarkname[0]);
		if(strstr(bkmidname,"��ʮһ�� u�� u��i u�� u�� ���� ��r"))
		{
			q = strchr(bkmidname, ' ');
			*(q+1) = '\0';
			strcpy(speechname, bkmidname);//
			strcat(speechname, "��ʮһ�� u�� u��i u�� u�� v�� ��r");
			printf("=====================11OK=====================\r\n");
			SPeech(speechname);
		}
		else if(strstr(bkmidname,"��ʮ��� ����n ��n i��ng"))
		{
			q=strchr(bkmidname,' ');
			*(q+1) = '\0';
			strcpy(speechname, bkmidname);//
			strcat(speechname,"��ʮ��� v��n ��n i��ng");
			printf("=====================15OK=====================\r\n");
			SPeech(speechname);
		}	
		else	
		SPeech(bkmidname);
	}
	num=line;
	f_closedir(bkdir);
	myfree(SRAMIN,bkfileinfo->lfname);
	myfree(SRAMIN,bkdir);
	myfree(SRAMIN,bkfileinfo);
	return num;
}
FRESULT bookmark_Read(const u8*path,u8*buf_Read)//����ǩ���ݣ���Ϊtext��offset��data��offset������ǩ��¼�ĵ�ַ
{
	DIR *dir;
	FIL *fil;
	FRESULT res;
	dir=(DIR*)mymalloc(SRAMIN,sizeof(DIR));
	fil=(FIL*)mymalloc(SRAMIN,sizeof(FIL));
	memset(buf_Read,0,100);
	P3=0;
	P4=0;
	res=f_opendir(dir,"0:");
	if(!res)
	{
		res=f_open(fil,(const TCHAR*)path,FA_READ);//�����½�д�룬Ҳ���������ļ�����д��
		res = f_read(fil,&P3,sizeof(P3),&br);
		res = f_read(fil,&P4,sizeof(P4),&br);
		for(;;)
		{
			res = f_read(fil,buf_Read,100,&br);
			//printf("%s\r\n",buf_Read);//��ʾ��ǩ·��
			if(res||br<100)break;
		}
	}
	f_close(fil);
	f_closedir(dir);
	myfree(SRAMIN,fil);
	myfree(SRAMIN,dir);
	return res;	
}
void select_Bookmark(u16 index)
/*i��0��ʼ��������Ԫ���±����ʼλ����ͬ���ҵ��±�Ϊindex��Ԫ�أ��򿪲��ҵ��ô���ǩ�ĺ�����
��·���浽path�У������path�е�text.txt��data.txt*/
{
//	FRESULT res=0;
//	DIR*dir=0;
//	FILINFO*finfo=0;
//	u8*fn=0;
	u8*pathp=0;
	int i=0;
	u8 red=0;
	u8 ret=0;
  LCD_Clear(WHITE);
	
//	dir=(DIR*)mymalloc(SRAMIN,sizeof(DIR));
//	finfo =(FILINFO*)mymalloc(SRAMIN,sizeof(FILINFO));
//	finfo->lfsize=_MAX_LFN*2+1;          
//	finfo->lfname= mymalloc(SRAMIN,finfo->lfsize);
	pathp=mymalloc(SRAMIN,200);
  pathp[0]=0;
	strcat((char*)pathp,"0:");
	memset(path,0,200);
//	res=f_opendir(dir,(const TCHAR*)pathp);
//	if(res==0)
//	{
//	  while(1)
//		{
//			res=f_readdir(dir,finfo);
//		  fn=(u8*)(*finfo->lfname?finfo->lfname:finfo->fname);		
//		  if(!finfo->fname[0]||res!=FR_OK) break;
//		  res=f_typetell(fn);	
//		  if((res&0XFF)==0X31)//�Ƿ�Ϊ��ǩ�ļ�	
//			{
//				if(i==index) break;
//				i++;
//			}
//		}
//	}
////	for (i = 0; i < 10; i++)
////		printf("%s\r\n", bookmarkname[i]);
	
	i=index;
	strcat((char*)pathp,"/");
	strcat((char*)pathp,(char*)bookmarkname[i]);
	strcat((char*)pathp,".c");
//	f_closedir(dir);
////printf("%s\r\n",pathp);
	i=0;
	res=bookmark_Read(pathp,buf_Read);
	if(res==0)
		strcpy((char*)path,(char*)buf_Read);
//	myfree(SRAMIN,finfo->lfname);
//	myfree(SRAMIN,dir);
//	myfree(SRAMIN,finfo);
	myfree(SRAMIN,pathp);
	 if(demo==2)
	{
		demo=0;
		pathtxt=mymalloc(SRAMIN,511);
		pathdata=mymalloc(SRAMIN,511);
		pathtxt[0]=pathdata[0]=0;
		mymemset(pathtxt,0,511);
		mymemset(pathdata,0,511);
		strcat((char*)pathtxt,(char*)path);
		strcat((char*)pathdata,(char*)path);
		strcat((char*)pathtxt,"/text.txt"); 
		strcat((char*)pathdata,"/data.txt");
		ret=f_open(&fil1,(char*)pathtxt,FA_READ);
		red=f_open(&fil2,(char*)pathdata,FA_READ);
	  if(red==FR_OK&&ret==FR_OK)
		{
		  f_lseek(&fil1,P3);
		  f_lseek(&fil2,P4);
		  f_gets(buffer2,121,&fil2);
		  f_gets(buffer1,38,&fil1);
		  play();
	 	  P3=0;
		  P4=0;
		}
	}
}
void move_Bookmarkcursor_Next(u16 n)//ѡ����һ����ǩ
{
	u16 cursor;
	char *q=NULL;
	char speechname[50]="";
	memset(speechname,0,50);
	SPeech("[i1][n2]");
	bkplace=(bkplace+1)%n;
	cursor=bkplace;
	highlight(cursor);
	memset(bkmidname,'\0',sizeof(bkmidname));
	delay_ms(1);
	strcpy(bkmidname,bookmarkname[bkplace]);
	if(strstr(bkmidname,"��ʮһ�� u�� u��i u�� u�� ���� ��r"))
		{
			q = strchr(bkmidname, ' ');
			*(q+1) = '\0';
			strcpy(speechname, bkmidname);//
			strcat(speechname, "��ʮһ�� u�� u��i u�� u�� v�� ��r");
			printf("=====================11OK=====================\r\n");
			SPeech(speechname);
		}
		else if(strstr(bkmidname,"��ʮ��� ����n ��n i��ng"))
		{
			q=strchr(bkmidname,' ');
			*(q+1) = '\0';
			strcpy(speechname, bkmidname);//
			strcat(speechname,"��ʮ��� v��n ��n i��ng");
			printf("=====================15OK=====================\r\n");
			SPeech(speechname);
		}	
		else	
		SPeech(bkmidname);
}
void move_Bookmarkcursor_Last(u16 n)//ѡ����һ����ǩ
{
	u16 cursor;
	char *q=NULL;
	char speechname[50]="";
	memset(speechname,0,50);
	SPeech("[i1][n2]");
	if((bkplace-1)<0)
		bkplace=n-1;
	else
	bkplace=(bkplace-1)%n;
	cursor=bkplace;
	highlight(cursor);
	memset(bkmidname,'\0',sizeof(bkmidname));
	delay_ms(1);
	strcpy(bkmidname,bookmarkname[bkplace]);
	if(strstr(bkmidname,"��ʮһ�� u�� u��i u�� u�� ���� ��r"))
		{
			q = strchr(bkmidname, ' ');
			*(q+1) = '\0';
			strcpy(speechname, bkmidname);//
			strcat(speechname, "��ʮһ�� u�� u��i u�� u�� v�� ��r");
			printf("=====================11OK=====================\r\n");
			SPeech(speechname);
		}
		else if(strstr(bkmidname,"��ʮ��� ����n ��n i��ng"))
		{
			q=strchr(bkmidname,' ');
			*(q+1) = '\0';
			strcpy(speechname, bkmidname);//
			strcat(speechname,"��ʮ��� v��n ��n i��ng");
			printf("=====================15OK=====================\r\n");
			SPeech(speechname);
		}	
		else	
		SPeech(bkmidname);
}
void selectSort(char(*pt)[50], int n) 
/*����ǩ1~10������ǩ����ʽ����ǩX XXXXX,�β�ptΪָ���ά�ַ������ָ�롣��ǩ1 XXX����ǩ10 XXXС����Ϊ�ո��ASCII����20,0��ASCII����30.
�����ֵ�ASCII�����ֺͷ��ŵ�ASCII���������ǩ10 XXX�����ս��Ϊ��ǩ1 XXX,��ǩ10 XXX����ǩ2 XXX.....*/
{
	int i, j, k;
	char tmp[50];  //��ʱ�ַ�����
	for (i = 0; i < n - 1; i++)  //��������δ������ַ���������
	{
		k = i;  //����k��ŵ�ǰ��С�ַ������±�
		for (j = i + 1; j < n; j++)               //�����±��(i+1)~(n-1)�������ַ���
			if (strcmp(pt[k], pt[j]) > 0)  //�ַ�������������С�Ƚ�,���>0,��ִ��if�����
				k = j;                     //����ǰ��С���ַ����������±긳ֵ������k
		if (k != i)                       //���k������i,��ִ��if�����
		{   //�����ַ������н�������
			strcpy(tmp, pt[k]);
			strcpy(pt[k], pt[i]);
			strcpy(pt[i], tmp);
		}
	}
	if(n==MAXBK)//�����ǩ��Ŀ��10�����ͽ������½������Ƚ���10��1��˳��Ȼ�����ν���1�������ڵ�������ţ���10���������һλ
	{
		strcpy(tmp, pt[0]);
		strcpy(pt[0], pt[1]);
		strcpy(pt[1], tmp);
		for (i = 0; i < n-1; i++)
		{
			strcpy(tmp, pt[i]);
			strcpy(pt[i], pt[i+1]);
			strcpy(pt[i+1], tmp);
		}
	}
}
	
	
	