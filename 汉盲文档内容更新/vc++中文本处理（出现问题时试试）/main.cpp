#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>

FILE *ft1 = NULL;
FILE *ft2 = NULL;
FILE *fd1 = NULL;
FILE *fd2 = NULL;

main()
{
  ft1=fopen("C:\\Users\\ASUS\\Desktop\\1.txt","r");
  ft2=fopen("C:\\Users\\ASUS\\Desktop\\text.txt","w");
  fd1=fopen("C:\\Users\\ASUS\\Desktop\\2.txt","r+");
  fd2=fopen("C:\\Users\\ASUS\\Desktop\\data.txt","w");

  /*ft1=fopen("C:\\Users\\Administrator\\Desktop\\分词结果.txt","r");//分词结果用ft1表示
  ft2=fopen("C:\\Users\\Administrator\\Desktop\\text.txt","w");//点显机读的text用ft2表示
  fd1=fopen("C:\\Users\\Administrator\\Desktop\\盲文块.txt","r+");//盲文块用fd1表示
  fd2=fopen("C:\\Users\\Administrator\\Desktop\\data.txt","w");//点显机读的data用fd2表示*/
  char bufferd[127];
  char buffert[38];
  char bd[7];
  char br0[7];
  char br1[7];
  char br2[7];
  char kong[7]="000000";
  int l, n,i,j,k,s=0;
 // int yan=0;
  int j1=0,t=0, j2=0,j3=0;
  int m1=0,m2=0,m=0;
while(1)
{
  fseek(ft1,t,0);
  fseek(fd1,s,0);
  fgets(bufferd,127,fd1);//从fd1读126个字符存到bufferd
  fgets(buffert,38,ft1);//从ft1读37个字符到buffert
  for(i=0;i<strlen(bufferd);i++)//计算字符串 butterd 的长度，直到空结束字符，但不包括空结束字符，strlen最大为126
	  bufferd[i]=bufferd[i];
  bufferd[i]='\0';
    for(l=0;l<strlen(buffert);l++)
	  buffert[i]=buffert[i];
  buffert[l]='\0';
  if(i<126)
  {
     fputs(bufferd,fd2); 
	 fputs(buffert,ft2);
	break;
  }
  else//大于120即126，构成了20方和21方
  {	 
    for(k=0;k<6;k++)//拿出第20方到br1
       br1[k]=bufferd[6*19+k];
	br1[6]='\0';
    for(k=0;k<6;k++)//拿出第21方到br2
	   br2[k]=bufferd[6*20+k];
	br2[6]='\0';
	 if((br1[0]!='0'||br1[1]!='0'||br1[2]!='0'||br1[3]!='0'||br1[4]!='0'||br1[5]!='0')&&(br2[0]!='0'||br2[1]!='0'||br2[2]!='0'||br2[3]!='0'||br2[4]!='0'||br2[5]!='0'))//br1、br2都不为空方
	{ 
    //计算多少个空格
      for(j=18,j1=0;j>=0;j--)
	  {
	    for(n=0;n<6;n++)
		 br0[n]=bufferd[6*j+n];
		br0[6]='\0';
        if(br0[0]=='0'&&br0[1]=='0'&&br0[2]=='0'&&br0[3]=='0'&&br0[4]=='0'&&br0[5]=='0')
			j1=j1+1;//有j1个空格
	  }
  printf("%d\n",j1); 

//添加转换到text的程序

   for(j=0,j2=0;j<37;j++)
   {
     if(buffert[j]==' ') j2++;
	 fputc(buffert[j],ft2);
	 if(j2==j1) break;
   }
   for(j3=0;j3<36-j;j3++)
     fputc(' ',ft2);
   t=t+j+1;


		//	printf("%s",br1);
	//	printf("       %s\n",br2);
      for(j=18;j>0;j--)
	  {
	    for(n=0;n<6;n++)
		 br0[n]=bufferd[6*j+n];
		br0[6]='\0';
		//if(br0==kong) break;//这个错误
        if(br0[0]=='0'&&br0[1]=='0'&&br0[2]=='0'&&br0[3]=='0'&&br0[4]=='0'&&br0[5]=='0')//这个正确
			break;
	  }
     for(k=0;k<=j;k++)
		 for(n=0;n<6;n++)
			  fputc(bufferd[6*k+n],fd2);
	 for(k=0;k<19-j;k++)
		for(n=0;n<6;n++)
			fputc('0',fd2);
       s=s+6*j+6;

	}



	else 
	{
	  for(k=0;k<120;k++)
      fputc(bufferd[k],fd2);

      for(k=0;k<6;k++)
		  bd[k]=bufferd[114+k];
      bd[6]='\0';//第20方

	   for(j=19,j1=0;j>=0;j--)
	  {
	    for(n=0;n<6;n++)
		 br0[n]=bufferd[6*j+n];
		br0[6]='\0';
        if(br0[0]=='0'&&br0[1]=='0'&&br0[2]=='0'&&br0[3]=='0'&&br0[4]=='0'&&br0[5]=='0')
			j1=j1+1;//有j1个空格
	  }

	    if(bd[0]=='0'&&bd[1]=='0'&&bd[2]=='0'&&bd[3]=='0'&&bd[4]=='0'&&bd[5]=='0')
		{
		   for(j=0,j2=0;j<37;j++)
		   {
             if(buffert[j]==' ') j2++;
        	 fputc(buffert[j],ft2);
        	 if(j2==j1) break;
		   }

		}
		else
		{
		  for(j=0,j2=0;j<37;j++)
		  {
		    if(buffert[j]==' ') j2++;
			if(j2==j1+1) 
			{  
				j=j-1;
				break;
			}
			fputc(buffert[j],ft2);
		  }
		}
      for(j3=0;j3<36-j;j3++)
         fputc(' ',ft2);
       t=t+j+1;
	   s=s+120;
     printf("%d\n",j1); 
	  
	}
  }
 
}



fseek(fd2,0,SEEK_END);
fseek(ft2,0,SEEK_END);
m1=ftell(fd2);
m2=ftell(ft2);
if(m1%120==0)
{
  m=m2%37;
  for(j=0;j<37-m;j++)
   fputc(' ',ft2);
}

	fclose(fd1);
    fclose(fd2);
	fclose(ft1);
    fclose(ft2);




return 0;
 }	
