#include "readwrite.h"
#include "string.h"
#include "exfuns.h"
#include "usart.h"
extern u32 length;
extern u8 readbuf[1000];
extern u8 path[512];
extern u8 demo;
extern FIL fil;
FRESULT times_Read(u8* path)//读 创建次数.txt(nums.txt)获取创建书签的次数
{
	DIR *dir;
	FIL *fil;
	FRESULT res;
	
	dir=(DIR*)mymalloc(SRAMIN,sizeof(DIR));
	fil=(FIL*)mymalloc(SRAMIN,sizeof(FIL));
	res=f_opendir(dir,(const TCHAR*)"3:");
	printf("key1 f_opendir res:%d\r\n",res);
	res=f_open(fil,(const TCHAR*)path,FA_READ);
	printf("key1 f_open res:%d\r\n",res);
	if(!res)
	{
		while(!res)
		{
			res=f_read(fil,readbuf,1000,&br);
			printf("key1 f_read res:%d\r\n",res);
			if (res || br < 1000) 
//			f_gets((TCHAR*)readbuf,121,fil);
				break;
		}				
	}
	f_close(fil);
	f_closedir(dir);
	length=strlen(readbuf);
	myfree(SRAMIN,dir);
	myfree(SRAMIN,fil);
	dir=NULL;
	fil=NULL;
	return res;	
}
FRESULT times_Write(const u8*path)//写 创建次数.txt(nums.txt)，增加创建书签的次数，写入成功后返回值为0
{
	DIR *dir;
	FIL *fil;
	FRESULT res;
	const char buf[]="我";
	dir=(DIR*)mymalloc(SRAMIN,sizeof(DIR));
	fil=(FIL*)mymalloc(SRAMIN,sizeof(FIL));
	res=f_opendir(dir,(const TCHAR*)"3:");
	res=f_open(fil,(const TCHAR*)path,FA_READ|FA_WRITE);
	printf("open ok\r\n");
	f_lseek(fil,f_size(fil));
	printf("f_lseek ok\r\n");
	if(!res)
	{
		res=f_write(fil,buf,2,&bw);	
		printf("write ok\r\n");		
	}
	f_close(fil);
	printf("f_close ok\r\n");
	f_closedir(dir);
	printf("f_closedir ok\r\n");
	myfree(SRAMIN,fil);
	printf("free fil ok\r\n");
	myfree(SRAMIN,dir);
	printf("free dir ok\r\n");
	dir=NULL;
	fil=NULL;
	return res;	
}
FRESULT times_Init(const u8*path)//初始化 创建次数.txt(nums.txt)，初始值为0，写入成功后返回值为0
{
	DIR *dir;
	FIL *fil;
	FRESULT res;
	u8 buf[]="你我他123abc";
	dir=(DIR*)mymalloc(SRAMIN,sizeof(DIR));
	fil=(FIL*)mymalloc(SRAMIN,sizeof(FIL));
	res=f_opendir(dir,(const TCHAR*)"3:");
	if(!res)
	{
		res=f_open(fil,(const TCHAR*)path,FA_CREATE_NEW|FA_WRITE);
			if(!res)
			{
				do
				{
					res = f_write(fil,buf,strlen(buf),&bw);
					if(res)
						break;
				}
				while (bw <strlen(buf));
			}
	}
	f_close(fil);
	f_closedir(dir);
	myfree(SRAMIN,fil);
	myfree(SRAMIN,dir);
	dir=NULL;
	fil=NULL;
	return res;	
}

void Bytes_Get(u8 num)
{
	int cnt=0;
	f_gets((TCHAR*)readbuf,num,&fil);
	length=strlen(readbuf);
	for(cnt=0;cnt<length;cnt++)
		printf("第%d个字节:%x\r\n",cnt+1,readbuf[cnt]);
}

void Get_Nextpage(u8 num)
{
	 if(f_tell(&fil)==f_size(&fil))
        f_lseek(&fil,0);
    Bytes_Get(num);
}

u8 Scan_Directory(u8* path)
{
    u8 res=0;
    DIR*dir=0;
    FILINFO*finfo=0;
    u8*fn=0;
	u8*pathp=0;
	u8 filetype=0;
    int i=0;
    int cnt=0;
    dir=(DIR*)mymalloc(SRAMIN,sizeof(DIR));
    finfo =(FILINFO*)mymalloc(SRAMIN,sizeof(FILINFO));
	pathp=mymalloc(SRAMIN,512);
	mymemset(pathp,0,512);
	strcat((char*)pathp,(const char*)path);
    res=f_opendir(dir,(const TCHAR*)path);
	printf("Scan_Directory res:%d\r\n",res);
    if(res==0)
    {
        while(1)
        {
            res=f_readdir(dir,finfo);
            fn=(u8*)(finfo->fname);
            if(!finfo->fname[0]||res!=FR_OK) break;
			filetype=f_typetell(fn);
            if(finfo->fattrib==AM_DIR||(filetype&0XFF)==0X30)
            {
                while(*fn!='\0')
				{
					printf("第%d个文件夹的第%d个字节为:%x\r\n",cnt+1,i+1,*fn);
					i+=1;
					fn++;
				}
				cnt++;
				i=0;
            }
			
        }
    }
    f_closedir(dir);
    myfree(SRAMIN,dir);
    myfree(SRAMIN,finfo);
	myfree(SRAMIN,pathp);
	dir=NULL;
	fn=NULL;
	finfo=NULL;
	pathp=NULL;
    return cnt;
}


u8 Confirm_Buttom(u8 index)
{
	u8 res=0;
	DIR*dir=0;
	FILINFO*finfo=0;
	u8*fn=0;
	u8*pathp=0;
	u8*pathtxt=0;
	int i=0;
	int cnt=0;
	u8 ret=0;
	u8 filetype=0;
	dir=(DIR*)mymalloc(SRAMIN,sizeof(DIR));
	finfo =(FILINFO*)mymalloc(SRAMIN,sizeof(FILINFO));
	pathp=mymalloc(SRAMIN,512);
	mymemset(pathp,0,512);
	strcat((char*)pathp,(char*)path);
	memset(path,0,512);
	res=f_opendir(dir,(const TCHAR*)pathp);
	if(res==0)
	{
	  while(1)
		{
			res=f_readdir(dir,finfo);
			fn=(u8*)(finfo->fname);
            if(!finfo->fname[0]||res!=FR_OK) break;
			filetype=f_typetell(fn);
			if(finfo->fattrib==AM_DIR||(filetype&0XFF)==0X30)
			{
				if(cnt==index)
				{
					if((filetype&0XFF)==0X30)
						demo=0;
					else
						demo=1;
					break;
				}
				cnt++;
			}
		}
	}
	printf("demo=%d\r\n",demo);
	strcat((char*)pathp,"/");
	strcat((char*)pathp,(char*)fn);
	strcpy((char*)path,(char*)pathp);
	printf("path:%s\r\n",path);
	f_closedir(dir);
	cnt=0;
	if(demo==1)
	{
		res=f_opendir(dir,(const TCHAR*)pathp);
		if(res==0)
		{
			while(1)
			{
				res=f_readdir(dir,finfo);
				fn=(u8*)(finfo->fname);
				if(!finfo->fname[0]||res!=FR_OK) break;
				filetype=f_typetell(fn);
				if(finfo->fattrib==AM_DIR||(filetype&0XFF)==0X30)
				{
						while(*fn!='\0')
					{
						printf("第%d个文件夹的第%d个字节为:%x\r\n",cnt+1,i+1,*fn);
						i+=1;
						fn++;
					}
					cnt++;
					i=0;
				}
			}
			f_closedir(dir);
			myfree(SRAMIN,dir);
			myfree(SRAMIN,finfo);
			myfree(SRAMIN,pathp);
			dir=NULL;
			fn=NULL;
			finfo=NULL;
			pathp=NULL;
		}	
	}
	else if(demo==0)
	{
		pathtxt=mymalloc(SRAMIN,512);
		pathtxt[0]=0;
		mymemset(pathtxt,0,512);
		strcat((char*)pathtxt,(char*)path);
		printf("pathtxt:%s\r\n",pathtxt);
		ret=f_open(&fil,(char*)pathtxt,FA_READ);
		myfree(SRAMIN,pathtxt);
		pathtxt=NULL;
		if(ret==FR_OK)
			f_lseek(&fil,0);
		Bytes_Get(161);
	}
	return cnt;
}

u8 Get_Parentdirectory()
{
	u8 res=0;
	u8*pathp=0;
	char*p=0;
	int cnt=0;
	u8 fnt[100]="";
	pathp=mymalloc(SRAMIN,512);
	mymemset(pathp,0,512);
	strcat((char*)pathp,(char*)path);
	memset(fnt,0,100);
	if(demo==0)
	{
		f_close(&fil);
	}
	demo=1;	
	p=strrchr((const char*)pathp,'/');
	strcpy(fnt,p?p+1:pathp);
	if(p!=NULL)
		*p='\0';
	memset(path,0,512);
	strcpy((char*)path,(char*)pathp);
	cnt=Scan_Directory(pathp);
	return cnt;
}	
