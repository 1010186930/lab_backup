#include "readwrite.h"
#include "usart.h"
#include<string.h>
extern u32 filelength;
extern u8 readbuf[200];
FRESULT times_Read(const u8*path)//�� ��������.txt(nums.txt)��ȡ������ǩ�Ĵ���
{
	DIR *dir;
	FIL *fil;
	FRESULT res;
	memset(readbuf,'\0',sizeof(readbuf));
	dir=(DIR*)mymalloc(SRAMIN,sizeof(DIR));
	fil=(FIL*)mymalloc(SRAMIN,sizeof(FIL));
	res=f_opendir(dir,"0:");
	res=f_open(fil,(const TCHAR*)path,FA_READ);
	printf("f_open:%d\r\n",res);
	if(!res)
	{
		while(!res)
		{
			res=f_read(fil,readbuf,200,&br);
			if (res || br < 200) 
				break;
		}				
	}
	filelength=strlen(readbuf);
	f_close(fil);
	f_closedir(dir);
	myfree(SRAMIN,dir);
	myfree(SRAMIN,fil);
	dir=NULL;
	fil=NULL;
	return res;	
}
FRESULT times_Write(const u8*path)//д ��������.txt(nums.txt)�����Ӵ�����ǩ�Ĵ�����д��ɹ��󷵻�ֵΪ0
{
	DIR *dir;
	FIL *fil;
	FRESULT res;
	const char buf[]="��";
	dir=(DIR*)mymalloc(SRAMIN,sizeof(DIR));
	fil=(FIL*)mymalloc(SRAMIN,sizeof(FIL));
	res=f_opendir(dir,"3:");
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
FRESULT times_Init(const u8*path)//��ʼ�� ��������.txt(nums.txt)����ʼֵΪ0��д��ɹ��󷵻�ֵΪ0
{
	DIR *dir;
	FIL *fil;
	FRESULT res;
	u8 buf[]="������123abc";
	dir=(DIR*)mymalloc(SRAMIN,sizeof(DIR));
	fil=(FIL*)mymalloc(SRAMIN,sizeof(FIL));
	res=f_opendir(dir,"3:");
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
