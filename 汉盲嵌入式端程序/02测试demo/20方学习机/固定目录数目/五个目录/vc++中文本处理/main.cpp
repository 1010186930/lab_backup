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
/*
//����
  ft1=fopen("C:\\Users\\wei\\Desktop\\bt\\�ִʽ��.txt","r");
  ft2=fopen("C:\\Users\\wei\\Desktop\\bt\\text.txt","w");
  fd1=fopen("C:\\Users\\wei\\Desktop\\bt\\ä�Ŀ�.txt","r+");
  fd2=fopen("C:\\Users\\wei\\Desktop\\bt\\data.txt","w");
  */

  ft1=fopen("C:\\Users\\wei\\Desktop\\ä��ѧϰ��\\ʦ�ܳ¿���\\TO\\��ʫ+����\\��ʫ\\����\\�ִʽ��.txt","r");
  ft2=fopen("C:\\Users\\wei\\Desktop\\ä��ѧϰ��\\ʦ�ܳ¿���\\TO\\��ʫ+����\\��ʫ\\����\\text.txt","w");
  fd1=fopen("C:\\Users\\wei\\Desktop\\ä��ѧϰ��\\ʦ�ܳ¿���\\TO\\��ʫ+����\\��ʫ\\����\\ä�Ŀ�.txt","r+");
  fd2=fopen("C:\\Users\\wei\\Desktop\\ä��ѧϰ��\\ʦ�ܳ¿���\\TO\\��ʫ+����\\��ʫ\\����\\data.txt","w");
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
while(1)
{
  fseek(ft1,t,0);
  fseek(fd1,s,0);
  fgets(bufferd,127,fd1);
  fgets(buffert,38,ft1);
  for(i=0;i<strlen(bufferd);i++)
	  bufferd[i]=bufferd[i];
  bufferd[i]='\0';
    for(l=0;l<strlen(buffert);l++)
	  buffert[i]=buffert[i];
  buffert[l]='\0';
  // printf("%d\n",i);   //126+126+126+126+126+73
  if(i<126)//С��126��ĩβֱ�����
  {
    fputs(bufferd,fd2);  
	 fputs(buffert,ft2);  
	//printf("%d\n",i);
	break;
  }
  else
  {	 
    for(k=0;k<6;k++)//��20��
       br1[k]=bufferd[6*19+k];
	br1[6]='\0';
    for(k=0;k<6;k++)//��21��
	   br2[k]=bufferd[6*20+k];
	br2[6]='\0';




//	if(br1!=kong&&br2!=kong)
	 if((br1[0]!='0'||br1[1]!='0'||br1[2]!='0'||br1[3]!='0'||br1[4]!='0'||br1[5]!='0')&&(br2[0]!='0'||br2[1]!='0'||br2[2]!='0'||br2[3]!='0'||br2[4]!='0'||br2[5]!='0'))//br1\br2Ϊ�շ�
	{ 
    //������ٸ��ո�
      for(j=18,j1=0;j>=0;j--)
	  {
	    for(n=0;n<6;n++)
		 br0[n]=bufferd[6*j+n];
		br0[6]='\0';
        if(br0[0]=='0'&&br0[1]=='0'&&br0[2]=='0'&&br0[3]=='0'&&br0[4]=='0'&&br0[5]=='0')
			j1=j1+1;//��j1���ո�
	  }
  printf("%d\n",j1); 

//���ת����text�ĳ���

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
		//if(br0==kong) break;//�������
        if(br0[0]=='0'&&br0[1]=='0'&&br0[2]=='0'&&br0[3]=='0'&&br0[4]=='0'&&br0[5]=='0')//�����ȷ
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
      bd[6]='\0';

	   for(j=19,j1=0;j>=0;j--)
	  {
	    for(n=0;n<6;n++)
		 br0[n]=bufferd[6*j+n];
		br0[6]='\0';
        if(br0[0]=='0'&&br0[1]=='0'&&br0[2]=='0'&&br0[3]=='0'&&br0[4]=='0'&&br0[5]=='0')
			j1=j1+1;//��j1���ո�
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



	fclose(fd1);
    fclose(fd2);
	fclose(ft1);
    fclose(ft2);

return 0;
 }	
