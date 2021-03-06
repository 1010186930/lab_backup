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
#include "ASCIItoBraille.h"
#include<stdlib.h>
#include<string.h>
#define MAXSIZE 10//数组大小基数
#define MAXBK 10//书签数目
#define MAXDR 10//单页显示最多的目录数目
#define BUFFER1_TOREAD 20
#define BUFFER2_TOREAD 120
void bookmarkRename(char *str);
void NoBlankSpace(char* pStr);//删去字符串中的空格
void selectSort_ascending(char(*pt)[100], int n);
void Rename_Bookmark (const u8* path);
int GetLastTwentyBits();
void LastPage();
void NextPage();
int GetNextTwentyBits();
u32 update_percent(u16 x,u16 y,u8 size,u32 fsize,u32 pos);//ascii到点序处理的进度
void ASCIItoBraille(char* toTranslate, char* translated);
const char ext[]=".c";//书签的扩展名
void k3_last(u8 n);//目录端和文本端的上一个
void move_Bookmarkcursor_Last(u16 n);//选择下一个书签
void selectSort(char(*pt)[100], int n);//书签排序函数
void select_Bookmark(u16 index);//选择要打开的书签，和确认键的功能类似
void move_Bookmarkcursor_Next(u16 n);//选择下一个书签
FRESULT bookmark_Read(const u8*path,u8*buf_Read);
int display_Bookmark();//遍历出所有的.c文件并且按照书签1~10的顺序排序
u32 path_Change(u32 cnt1,u16 cnt2);//得到要替换书签名的字串，例如要替换书签1 XXX，得到字串书签1
FRESULT create_New(const u8*path,const u8*path2,UINT nums);//path是文件的路径，path2是写入的字符数组,先写text再写data最后写文本存在的路径
FRESULT times_Init(const u8*path);//初始化 创建次数.txt(nums.txt)，初始值为0，写入成功后返回值为0
void Int_To_Str(int x, char* Str);//十进制转换成字符串
u32 times_Read(const u8*path);//读 创建次数.txt(nums.txt)获取创建书签的次数
FRESULT times_Write(const u8*path);//写 创建次数.txt(nums.txt)，增加创建书签的次数，写入成功后返回值为0
u16 scan_Bookmark (const u8* path,int num);//获取书签的数目并且将要替换的书签名赋值给nameReplaced
void findExt( char* file_name, char* name, char* ext);//得出文件名的扩展名和文件名
u8 s_files(u8*);
void highlight( u8 );
int mouse=0;
int countdown;
//int flag=3;//是否有data.txt,初始化为3
u8 k1_event(u8);
u8 k2_event();
void k3_event(u8);
int curplace=0;
u16 bkplace=0;//书签的位置信息
u8 buf_Read[20*MAXSIZE]="";//存放书签读到的地址
u8 path[200]={""};//全局变量，存放当前地址
u8 nameReplaced[100]="";//要替换的书签名
u8*pshu=0;
void k4_event(int flag);
void k5_event(int flag);
char buffer1[BUFFER1_TOREAD+2]="";//text
char buffer2[BUFFER2_TOREAD+1]="";//data
FIL fil1,fil2;//fil3删了 fil1打开text fil2打开data
u8*pathtxt=0;//text路径
//u8*pathdata=0;//data路径
int demo=1;
int num_Acquired=0;
void dis_txt(int flag);
void play();
void reco();
DWORD P1=0,P2=0;//P1是text的位置，P2是data的位置
DWORD P3=0,P4=0;//P3是读到的text的位置，P4是读到的data的位置

u8 path_c[10*MAXSIZE]="";//创建的地方	

FRESULT res;
BYTE buffer[20*MAXSIZE]="";//按照gb2312编码，一个汉字两个字节
char filename[50][50]={{""}};//存放fn的二维数组
char midname[50]="";//需要发声的数组
char bookmarkname[10][100]={{""}};//存放书签名的二维数组
char bkmidname[100]="";//修改后需要发声的数组
int main()
{
	
	
	FRESULT res1;
	int key_v;
	u8 menu=0;
	int n_files;
	int bk_nums;
	delay_init();	    	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		
	uart_init(9600);	  	
	KEY_Init();				
	LCD_Init();//5510的width480 height800	
	W25QXX_Init();		
	my_mem_init(SRAMIN);	
	exfuns_init();				
	SUOCUN_init();
	font_init();
	f_mount(fs[0],"0:",1); 	
	POINT_COLOR=RED;
	TIM3_Int_Init(99,7199);//0.01s	
	times_Init("0:/nums.h");
//	n_files=display_Bookmark("0:");
	n_files=s_files("0:");
	strcpy((char*)path,"0:");

//写书签（dir 和 fil都不是内存分配出来的）
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
//		  cnt2=scan_Bookmark("0:");//已有书签的个数
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

//写书签（dir和fil通过分配内存）
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
//			bk_nums=display_Bookmark();//显示书签
//	}
//return 0;
//}
//读书签
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
//按键重排+翻页+书签+ATB
while(1)
	{
		key_v=KEY_Scan(0);
		if(key_v==1&&demo==1)
		{
			mouse=0;
		  n_files=k1_event(curplace);
		}
		else if(key_v==2&&demo==1)
			 k3_event(n_files);//目录端下一个
		else if(key_v==3&&demo==1)
			k3_last(n_files);//目录端上一个
		else if(key_v==3&&demo==0)
			LastPage();//文本端上一页
		else if(key_v==2&&demo==0)
			 NextPage();//文本端下一页
//		else if(key_v==4)
//		  k4_event();
    else if(key_v==5)
			n_files=k2_event();//上一级
		else if(key_v==6)
			bk_nums=display_Bookmark();//显示书签
		else if(key_v==1&&demo==2)
			select_Bookmark(bkplace);//书签端确认
		else if(key_v==3&&demo==2)
			move_Bookmarkcursor_Last(bk_nums);//书签端上一个
		else if(key_v==2&&demo==2)
			move_Bookmarkcursor_Next(bk_nums);//书签端下一个
		if(countdown==30000)
		{
			dis(0);
			LCD_LED=0;
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,DISABLE);
		}
	}
	return 0;
}
//翻译测试
//while(1)
//	{
//		key_v=KEY_Scan(0);
//		if(key_v==1&&demo==1)
//		{
//			mouse=0;
//	   n_files=k1_event(curplace);
//		}
//			else if(key_v==3&&demo==1)
//			 k3_event(n_files);//目录端下一个
//			else if(key_v==1&&demo==1)
//			k3_last(n_files);
//			else if(key_v==2&&demo==0)
//				n_files=k2_event();//上一级
//		else if(key_v==3&&demo==0)
//			NextPage();//文本端下一页
//		else if(key_v==1&&demo==0)
//			LastPage();//文本端上一页
//		else if(key_v==2&&demo==1)
//			bk_nums=display_Bookmark();//显示书签
//		else if(key_v==2&&demo==2)
//			select_Bookmark(bkplace);//书签端确认
//		else if(key_v==1&&demo==2)
//			move_Bookmarkcursor_Last(bk_nums);//书签端上一个
//		else if(key_v==3&&demo==2)
//			move_Bookmarkcursor_Next(bk_nums);//书签端下一个
//	}
//	return 0;
//}

//读书签测试
//	while(1)
//	{
//		key_v=KEY_Scan(0);
//		if(key_v==1&&demo==1)
//		{
//			bk_nums=display_Bookmark();
//		}
//		else if(key_v==2&&demo==2)
//		{
//			select_Bookmark(bkplace);
//		}
//		else if(key_v==3&&demo==2)
//		{
//				move_Bookmarkcursor_Next(bk_nums);//书签端下一个
//		}
//		else if(key_v==3&&demo==0)
//			NextPage();//文本端下一页
//		else if(key_v==1&&demo==0)
//			LastPage();//文本端上一页
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
//			printf("记录的内容%s\r\n",buf_Read);
//		}
//		else if(key_v==3)
//		{
//			printf("创建之前书签创建的次数  %d\r\n",cnt1);
//			cnt2=scan_Bookmark("0:");//已有书签的个数
//			printf("创建之前书签的个数     %d\r\n",cnt2);
//			path_Change(cnt1,cnt2);
//			res1=create_New((const u8*)path_c,buffer,cnt3);
//			if(res1==FR_OK)
//				times_Write("0:/num.txt");
//			else
//				printf("创建失败\r\n");
//			cnt1=times_Read("0:/num.txt");
//			printf("创建之后书签创建的次数  %d\r\n",cnt1);
//			cnt2=scan_Bookmark("0:");//已有书签的个数
//			printf("创建之后书签的个数     %d\r\n",cnt2);
			
			
//			cnt2=scan_Bookmark("0:");//已有书签的个数
//			printf("创建之前书签的个数     %d\r\n",cnt2);
//			path_Change(cnt1,cnt2);
//			res1=create_New((const u8*)path_c,buffer,cnt3);
//			if(res1==FR_OK)
//				times_Write("0:/num.txt");
//			else
//				printf("创建失败\r\n");
//			LCD_Clear(WHITE);
//			s_files("0:/01盲文基础学习");
//		}
//	}
	

//师姐的操作
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
	int j=0;//屏幕显示位置，行数变量
	char processedname[50]="";//文件名不带扩展名
	char extension[3]="";
	SPeech("[d]");
	memset(processedname,0,50);
  dir=(DIR*)mymalloc(SRAMIN,sizeof(DIR));
	finfo =(FILINFO*)mymalloc(SRAMIN,sizeof(FILINFO));
	finfo->lfsize=_MAX_LFN*2+1;          
	finfo->lfname= mymalloc(SRAMIN,finfo->lfsize); 
  //注意，这个必须放在finfo.lfanme之前。先为finfo申请内存，再才会有为finfo.lfname申请内存
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
			res=f_typetell(fn);
//			printf("第%d个文件的文件类型是%x,文件名是%s\r\n",i,res,fn);
			if(finfo->fattrib==AM_DIR||(res&0XFF)==0X30)
			{
				if((res&0XFF)==0X30)
				{
					findExt((char*)fn, processedname, extension);
					strcpy((char*)filename[i],processedname);
				}
				else
				strcpy((char*)filename[i],(char*)fn);
				i++;
			}
		}
		if(i>MAXDR)
		{
			for(j=0;j<MAXDR;j++)
			Show_Str(60,32+42*j,800,42,(u8*)filename[j],32,0);
		}
		else
		{
			for(j=0;j<i;j++)
			Show_Str(60,32+42*j,800,42,(u8*)filename[j],32,0);
		}
//		memset(midname,'\0',sizeof(midname));
//		strncpy(midname,filename[0]+2,strlen(filename[0])-2);
		SPeech(filename[0]);
	}	
	f_closedir(dir);
	myfree(SRAMIN,finfo->lfname);
	myfree(SRAMIN,dir);
  myfree(SRAMIN,finfo);
	myfree(SRAMIN,pathp);
	dir=NULL;
	fn=NULL;
	finfo=NULL;
	pathp=NULL;
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
	char processedname[50]="";//文件名不带扩展名
	char extension[3]="";
	memset(processedname,0,50);
  LCD_Clear(WHITE);
	SPeech("[h0][n0]");
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
			res=f_typetell(fn);
			if(finfo->fattrib==AM_DIR||(res&0XFF)==0X30)
			{
				if(i==curfiles)
				{
					if((res&0XFF)==0X30)
						demo=0;
					else
						demo=1;
					break;
				}
				i++;
			}
		}
	}
  strcat((char*)pathp,"/");
	strcat((char*)pathp,(char*)fn);
	strcpy((char*)path,(char*)pathp);
	f_closedir(dir);
	i=0;
	if(demo==1)
	{
		res=f_opendir(dir,(const TCHAR*)pathp);
		if(res==0)
		{
			while(1)
			{
				res=f_readdir(dir,finfo);
				fn=(u8*)(*finfo->lfname?finfo->lfname:finfo->fname);		
				if(!finfo->fname[0]||res!=FR_OK) break;
				res=f_typetell(fn);
				if(finfo->fattrib==AM_DIR||(res&0XFF)==0X30)
				{
					if((res&0XFF)==0X30)
					{
						memset(processedname,0,50);
						findExt((char*)fn, processedname, extension);
						strcpy((char*)filename[i],processedname);
					}
					else
						strcpy((char*)filename[i],(char*)fn);
					i++;
				}
			}
			if(i>MAXDR)
			{
				for(j=0;j<MAXDR;j++)
				Show_Str(60,32+42*j,800,42,(u8*)filename[j],32,0);
			}
			else
			{
				for(j=0;j<i;j++)
				Show_Str(60,32+42*j,800,42,(u8*)filename[j],32,0);
			}
			SPeech(filename[0]);
		}
		f_closedir(dir);
		myfree(SRAMIN,finfo->lfname);
		myfree(SRAMIN,dir);
		myfree(SRAMIN,finfo);
		myfree(SRAMIN,pathp);
		dir=NULL;
		fn=NULL;
		finfo=NULL;
		pathp=NULL;
		curplace=0;
		highlight(mouse);
	}
	else if(demo==0)
	{
		pathtxt=mymalloc(SRAMIN,511);
		pathtxt[0]=0;
		mymemset(pathtxt,0,511);
		strcat((char*)pathtxt,(char*)path); 
		ret=f_open(&fil1,(char*)pathtxt,FA_READ);
		if(ret==FR_OK)
			f_lseek(&fil1,0);
		P1=0;
		P2=0;
		GetNextTwentyBits();
		LCD_Clear(WHITE);
		play();
	}
	return i;
}

u8 k2_event()
{
	u8 res=0;
	DIR*dir=0;
	FILINFO*finfo=0;
	u8*fn=0;
  u8*pathp=0;
	char idx[3]="";
	char bk[10]="书签";
	char*p=0;
	char*q=0;
	int i=0;
	int l=0;//显示行数
	int j;//文件名数组的起始和终止位置
	int k=0;//父目录标志
	u8 fnt[100]={""};
	u8 bkname[100]={""};
	u32 cnt1;//创建书签的次数
  u16 cnt2;//已有书签的个数
  u32 cnt3;//要写入文本地址的长度
	int index;//要新建的书签编号
	char processedname[50]="";//文件名不带扩展名
	char extension[3]="";
	memset(processedname,0,50);
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
	memset(bkname,0,100);//文档所属的名称
	memset(path_c,0,10*MAXSIZE);
	memset(buffer,0,20*MAXSIZE);//要写入地址的路径
	if(demo==0)
	{
		f_close(&fil1);
		myfree(SRAMIN,pathtxt);
		pathtxt=NULL;
		strcpy((char*)buffer,(const char*)path);
		cnt3=strlen((const char*)buffer);
		cnt2=scan_Bookmark("0:",-1);//已有书签的个数
//		printf("已有书签数目是%d\r\n",cnt2);
			if(cnt2==MAXBK)
		{
			strcpy(path_c,"书签10 ");
			scan_Bookmark("0:",cnt2);
			if(*nameReplaced!=NULL)
			{
//				printf("要删除的书签：%s\r\n",nameReplaced);
				res=f_unlink((char*)nameReplaced);
//				printf("删除结果：%d\r\n",res);
			}
			Rename_Bookmark ("0:");
		}
		else if(cnt2>=0&&cnt2<=MAXBK-1)
		{
			sprintf(idx, "%d", cnt2+1);
			strcat(bk, idx);
			strcat(bk," ");
			strcat(path_c, bk);
		}
//		printf("path_c是%s\r\n",path_c);
		q=strrchr((const char*)pathp,'/');
		strcpy((char*)bkname,q?q+1:pathp);//把数字和'/'去了
//		printf("bkname是%s\r\n",bkname);
		findExt((char*)bkname, processedname, extension);
		strcat(path_c,processedname);
		strcat(path_c,ext);//把书签文件换成.c扩展名
//		printf("要创建的书签名称是%s\r\n",path_c);
		res=create_New((const u8*)path_c,buffer,cnt3);
//		printf("创建书签结果%d\r\n",res);
		if(res==FR_OK)
			times_Write("0:/nums.h");
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
	if(!strcmp(fnt,pathp))
		k=0;
	memset(path,0,200);
	strcpy((char*)path,(char*)pathp);
	res=f_opendir(dir,(const TCHAR*)pathp);//打开修改过的路径
	if(res==0)
	{
	  while(1)
		{
		  res=f_readdir(dir,finfo);
		  fn=(u8*)(*finfo->lfname?finfo->lfname:finfo->fname);		
		  if(!finfo->fname[0]||res!=FR_OK) break;
			res=f_typetell(fn);
			if(finfo->fattrib==AM_DIR||(res&0XFF)==0X30)
			{
				if((res&0XFF)==0X30)
				{
					memset(processedname,0,50);
					findExt((char*)fn, processedname, extension);
					strcpy((char*)filename[i],processedname);
				}
				else
				strcpy((char*)filename[i],(char*)fn);
				if(!strcmp(fnt,fn))
					k=i;
				
				i++;
			}
		}
		if(i>MAXDR)
		{
			for(j=(k/MAXDR)*MAXDR;j<(k/MAXDR)*MAXDR+MAXDR;j++,l++)
			Show_Str(60,32+42*l,800,42,(u8*)filename[j],32,0);
		}
		else
		{
			for(j=0;j<i;j++)
			Show_Str(60,32+42*j,800,42,(u8*)filename[j],32,0);
		}
		SPeech(filename[k]);
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
			Show_Str(60,32+42*l,800,42,(u8*)filename[j],32,0);
		}
		else if(curplace%MAXDR==0&&n<=(curplace/MAXDR)*MAXDR+MAXDR)
		{
			LCD_Clear(WHITE);
			for(j=(curplace/MAXDR)*MAXDR;j<n;j++,l++)
			Show_Str(60,32+42*l,800,42,(u8*)filename[j],32,0);
		}	
	}
	curplace2=curplace%MAXDR;
	mouse=curplace2;
	highlight(mouse);
	SPeech(filename[curplace]);
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
			Show_Str(60,32+42*l,800,42,(u8*)filename[j],32,0);
		}
		else if((curplace+1)%MAXDR==0&&(curplace+1)!=0)
		{
			LCD_Clear(WHITE);
			for(j=(curplace/MAXDR)*MAXDR;j<(curplace/MAXDR)*MAXDR+MAXDR;j++,l++)
			Show_Str(60,32+42*l,800,42,(u8*)filename[j],32,0);
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
	SPeech(filename[curplace]);
}
void k4_event(int flag)
{
	DWORD temp=f_tell(&fil1);
	TCHAR buf[21];
	if(flag==0)
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
	}
	else if(flag==1)
	{
//		printf("按下翻键前的文件指针位置=%ld\r\n",temp);
		if(f_tell(&fil1)==f_size(&fil1))
			f_lseek(&fil1,0);
		P1=f_tell(&fil1);
		
		P2=0;
		LCD_Clear(WHITE);
		strcpy(buf,f_gets(buffer1,21,&fil1));
//		f_gets((char*)buffer1,21,&fil1);
		temp=f_tell(&fil1);
//		printf("按下翻键后的文件指针位置（取了）=%ld\r\n",temp);
//		printf("buf:%s\r\n",buf);
//		printf("buffer1:%s\r\n",buffer1);
		ASCIItoBraille(buffer1, buffer2);
//		printf("buffer2:%s\r\n",buffer2);
	}
	play(flag);
}
int GetNextTwentyBits()
{
	DWORD temp=0;
	TCHAR buf[2]="";
	char buff_Totranslate[BUFFER1_TOREAD+1]="";
	int j=0;
	char *q=NULL;
	memset(buf,'\0',sizeof(buf));
	memset(buffer1,'\0',sizeof(buffer1));
	memset(buff_Totranslate,'\0',sizeof(buff_Totranslate));
	while(j!=BUFFER1_TOREAD+1)
	{	
		temp=f_tell(&fil1);
		if(temp==f_size(&fil1))
			break;
		f_gets(buf,2,&fil1);
		j++;
		if(buf[0]!=0x0A)//对于回车而言Windows系统下CRLF同时出现，LF=0XA0(10),CR=0X0D(13),'\r'CR舍去 '\n'LF保留 MAC只有'\r'
		{
//			printf("取到的字符为:%c\r\n",buf[0]);
			strcat(buffer1,buf);	
		}
	}
//	printf("取到的字符数目j:%d\r\n",j);
	if(j<21)
	{
		num_Acquired=strlen(buffer1);
		ASCIItoBraille(buffer1, buffer2);
//		printf("取到的字符数目j<21的情况下num_Acquired=:%d,buffer1=:%s,buffer2=:%s\r\n",j,buffer1,buffer2);
	}
	else
	{
		if(buffer1[19]!=' '&&buffer1[20]!=' ')
		{
			q = strrchr(buffer1, ' ');
			strncpy(buff_Totranslate, buffer1, q?(q-buffer1+1) * sizeof(char):strlen(buffer1)-1);//将包括空格的内容保存到buff_Totranslate
		}
		else
		strncpy(buff_Totranslate, buffer1,20);
		num_Acquired=strlen(buff_Totranslate);
		f_lseek(&fil1,f_tell(&fil1)-(BUFFER1_TOREAD+1-num_Acquired));
		ASCIItoBraille(buff_Totranslate, buffer2);
//		printf("取到的字符数目j=21的情况下num_Acquired=:%d,buff_Totranslate=:%s,buffer2=:%s\r\n",num_Acquired,buff_Totranslate,buffer2);
	}
	q=NULL;
	return j;
}
int GetLastTwentyBits()
{
	DWORD temp=0;
	TCHAR buf[2]="";
	char buff_Totranslate[BUFFER1_TOREAD+1]="";
	int j=0;
	char *q=NULL;
	memset(buf,'\0',sizeof(buf));
	memset(buffer1,'\0',sizeof(buffer1));
	memset(buff_Totranslate,'\0',sizeof(buff_Totranslate));
	while(j!=BUFFER1_TOREAD+1)
	{	
		f_gets(buf,2,&fil1);
		j++;
		if(buf[0]!=0x0A)//对于回车而言Windows系统下CRLF同时出现，LF=0XA0(10),CR=0X0D(13),'\r'CR舍去 '\n'LF保留 MAC只有'\r'
		{
//			printf("取到的字符为:%c\r\n",buf[0]);
			strcat(buffer1,buf);	
		}
	}
	q = strchr(buffer1, ' ');
	if (buffer1[0] != ' ' && buffer1[1] != ' ')
	{
		if (q)
			strcpy(buff_Totranslate, q);
		else
			strcpy(buff_Totranslate, buffer1 + 1);//将包括空格的内容保存到buff_Totranslate
	}
	else
		strcpy(buff_Totranslate, buffer1 + 1);
	num_Acquired=strlen(buff_Totranslate);
	ASCIItoBraille(buff_Totranslate, buffer2);
	q=NULL;
//	printf("num_Acquired=:%d,buff_Totranslate=:%s,buffer2=:%s\r\n",num_Acquired,buff_Totranslate,buffer2);
	return j;
}
void NextPage()
{
//	printf("按下翻键前的文件指针位置:%ld\r\n",f_tell(&fil1));
	if(f_tell(&fil1)==f_size(&fil1))
		f_lseek(&fil1,0);
	P1=f_tell(&fil1);
	P2=0;
//	printf("当前文件指针P1的位置在:%ld\r\n",P1);
	GetNextTwentyBits();
	LCD_Clear(WHITE);
	play();
}
void LastPage()
{
	TCHAR temp[2]="";
	int i=0;
	int j=0;
	j=f_tell(&fil1)-num_Acquired;//从第二页到第一页获取的内容
	if(f_size(&fil1)<=BUFFER1_TOREAD)//文本长度小于等于20个字节
	{
//		printf("上翻情况1，按下前前的文件指针位置:%ld,",f_tell(&fil1));
		f_lseek(&fil1,0);
		P1=f_tell(&fil1);
//		printf("当前文件指针P1的位置在:%ld,",P1);
		GetNextTwentyBits();
//		printf("上翻情况1，按下前后的文件指针位置:%ld\r\n",f_tell(&fil1));
	}
	else //文本长度大于20个字节
	{
		if(f_tell(&fil1)-num_Acquired==0)//当前位置是第一页末
		{
//			printf("上翻情况2，按下前前的文件指针位置:%ld,",f_tell(&fil1));
			f_lseek(&fil1,f_size(&fil1)-21);
			GetLastTwentyBits();
//			printf("上翻情况2，按下前后的文件指针位置:%ld,",f_tell(&fil1));
			P1=f_tell(&fil1)-num_Acquired;
//			printf("当前文件指针P1的位置在:%ld\r\n",P1);
		}
		else if(f_tell(&fil1)-num_Acquired<=20)//当前位置是第二页末
		{
//			printf("上翻情况3，按下前前的文件指针位置:%ld,",f_tell(&fil1));
			f_lseek(&fil1,0);
			P1=f_tell(&fil1);
////			printf("当前文件指针P1的位置在:%ld\r\n",P1);
			memset(buffer1,'\0',sizeof(buffer1));
			for(i=0;i<j;i++)
			{	
				f_gets(temp,2,&fil1);
				if(temp[0]!=0x0A)//对于回车而言Windows系统下CRLF同时出现，LF=0XA0(10),CR=0X0D(13),'\r'CR舍去 '\n'LF保留 MAC只有'\r'
				{
//					printf("取到的字符为:%c\r\n",temp[0]);
					strcat(buffer1,temp);	
				}
			}
			num_Acquired=j;
			ASCIItoBraille(buffer1, buffer2);
//			printf("num_Acquired=:%d,buffer1=:%s,buffer2=:%s\r\n",num_Acquired,buffer1,buffer2);
//			printf("上翻情况3，按下前后的文件指针位置:%ld\r\n",f_tell(&fil1));
		}
		else //其他情况
		{
//			printf("上翻情况4，按下前前的文件指针位置:%ld,",f_tell(&fil1));
			f_lseek(&fil1,f_tell(&fil1)-num_Acquired-21);
			GetLastTwentyBits();
//			printf("上翻情况4，按下前后的文件指针位置:%ld,",f_tell(&fil1));
			P1=f_tell(&fil1)-num_Acquired;
//			printf("当前文件指针P1的位置在:%ld\r\n",P1);
		}		
	}
	P2=0;
	LCD_Clear(WHITE);
	play();
}
void k5_event(int flag)
{ 
	FRESULT res;
	TCHAR buf[21];
	DWORD temp=f_tell(&fil1);
	memset(buf,'\0',sizeof(buf));
	if(flag==0)
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
	}
	else if(flag==1)
	{
//		printf("按上翻键前的文件指针位置=%ld\r\n",temp);
		if(f_tell(&fil1)==f_size(&fil1))
			{
				if(f_size(&fil1)%20==0)
				{
					res=f_lseek(&fil1,f_size(&fil1)-40);
//					printf("情况1,res=%d\r\n",res);
				}
							
				else
				{
					res=f_lseek(&fil1,f_size(&fil1)-f_size(&fil1)%20-20);
//					printf("情况2,res=%d\r\n",res);
				}
							
			}			 
	  else if(f_tell(&fil1)==20)
			{
				if(f_size(&fil1)%20==0)
				{
					res=f_lseek(&fil1,f_size(&fil1)-20);	
//					printf("情况3,res=%d\r\n",res);
				}
						
				else
				{
					res=f_lseek(&fil1,f_size(&fil1)-f_size(&fil1)%20);	
//					printf("情况4,res=%d\r\n",res);
				}
					
			}		
		else		
		{
			res=f_lseek(&fil1,f_tell(&fil1)-40);	
//			printf("情况5,res=%d\r\n",res);
		}			
		P1=f_tell(&fil1);
//		printf("按上翻键后的文件指针的位置(还没取)=%ld\r\n",P1);
		P2=0;
		LCD_Clear(WHITE);
		strcpy(buf,f_gets(buffer1,21,&fil1));
//	f_gets(buffer1,21,&fil1);	
//		printf("buf:%s\r\n",buf);
//		printf("buffer1:%s\r\n",buffer1);
		ASCIItoBraille(buffer1, buffer2);
//		printf("buffer2:%s\r\n",buffer2);
	}
	play(flag);
}
void highlight(const u8 line)
{
	LCD_Fill(35,45,45,800,WHITE);//清除原先位置，白色填充	
	LCD_Fill(35,45+42*line,45,55+42*line,BLUE);
}

void dis_txt(int flag)
 {
	TCHAR buf[21];
	DWORD temp;
	memset(buf,'\0',sizeof(buf));
	 if(flag==0)
	 {
		 f_lseek(&fil1,0);
		 f_lseek(&fil2,0);
		 f_gets(buffer2,121,&fil2);
		 f_gets(buffer1,38,&fil1);
	 }
	 else if(flag==1)
	 {
		 
		 f_lseek(&fil1,0);
		 temp=f_tell(&fil1);
//		 printf("按确认键前的文件指针位置=%ld\r\n",temp);
		 strcpy(buf,f_gets(buffer1,21,&fil1));
		 temp=f_tell(&fil1);
//		 printf("按确认键后的文件指针位置=%ld\r\n",temp);
//		 printf("buf:%s\r\n",buf);
//		 printf("buffer1:%s\r\n",buffer1);
		 //f_gets(buffer1,21,&fil1);
		 ASCIItoBraille(buffer1, buffer2);
//		 printf("buffer2:%s\r\n",buffer2);
	 }
	 play(flag);
 }


void play()
{
	int m;
	int l;
	char btmp[20][7]={""};
	LCD_Clear(WHITE);
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
u16 scan_Bookmark (const u8* path,int num)//获取书签的数目并且将要替换的书签名赋值给nameReplaced
{
	u16 cnt=0;
	FRESULT res;
	DIR *dir;
	FILINFO *fno;
	u8*fn;
	char buf[10];//存储fn
	memset(nameReplaced,0,100);
//	memset(nameReplaced,0,50);
	dir=(DIR*)mymalloc(SRAMIN,sizeof(DIR));
	fno =(FILINFO*)mymalloc(SRAMIN,sizeof(FILINFO));
	fno->lfsize=_MAX_LFN*2+1;          
	fno->lfname= mymalloc(SRAMIN,fno->lfsize); 
	res = f_opendir(dir, (const TCHAR*)path);
	if(res==FR_OK&&fno->lfname!=NULL)
		{
			while(1)//查询总的有效文件数
			{
				res=f_readdir(dir,fno);       		//读取目录下的一个文件
				fn=(u8*)(*fno->lfname?fno->lfname:fno->fname);				
				if(res!=FR_OK||fno->fname[0]==0)
					break;	//错误了/到末尾了,退出		   
				res=f_typetell(fn);	
				if((res&0XFF)==0X31)//取高四位,看看是不是.C书签文件
					{
						cnt++;//有效文件数增加1
						if(num==MAXBK)
						{
							memset(buf,'\0',sizeof(buf));
							strncpy(buf,(const char*)fn,6);
							if(strstr(buf,"1")!=NULL&&strstr(buf,"0")==NULL)
							{
								strcpy(nameReplaced,"0:/");
								strcat(nameReplaced,fn);
//								printf("要删除的书签名是%s\r\n",nameReplaced);
							}	
						}						
					}								
			 }  
		} 
	f_closedir(dir);
	myfree(SRAMIN,fno->lfname);
	fn=NULL;
	myfree(SRAMIN,dir);
	dir=NULL;
	myfree(SRAMIN,fno);
	fno=NULL;
	return cnt;
}
void findExt( char* file_name, char* name, char* ext)
{
	int flag = 0;
	char* end;
	char* ptr = file_name;
	while (*ptr != '\0')
	{
		ptr++;//移到文件名末尾
		if (*ptr == '.')
			flag = 1;
	}
	end = ptr;//存一下
	if(flag==1)
	{
		while (*ptr != '.')
			ptr--;//从后往前移动到.的位置
		memcpy(name, file_name, (ptr - file_name) * sizeof(char));
		memcpy(ext, ptr + 1, (end - ptr) * sizeof(char));
	}
	else
	{
		strcpy(name, file_name);
		ext = NULL;
	}
}
u32 times_Read(const u8*path)//读 创建次数.txt(nums.txt)获取创建书签的次数
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
FRESULT times_Write(const u8*path)//写 创建次数.h(nums.h)，增加创建书签的次数，写入成功后返回值为0
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
FRESULT times_Init(const u8*path)//初始化 创建次数.txt(nums.txt)，初始值为0，写入成功后返回值为0
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
void Int_To_Str(int x, char* Str)//整数转成字符串
{
	int t;
	char* Ptr, Buf[5];
	int i = 0;
	Ptr = Str;
	if (x < 10)  // 当整数小于10，转换为0x格式 
	{
		*Ptr++ = x + 0x30;
	}
	else
	{
		while (x > 0)
		{
			t = x % 10;
			x = x / 10;
			Buf[i++] = t + 0x30; // 通过计算把数字编成ASCII码形式  
		}
		i--;
		for (; i >= 0; i--)   // 将得到的字符串倒序  
		{
			*(Ptr++) = Buf[i];
		}
	}
	*Ptr = '\0';
}
FRESULT create_New(const u8*path,const u8*path2,UINT nums)//path是文件的路径，path2是写入的字符数组,先写text再写data最后写文本存在的路径
{
	DIR *dir;
	FIL *fil;
	FRESULT res;
	dir=(DIR*)mymalloc(SRAMIN,sizeof(DIR));
	fil=(FIL*)mymalloc(SRAMIN,sizeof(FIL));
	res=f_opendir(dir,"0:");
	if(!res)
	{
		res=f_open(fil,(const TCHAR*)path,FA_READ|FA_WRITE|FA_CREATE_ALWAYS);//可以新建写入，也可以已有文件覆盖写入
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
/*cnt1是创建书签的次数，cnt2是已有书签个数 如果cnt2小于10个，把cnt2+1然后转换成字符串。
如果cnt2=10，此时若cnt1+1能整除10，就替换第10个书签。否则就替代第（cnt1+1）%10个书签
原理：如果有10个书签，cnt1必然为10.创建第11个书签相当于替换第（cnt1+1）%10个书签，如果cnt1+1为整除10的数，例如cnt1=19.创造次数为20
则替换的是第10个书签*/
{
	char idx[MAXSIZE]="";
	char bk[3*MAXSIZE]="书签";
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
int display_Bookmark()//遍历出所有的.c文件并且按照书签1~10的顺序排序
{
	FRESULT res;
	int i=0;
	int line=0;
	int num=0;//书签个数
	DIR *bkdir;
	FILINFO *bkfileinfo;//文件信息
	u8 *fn;   			//长文件名
	char processedname[100]="";//文件名不带扩展名
	char extension[3]="";
	memset(processedname,0,100);
	memset(&bookmarkname[0][0],0,sizeof(char)*10*100);
	LCD_Clear(WHITE);
	bkdir=(DIR*)mymalloc(SRAMIN,sizeof(DIR));
  bkfileinfo =(FILINFO*)mymalloc(SRAMIN,sizeof(FILINFO));
	bkfileinfo->lfsize=_MAX_LFN*2+1;          
	bkfileinfo->lfname= mymalloc(SRAMIN,bkfileinfo->lfsize);
	demo=2;
	bkplace=0;//记录读到书签所处目录的位置
	highlight(0);
	memset(path,0,200);
	strcpy((char*)path,"0:");
//	num=scan_Bookmark("0:");
//	if(num==0)
//	{
//		LCD_Clear(WHITE);
//		Show_Str(60,242,500,42,"没有书签文件！",32,0);
//		SPeech("没有书签文件");
//	}
	res=f_opendir(bkdir,(const char*)path);
	if(res==FR_OK)
	{
		while(1)//全部查询一遍
		{
			res=f_readdir(bkdir,bkfileinfo);//读取目录下的一个文件
			if(res!=FR_OK||bkfileinfo->fname[0]==0)break;	//错误了/到末尾了,退出		  
			fn=(u8*)(*bkfileinfo->lfname?bkfileinfo->lfname:bkfileinfo->fname);			 
			res=f_typetell(fn);	
			if((res&0XFF)==0X31)//是否为书签文件	
			{
				findExt( (char*)fn, processedname, extension);
				strcpy((u8*)bookmarkname[line],processedname);
				line++;
				memset(processedname,0,100);
			}	    
		}
		selectSort(bookmarkname, line); 
		for(i=0;i<line;i++)
		Show_Str(60,32+42*i,800,42,(u8*)bookmarkname[i],32,0);
		memset(bkmidname,'\0',sizeof(bkmidname));
		strcpy(bkmidname,bookmarkname[0]);
		SPeech(bkmidname);
	}
	num=line;
	f_closedir(bkdir);
	myfree(SRAMIN,bkfileinfo->lfname);
	myfree(SRAMIN,bkdir);
	myfree(SRAMIN,bkfileinfo);
	return num;
}
FRESULT bookmark_Read(const u8*path,u8*buf_Read)//读书签内容，分为text的offset，data的offset，和书签记录的地址
{
	DIR *dir;
	FIL *fil;
	FRESULT res;
	dir=(DIR*)mymalloc(SRAMIN,sizeof(DIR));
	fil=(FIL*)mymalloc(SRAMIN,sizeof(FIL));
	memset(buf_Read,0,20*MAXSIZE);
	P3=0;
	P4=0;
	res=f_opendir(dir,"0:");
	if(!res)
	{
		res=f_open(fil,(const TCHAR*)path,FA_READ);//可以新建写入，也可以已有文件覆盖写入
		res = f_read(fil,&P3,sizeof(P3),&br);
		res = f_read(fil,&P4,sizeof(P4),&br);
//		printf("第一个数字%d\r\n",(int)P3);
//		printf("第二个数字%d\r\n",(int)P4);
		for(;;)
		{
			res = f_read(fil,buf_Read,20*MAXSIZE,&br);
//			printf("%s\r\n",buf_Read);
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
/*i从0开始，和数组元素下标的起始位置相同，找到下标为index的元素，打开并且调用打开书签的函数，
将路径存到path中，方便打开path中的text.txt和data.txt*/
{
	FRESULT res=0;
	DIR*dir=0;
	u8*fn=0;
	u8*pathp=0;
	int i=0;
	u8 ret=0;
  LCD_Clear(WHITE);
	dir=(DIR*)mymalloc(SRAMIN,sizeof(DIR));
	pathp=mymalloc(SRAMIN,200);
  pathp[0]=0;
	strcat((char*)pathp,"0:");
	memset(path,0,200);
	i=index;
	strcat((char*)pathp,"/");
	strcat((char*)pathp,(char*)bookmarkname[i]);
	strcat((char*)pathp,".c");
	i=0;
	res=bookmark_Read(pathp,buf_Read);
	if(res==0)
	strcpy((char*)path,(char*)buf_Read);
	myfree(SRAMIN,pathp);
	pathtxt=mymalloc(SRAMIN,511);
	mymemset(pathtxt,0,511);
	strcpy((char*)pathtxt,(char*)path);
	if(demo==2)
	{
		demo=0;
		ret=f_open(&fil1,(char*)pathtxt,FA_READ);
		if(ret==FR_OK)
		{
			f_lseek(&fil1,P3);
		  GetNextTwentyBits();
			LCD_Clear(WHITE);
			play();
			P3=0;
			P4=0;
		}
	}
}
void move_Bookmarkcursor_Next(u16 n)//选择下一个书签
{
	u16 cursor;
	SPeech("[n0]");
	bkplace=(bkplace+1)%n;
	cursor=bkplace;
	highlight(cursor);
	memset(bkmidname,'\0',sizeof(bkmidname));
	delay_ms(1);
	strcpy(bkmidname,bookmarkname[bkplace]);
	SPeech(bkmidname);
}
void move_Bookmarkcursor_Last(u16 n)//选择上一个书签
{
	u16 cursor;
	SPeech("[n0]");
	if((bkplace-1)<0)
		bkplace=n-1;
	else
	bkplace=(bkplace-1)%n;
	cursor=bkplace;
	highlight(cursor);
	memset(bkmidname,'\0',sizeof(bkmidname));
	delay_ms(1);
	strcpy(bkmidname,bookmarkname[bkplace]);
	SPeech(bkmidname);
}
void selectSort(char(*pt)[100], int n) 
/*对书签1~10排序，书签名格式：书签X XXXXX,形参pt为指向二维字符数组的指针。书签1 XXX比书签10 XXX小，因为空格的ASCII码是20,0的ASCII码是30.
但汉字的ASCII比数字和符号的ASCII大。如果有书签10 XXX，最终结果为书签1 XXX,书签10 XXX，书签2 XXX.....*/
{
	int i, j, k;
	char tmp[100];  //临时字符数组
	for (i = 0; i < n - 1; i++)  //遍历所有未排序的字符串的趟数
	{
		k = i;  //变量k存放当前最小字符串的下标
		for (j = i + 1; j < n; j++)               //遍历下标从(i+1)~(n-1)的所有字符串
			if (strcmp(pt[k], pt[j]) < 0)  //字符串进行两两大小比较,如果<0,则执行if语句体
				k = j;                     //将当前最小的字符串的数组下标赋值给变量k
		if (k != i)                       //如果k不等于i,则执行if语句体
		{   //两个字符串进行交换操作
			strcpy(tmp, pt[k]);
			strcpy(pt[k], pt[i]);
			strcpy(pt[i], tmp);
		}
	}
	if (n == 10)//如果书签数目是10个，就进行如下交换：先交换10和1的顺序，然后依次交换1后面相邻的两个序号，把10交换到最后一位
	{
		/*strcpy(tmp, pt[0]);
		strcpy(pt[0], pt[1]);
		strcpy(pt[1], tmp);*/
		for (i = 9; i > 1; i--)
		{
			strcpy(tmp, pt[i-2]);
			strcpy(pt[i-2], pt[i - 1]);
			strcpy(pt[i - 1], tmp);
		}
	}
}
void ASCIItoBraille(char* toTranslate, char* translated)
{
	char temp[7] = "";
	memset(buffer2,'\0',sizeof(buffer2));
	while (*toTranslate != NULL)
	{
		if(*toTranslate==0x13&&*(toTranslate+1)==0x10)
		{
			strcpy(temp, StrtoBraille(*toTranslate));
			strcat(translated, temp);
			toTranslate+=2;
		}
		else
		{
			strcpy(temp, StrtoBraille(*toTranslate));
			strcat(translated, temp);
			toTranslate++;
		}
//		printf("ascii:%c\r\n",*toTranslate);
		
//		printf("temp:%s\r\n", temp);
		
//		printf("translated:%s\r\n", translated);
	}
}
u32 update_percent(u16 x,u16 y,u8 size,u32 fsize,u32 pos)
{
	float prog;
	int t=0;
	static int speaktime=0;
	char per[]="%";
//	char reminder[10]="";
	speaktime++;
	prog=(float)pos/fsize;
	prog*=100;
	if(t!=prog)
	{
		LCD_ShowString(x+3*size/2,y,240,320,size,"%");		
		t=prog;
		if(t>100)
			t=100;
		if(speaktime%500==0)
		{
//			memset(reminder,'\0',sizeof(reminder));
//			sprintf(reminder, "%d", t);
//			strcat(reminder,per);
//			printf("进度：%s\r\n",reminder);
			SPeech("翻译中");
			
			
		}
		LCD_ShowNum(x,y,t,3,size);//显示数值
	}
	return 0;					    
} 
void bookmarkRename(char *str)//把书签X变成书签X-1 例如书签10 XXX.c->书签9 XXX.c
{
	char* p = str;
	char temp[3] = "";
	char str1[100] = "";
	char str2[100] = "";
	const char str3[] = "书签";
	char* q = NULL;
	int i = 0, j = -1;
	memset(str2, '\0', sizeof(str2) / sizeof(str2[0]));
	q = strchr(p, ' ');
	strcpy(str2, q);//书签名称
	q=NULL;
	strncpy(temp,p + 4, 2);
	NoBlankSpace(temp);
	j = atoi(temp);
//	printf("要替换的数字是%d\r\n",j);
	sprintf(temp, "%d", j - 1);
	memset(str1, '\0', sizeof(str1) / sizeof(str1[0]));
	strcat(str1, str3);
	strcat(str1, temp);
	strcat(str1, str2);
	strncpy(p, str1, strlen(str1));
	*(p+ strlen(str1)) = '\0';
	p=NULL;
}
void NoBlankSpace(char* pStr)//删去字符串中的空格
{
	char* pTmp = pStr;
	while (*pStr != '\0')
	{
		if (*pStr != ' ')
		{
			*pTmp = *pStr;
			pTmp++;
		}
		++pStr;
	}
	*pTmp = '\0';
}		
void selectSort_ascending(char(*pt)[100], int n)
/*对书签1~10由小到大排序，书签名格式：书签X XXXXX,形参pt为指向二维字符数组的指针。*/
{
	int i, j, k,z;
	char tmp[100];  //临时字符数组
	char num[3]="";
	char* p = NULL;
	int(*temp)[1] = (int(*)[1])mymalloc(SRAMIN,sizeof(int) * n);
	for (i = 0; i < n - 1; i++)  //遍历所有未排序的字符串的趟数
	{
		for (z = 0; z < n; z++)
		{
			p = pt[z];
			memcpy(num, p + 4, 2);
			NoBlankSpace(num);
			j = atoi(num);
			*temp[z] = j;
		}
		k = i;  //变量k存放当前最小字符串的下标
		for (j = i + 1; j < n; j++)               //遍历下标从(i+1)~(n-1)的所有字符串
			if (*temp[k] > * temp[j])  //字符串进行两两大小比较,如果>0,则执行if语句体
				k = j;                     //将当前最小的字符串的数组下标赋值给变量k
		if (k != i)                       //如果k不等于i,则执行if语句体
		{   //两个字符串进行交换操作
			strcpy(tmp, pt[k]);
			strcpy(pt[k], pt[i]);
			strcpy(pt[i], tmp);
		}
	}
	myfree(SRAMIN,temp);
	p = NULL;
}	
void Rename_Bookmark (const u8* path)//将书签文件的标号在磁盘中-1 例如书签10 XXX.c->书签9 XXX.c
{
	FRESULT res;
	u8 type;
	DIR *dir;
	FILINFO *fno;
	u8*fn;
	int i=0;
	int cnt=0;
//	char oldname[9][100]={{""}};
//  char newname[9][100]={{""}};
	char (*oldname)[100]=(char(*)[100])mymalloc(SRAMIN,sizeof(char)*9*100);
	char (*newname)[100]=(char(*)[100])mymalloc(SRAMIN,sizeof(char)*9*100);
	dir=(DIR*)mymalloc(SRAMIN,sizeof(DIR));
	fno =(FILINFO*)mymalloc(SRAMIN,sizeof(FILINFO));
	fno->lfsize=_MAX_LFN*2+1;          
	fno->lfname= mymalloc(SRAMIN,fno->lfsize); 
	res = f_opendir(dir, (const TCHAR*)path);
//	printf("打开目录结果：%d\r\n",res);
	if(res==FR_OK&&fno->lfname!=NULL)
		{
			while(1)//查询总的有效文件数
			{
				res=f_readdir(dir,fno);       		//读取目录下的一个文件
//				printf("读取目录结果:%d\r\n",res);
				fn=(u8*)(*fno->lfname?fno->lfname:fno->fname);				
				if(res!=FR_OK||fno->fname[0]==0)
					break;	//错误了/到末尾了,退出		   
				type=f_typetell(fn);	
//				printf("类型是%d\r\n",type);
				if((type&0XFF)==0X31)//取高四位,看看是不是.C书签文件
					{
							strcpy(oldname[i],"0:/");
							strcpy(oldname[i],fn);
//							printf("第%d个要改变的书签名是%s",i+1,oldname[i]);
							bookmarkRename((char*)fn);
							strcpy(newname[i],"0:/");
							strcpy(newname[i],fn);
//							printf(",第%d个新的书签名是%s\r\n",i+1,newname[i]);
							i++;
//						printf("数目i:%d\r\n",i);
					}						
			}	
				cnt=i;
		}
	selectSort_ascending(oldname, 9);
	selectSort_ascending(newname, 9);
  for(i=0;i<cnt;i++)
		{
			res=f_rename(oldname[i],newname[i]);
//			delay_ms(10);
//			if(!res)
//				printf("第%d个修改成功\r\n",i+1);
		}	
	f_closedir(dir);
	myfree(SRAMIN,fno->lfname);
	fn=NULL;
	myfree(SRAMIN,dir);
	dir=NULL;
	myfree(SRAMIN,fno);
	fno=NULL;
	myfree(SRAMIN,oldname);
	oldname=NULL;
	myfree(SRAMIN,newname);
	newname=NULL;
}
	