
#include<reg52.h>
#include<intrins.h>		
bit cmdArrived = 0; 
/*********************LED*********************/  
unsigned char cmdIndex,start1,start2,start3,start4,start5;//����оƬ����Ψһ�������ݷ���				                          //��1~5�ֱ��Ӧλ�ƻ�����1~3��������1~2
unsigned char ST;
sbit LE2=P3^7;//���嵥Ƭ���������� 573Ƭ2��������
sbit LE1=P3^5;	  //573Ƭ1��������
sbit OE31=P3^4;	  //573Ƭ1ʹ������
sbit OE32=P3^6;	  //573Ƭ2ʹ������
sbit SCL1=P2^0;	 //595��11����
sbit SCL2=P2^1;	 //595��12����
sbit SDA1=P2^2;	 //595��14����
sbit OE=P2^5;	 //595Ƭ1ʹ������
sbit OE1=P2^4;	 //595Ƭ2ʹ������
sbit OE2=P2^3;	 //595Ƭ3ʹ������
unsigned char zkb,zkb2,zkb3,zkb4,zkb5;// ����zkbռ�ձ�
unsigned char t,t2,t3,t4,t5;//���Ҷ�ɨ��ʱ����
unsigned char k,r1,r2,r3,r4,r5; //����λ�ƻ�������д���־λ
unsigned char ce1,ce2,ce3,ce4;	   //����595Ƭ1����д�����
unsigned char c2e1,c2e2,c2e3,c2e4; //����595Ƭ2����д�����
unsigned char c3e1,c3e2,c3e3,c3e4; //����595Ƭ3����д�����
unsigned char c4e1,c4e2,c4e3,c4e4; //����573Ƭ1����д�����
unsigned char c5e1,c5e2,c5e3,c5e4; //����573Ƭ2����д�����
unsigned char ys;
/*********************����*********************/
unsigned char pin1,pin2,pin3,pin4,pin5,pin6;
unsigned char ST;
sbit SCL1d=P2^6;	 //595��11����
sbit SCL2d=P2^7;	 //595��12����
sbit SDA1d=P3^3;	 //595��14����
sbit OEd=P3^2;	 //595Ƭ1ʹ������ 
/*sbit SCL1d=P0^7;	 //595��11����
sbit SCL2d=P0^6;	 //595��12����
sbit SDA1d=P0^5;	 //595��14����
sbit OEd=P0^4;	 //595Ƭ1ʹ������ */
unsigned char d1,d2,d3,d4,d5,d6; //����λ�ƻ�������д���־λ
unsigned char dz1,dz2,dz3,dz4;	   //����595Ƭ1����д�����
unsigned char d2z1,d2z2,d2z3,d2z4; //����595Ƭ2����д�����
unsigned char d3z1,d3z2,d3z3,d3z4; //����595Ƭ3����д�����
unsigned char d4z1,d4z2,d4z3,d4z4; //����573Ƭ1����д�����
unsigned char d5z1,d5z2,d5z3,d5z4; //����573Ƭ2����д�����
unsigned char d6z1,d6z2,d6z3,d6z4; //����573Ƭ2����д�����
void init()  //��ʼ������
  {
     TMOD|=0X01;//��ʼ����ʱ��
	 TH0=(65536-500)/256;	 //��ֵ����
	 TL0=(65536-500)%256;
	 EA=1;					 //�����ж�
	 ET0=1;					 //��ʱ/������T0�ж�����
	 TR0=1;					 
  }
void Delay10ms(unsigned int c)   //��ʱ���� ��� 0us
{
    unsigned char a, b;
    for (;c>0;c--)
	{
		for (b=38;b>0;b--)
		{
			for (a=13;a>0;a--);
		}
           
	}
        
}	
void UsartConfiguration()
{
	SCON=0X50;			//����Ϊ������ʽ1
	TMOD|=0X20;			//���ü�����������ʽ2
	PCON=0X00;			//�����ʼӱ� 0x80�����ʼӱ�
	TH1=0Xfd;				//��������ʼֵ���ã�ע�Ⲩ������9600��
	TL1=0Xfd;
	ES=1;						//�򿪽����ж�
	EA=1;						//�����ж�
	TR1=1;						//�򿪼�����
	IP=0X10;
	PS=1;

 }

/*********************LED*********************/ 
 void in(unsigned char Data)//λ�ƻ������������뺯��
  {
unsigned char i;
      for(i = 0; i < 8; i++)  //ѭ��8�θպ�����8��
    {
       SCL1 = 0;
	   SCL2 = 0;        //��λ�Ĵ������ƶ������õ�    
       _nop_();
       if((Data & 0x80)== 0x80)
            SDA1 =1;
       else
           SDA1 =0;
 
       Data <<= 1;//�����ݴθ�λ�ƶ������λ
 
       SCL1 = 1;//����Ϊ�ߣ�������λʱ�������أ�������ʱ���ݼĴ���������λ��λ
       _nop_();
	   _nop_();
	   SCL1 = 0;
     }
  }
 


void out(void)//λ�ƻ����������������
  {
      SCL2 = 1;//�Ƚ��洢�Ĵ�����������
     _nop_();
	 _nop_();
      SCL2 = 0;//���øߣ�������λʱ�������أ�������ʱ��λ�Ĵ��������ݽ������ݴ洢�Ĵ�����������ʾ����
  }
void Usart() interrupt 4
{
    if (RI) //���յ��ֽ�
    {																	           
		cmdIndex = SBUF;  //���ݽ��գ�SBUF���ݽ��ռĴ�����
		ce3 = SBUF;		  //595Ƭ1���ݽ���
		c2e3 = SBUF;	  //595Ƭ2���ݽ���
		c3e3 = SBUF;	  //595Ƭ3���ݽ���
		c4e3 = SBUF;	  //573Ƭ1���ݽ���
		c5e3 = SBUF;	  //573Ƭ2���ݽ���
	    dz3 = SBUF;		  //����595Ƭ1���ݽ���
		d2z3 = SBUF;	  //����595Ƭ2���ݽ���
		d3z3 = SBUF;	  //����595Ƭ3���ݽ���
		d4z3 = SBUF;	  //����573Ƭ1���ݽ���
		d5z3 = SBUF;	  //����573Ƭ2���ݽ���
		d6z3 = SBUF;	  //����573Ƭ2���ݽ���
		ys = SBUF;
		RI = 0;  //��������жϱ�־λ
		SBUF = cmdIndex;//�����յ������ݷ��뵽���ͼĴ���
		cmdArrived = 1;  
    }
    if (TI)//�ֽڷ�����
    {													 
        TI = 0;//���㷢���жϱ�־λ
    }
}
  void ind(unsigned char Data)//λ�ƻ������������뺯��
  {
unsigned char i;
      for(i = 0; i < 8; i++)  //ѭ��8�θպ�����8��
    {
       SCL1d = 0;
	   SCL2d = 0;        //��λ�Ĵ������ƶ������õ�    
       _nop_();
       if((Data & 0x80)== 0x80)
            SDA1d =1;
       else
           SDA1d =0;
 
       Data <<= 1;//�����ݴθ�λ�ƶ������λ
 
       SCL1d = 1;//����Ϊ�ߣ�������λʱ�������أ�������ʱ���ݼĴ���������λ��λ
       _nop_();
	   _nop_();
	   SCL1d = 0;
     }
  }
 


void outd(void)//λ�ƻ����������������
  {
      SCL2d = 1;//�Ƚ��洢�Ĵ�����������
     _nop_();
	 _nop_();
      SCL2d = 0;//���øߣ�������λʱ�������أ�������ʱ��λ�Ĵ��������ݽ������ݴ洢�Ĵ�����������ʾ����
  }
void LEDinit() //LED��ʼ������
{
    zkb=10; //��ʼ9Ƭ1��ռ�ձ�
	zkb2=10;//��ʼ9Ƭ2��ռ�ձ�
	zkb3=10;//��ʼ9Ƭ3��ռ�ձ�
	zkb4=10;//��ʼ3Ƭ1��ռ�ձ�
	zkb5=10;//��ʼ3Ƭ2��ռ�ձ�	                
	ST=0;
    OE=0;//ʹ�ܶ�����
    OE1=0;
    OE2=0;
    OE31=0;
    OE32=0;
    IP=0X10;
	r1=0;//����д���־λ����
	r2=0;
	r3=0;
	ce2=0x00;	 //д���������
	ce4=0x00;
	c2e2=0x00;
	c2e4=0x00;
	c3e2=0x00;
	c3e4=0x00;
	c5e4=0xff;
	c4e4=0xff;
}
void PINinit()  //�����ʼ������
{
	d1=0;//����д���־λ����
	d2=0;
	d3=0;	 //д���������
    d4=0;
    d5=0;
    d6=0;
	dz4=0xff;
	d2z4=0xff;
	d3z4=0xff;
	d4z4=0xff;
	d5z4=0xff;
	d6z4=0xff;	
}
  void sleep()
{
  OEd=0;
  ind(0xff);
  ind(0xff);
  ind(0xff);
  ind(0xff);
  ind(0xff);
  ind(0xff);
  outd();
}


void clear()
{
    OEd=0;
    ind(0xff);
	ind(0xff);
    ind(0xff);
	ind(0xff);
    ind(0xff);
    ind(0xaa);
    outd();
    Delay10ms(7);
	ind(0xff);
	ind(0xff);
    ind(0xff);
    ind(0xff);
    ind(0xaa);
    ind(0xff);
    outd();
	Delay10ms(7);
	ind(0xff);
	ind(0xff);
    ind(0xff);
	ind(0xaa);
    ind(0xff);
    ind(0xff);
    outd();
    Delay10ms(7);
	ind(0xff);
	ind(0xff);
    ind(0xaa);
	ind(0xff);
    ind(0xff);
    ind(0xff);
    outd();
    Delay10ms(7);
    ind(0xff);
	ind(0x5a);
    ind(0xff);
	ind(0xff);
    ind(0xff);
    ind(0xff);
    outd();
    Delay10ms(7);
	ind(0x55);
	ind(0xff);
    ind(0xff);
	ind(0xff);
    ind(0xff);
    ind(0xff);
    outd();
    Delay10ms(7);	

	sleep();
}	
void main()
{	
	in(0x00);
	in(0x00);
	in(0x00);
	out();
	k=0;//��ֵ595�����˳�����
	UsartConfiguration();//��ʼ��������
	init();//��ʼ����ʱ��
   	LEDinit();
	PINinit();
	clear();
    Delay10ms(10);
	sleep();
	Delay10ms(10);

	while(1)
	 {  
	  if(cmdArrived)//�����жϣ�������������ʹ��cmdIndex = SBUF���ִ��
		{
		  cmdArrived = 0;	
			if(cmdIndex==0x38)//595����һ���ȼ���
		      {
			    k=0;
		 	     if(k==0)
			       {
			         k++;
			         if(zkb>0)
				       {
				         zkb--;
				       }
			        }  	 
		       }
        else if(cmdIndex==0x37)//595����һ��������
			{  
               	 k=0;
			 if(k==0)
			 {
			     if(zkb<20)
				{
				   zkb++;
				}
			  }
		
			}
			
		
	    else if(cmdIndex==0x23)//595�������ȼ���
		      {
			    k=0;
		 	     if(k==0)
			       {
			         k++;
			         if(zkb2>0)
				       {
				         zkb2--;
				       }
			        }  	 
		       }
        else if(cmdIndex==0x39)//595�������������
			{  
               	 k=0;
			 if(k==0)
			 {
			     if(zkb2<20)
				{
				   zkb2++;
				}
			  }
		
			}
			
		else if(cmdIndex==0x25)//595�������ȼ���
		      {
			    k=0;
		 	     if(k==0)
			       {
			         k++;
			         if(zkb3>0)
				       {
				         zkb3--;
				       }
			        }  	 
		       }
        else if(cmdIndex==0x3F)//595��������������
			{  
               	 k=0;
			 if(k==0)
			 {
			     if(zkb3<20)
				{
				   zkb3++;
				}
			  }
		
			}					
		else if(cmdIndex==0x2B)//573����һ���ȼ���
		      {
			    k=0;
		 	     if(k==0)
			       {
			         k++;
			         if(zkb4>0)
				       {
				         zkb4--;
				       }
			        }  	 
		       }
        else if(cmdIndex==0x36)//573����һ��������
			{  
               	 k=0;
			 if(k==0)
			 {
			     if(zkb4<20)
				{
				   zkb4++;
				}
			  }
		
			}					
		else if(cmdIndex==0x2E)//573��������ȼ���
		      {
			    k=0;
		 	     if(k==0)
			       {
			         k++;
			         if(zkb5>0)
				       {
				         zkb5--;
				       }
			        }  	 
		       }
        else if(cmdIndex==0x2c)//573�������������
			{  
               	 k=0;
			 if(k==0)
			 {
			     if(zkb5<20)
				{
				   zkb5++;
				}
			  }
		
			}	  			
		else if(cmdIndex==0x7E)//����������		 
			{	
		//		while(1)
		//	     {
						ST=1;
					 while(1&ST)
					 {
		                 OE=1;
						 OE1=1;
						 OE2=1;
						 ET0=0; 
		ST=0;
				
		     //	 }		
			}		}
				else if(cmdIndex==0x26)		   //26����   7EϨ��
	                   {
					   
						ST=1;
					 while(1&ST)
					 {
						  OE=0;
						  OE1=0;
						  OE2=0;
						  ET0=1;
				 	   ST=0;
						  break;
	                   } 	
					   }
        else if(cmdIndex==0x30)//595����һ������
            {

			 ST=1;
			 start1=0x00;
			 cmdIndex=0x00;
			 ce1=0x00;
			 ce3=0x00;
			 ce2=0x00;

			 start2=0x00;
			 c2e1=0x00;
			 c2e3=0x00;
			 c2e2=0x00;

			 start3=0x00;
			 c3e1=0x00;
			 c3e3=0x00;
			 c3e2=0x00;
			 while(1&ST)
			  {
			    if(ce3>=0x01&&ce3<=0x08)
				{
				 if(ce3==0x01)
				 {
				 ce1=0x01;
				 ce2=ce4|ce1;
				 ce4=ce2;
				 ce3=0x00;
				 }	  
				 if(ce3==0x02)
				 {
				 ce1=0x02;
				 ce2=ce4|ce1;
				 ce4=ce2;
				 ce3=0x00;				 				 
				 }
				 if(ce3==0x03)
				 {
				 ce1=0x04;
				 ce2=ce4|ce1;
				 ce4=ce2;
				 ce3=0x00;				 				 
				 }
				 if(ce3==0x04)
				 {
				 ce1=0x08;
				 ce2=ce4|ce1;
				 ce4=ce2;
				 ce3=0x00;				 				 
				 }
				 if(ce3==0x05)
				 {
				 ce1=0x10;
				 ce2=ce4|ce1;
				 ce4=ce2;
				 ce3=0x00;				 				 
				 }
				 if(ce3==0x06)
				 {
				 ce1=0x20;
				 ce2=ce4|ce1;
				 ce4=ce2;
				 ce3=0x00;				 				 
				 }
				 if(ce3==0x07)
				 {
				 ce1=0x40;
				 ce2=ce4|ce1;
				 ce4=ce2;
				 ce3=0x00;				 
				 }
				 if(ce3==0x08)
				 {
				 ce1=0x80;
				 ce2=ce4|ce1;
				 ce4=ce2;
				 ce3=0x00;
				 }
				 }
				if(c2e3>=0x09&&c2e3<=0x16)
				{
				if(c2e3==0x09)
				 {
				 c2e1=0x01;
				 c2e2=c2e4|c2e1;
				 c2e4=c2e2;
				 c2e3=0x00;
				 }	  
				 if(c2e3==0x10)
				 {
				 c2e1=0x02;
				 c2e2=c2e4|c2e1;
				 c2e4=c2e2;
				 c2e3=0x00;
				 
				 
				 }
				 if(ce3==0x11)
				 {
				 c2e1=0x04;
				 c2e2=c2e4|c2e1;
				 c2e4=c2e2;
				 ce3=0x00;				 				 
				 }
				 if(c2e3==0x12)
				 {
				 c2e1=0x08;
				 c2e2=c2e4|c2e1;
				 c2e4=c2e2;
				 c2e3=0x00;				 				 
				 }
				 if(c2e3==0x13)
				 {c2e1=0x10;
				 c2e2=c2e4|c2e1;
				 c2e4=c2e2;
				 c2e3=0x00;				 				 
				 }
				 if(c2e3==0x14)
				 {
				 c2e1=0x20;
				 c2e2=c2e4|c2e1;
				 c2e4=c2e2;
				 c2e3=0x00;				 				 
				 }
				 if(c2e3==0x15)
				 {c2e1=0x40;
				 c2e2=c2e4|c2e1;
				 c2e4=c2e2;
				 c2e3=0x00;                 				 
				 }
				 if(c2e3==0x16)
				 {
				 c2e1=0x80;
				 c2e2=c2e4|c2e1;
				 c2e4=c2e2;
				 ce3=0x00;
				 }				 
				}
				if(c3e3>=0x17&&c3e3<=0x19) 
				{
				 if(c3e3==0x17)
				 {
				 c3e1=0x01;
				 c3e2=c3e4|c3e1;
				 c3e4=c3e2;
				 c3e3=0x00;
				 }	  
				 if(c3e3==0x18)
				 {
				 c3e1=0x02;
				 c3e2=c3e4|c3e1;
				 c3e4=c3e2;
				 c3e3=0x00;				 				 
				 }
				 if(c3e3==0x19)
				 {c3e1=0x04;
				 c3e2=c3e4|c3e1;
				 c3e4=c3e2;
				 c3e3=0x00;				 				 
				 }		 
				} 					 
				 start1=ce2;
				 start2=c2e2;
				 start3=c3e2; 
               if(cmdIndex==0x33)		 //
			   {
			   if(start1!=0x00)r1=1;
			   if(start2!=0x00)r2=1;
			   if(start3!=0x00)r3=1;
			   ST=0;
			   break;
			   } 
			  }
			}     		  
	    else if(cmdIndex==0x33)	//�������������ݵ���
            {
			  if(r1==0)start1=0x00;
			  if(r2==0)start2=0x00;
			  if(r3==0)start3=0x00;
			  ST=1;
			  while(1&ST)
			   {
                in(start3);
				in(start2);
				in(start1);
				out();
				start1=0x00;
				start2=0x00;
				start3=0x00;
				ce4=0x00;
			    c2e4=0x00;
			    c3e4=0x00;
				r1=0;
				r2=0;
				r3=0;
				ST=0;
			    break;
			  }
			}		
		 else if(cmdIndex==0x34)	//������������
		 {
		     ST=1;
			 start4=0xff;
			 cmdIndex=0x00;
			 c4e1=0xff;
			 c4e3=0x00;
			 c4e2=0xff;

			 start5=0xff;
			 c5e1=0xff;
			 c5e3=0x00;
			 c5e2=0xff;			 

			 while(1&ST)
			  {
			   if(c4e3>=0x01&&c4e3<=0x08)
			   {
                if(c4e3==0x01)
				 {c4e1=0xfe;
				 c4e2=c4e4&c4e1;
				 c4e4=c4e2;
				 c4e3=0x00;
				 }	  
				 if(c4e3==0x02)
				 {c4e1=0xfd;
				 c4e2=c4e4&c4e1;
				 c4e4=c4e2;
				 c4e3=0x00;
				 
				 
				 }
				 if(c4e3==0x03)
				 {c4e1=0xfb;
				 c4e2=c4e4&c4e1;
				 c4e4=c4e2;
				 c4e3=0x00;
				 
				 
				 }
				 if(c4e3==0x04)
				 {c4e1=0xf7;
				 c4e2=c4e4&c4e1;
				 c4e4=c4e2;
				 c4e3=0x00;
				 
				 
				 }
				 if(c4e3==0x05)
				 {c4e1=0xef;
				 c4e2=c4e4&c4e1;
				 c4e4=c4e2;
				 c4e3=0x00;
				 
				 
				 }
				 if(c4e3==0x06)
				 {c4e1=0xdf;
				 c4e2=c4e4&c4e1;
				 c4e4=c4e2;
				 c4e3=0x00;
				 
				 
				 }
				 if(c4e3==0x07)
				 {c4e1=0xbf;
				 c4e2=c4e4&c4e1;
				 c4e4=c4e2;
				 c4e3=0x00;
                 
				 
				 }
				 if(c4e3==0x08)
				 {c4e1=0x7f;
				 c4e2=c4e4&c4e1;
				 c4e4=c4e2;
				 c4e3=0x00;
				 }
				}	
				if(c5e3>=0x09&&c5e3<=0x12) 
				{
				 if(c5e3==0x09)
				 {c5e1=0xfe;
				 c5e2=c5e4&c5e1;
				 c5e4=c5e2;
				 c5e3=0x00;
				 }	  
				 if(c5e3==0x10)
				 {c5e1=0xfd;
				 c5e2=c5e4&c5e1;
				 c5e4=c5e2;
				 c5e3=0x00;
				 
				 
				 }
				 if(c5e3==0x11)
				 {c5e1=0xfb;
				 c5e2=c5e4&c5e1;
				 c5e4=c5e2;
				 c5e3=0x00;
				 
				 
				 }
				 if(c5e3==0x12)
				 {c5e1=0xf7;
				 c5e2=c5e4&c5e1;
				 c5e4=c5e2;
				 c5e3=0x00;
				 
				 
				 }
				}			 
				 start4=c4e2;
				 start5=c5e2;
                 if(cmdIndex==0x41)
			   {
			   if(start4!=0xff)r4=1;
			   if(start5!=0xff)r5=1;
			   ST=0;
			   break;
			   } 
			  }	
			    

		 }  	 

		else if(cmdIndex==0x41)		//573����  
		{
              if(r4==0)start4=0xff;
			  if(r5==0)start5=0xff;
			  ST=1;
			  while(1&ST)
			   {
				 LE2=0;	//������һ
				 LE1=1;
				 P1 = start4;
				 LE1=0;

                 LE2=1;	//�������
				 LE1=0;
				 P1 =start5;
				 LE2=0;
				 start4=0xff;
			     start5=0xff;

			     c4e4=0xff;
			     c5e4=0xff;
				 r4=0;
				 r5=0;
				 ST=0;
			     break;		
		   }

		}
  	   else if(cmdIndex==0x31)//����ѡ��
            {
			 ST=1;
			 pin1=0xff;
			 cmdIndex=0x00;
			 dz1=0xff;
			 dz3=0x00;
			 dz2=0xff;

			 pin2=0xff;
			 d2z1=0xff;
			 d2z3=0x00;
			 d2z2=0xff;

			 pin3=0xff;
			 d3z1=0xff;
			 d3z3=0x00;
			 d3z2=0xff;

			 pin4=0xff;
			 d4z1=0xff;
			 d4z3=0x00;
			 d4z2=0xff;

			 pin5=0xff;
			 d5z1=0xff;
			 d5z3=0x00;
			 d5z2=0xff;

			 pin6=0xff;
			 d6z1=0xff;
			 d6z3=0x00;
			 d6z2=0xff;

			 while(1&ST)
			  {
			    if(dz3>=0x01&&dz3<=0x04)  //��һƬ
				{
				 if(dz3==0x01)
				 {
				 dz1=0xfd;
				 dz2=dz4&dz1;
				 dz4=dz2;
				 dz3=0x00;
				 }	  
				 if(dz3==0x02)
				 {
				 dz1=0xf7;
				 dz2=dz4&dz1;
				 dz4=dz2;
				 dz3=0x00;				 				 
				 }
				 if(dz3==0x03)
				 {
				 dz1=0xdf;
				 dz2=dz4&dz1;
				 dz4=dz2;
				 dz3=0x00;				 				 
				 }
				 if(dz3==0x04)
				 {
				 dz1=0x7f;
				 dz2=dz4&dz1;
				 dz4=dz2;
				 dz3=0x00;				 				 
				 }
				 }
				if(d2z3>=0x05&&d2z3<=0x08)	 //�ڶ�Ƭ
				{
				if(d2z3==0x05)
				 {
				 d2z1=0xfd;
				 d2z2=d2z4&d2z1;
				 d2z4=d2z2;
				 d2z3=0x00;
				 }	  
				 if(d2z3==0x06)
				 {
				 d2z1=0xf7;
				 d2z2=d2z4&d2z1;
				 d2z4=d2z2;
				 d2z3=0x00;		 				 
				 }
				 if(d2z3==0x07)
				 {
				 d2z1=0xdf;
				 d2z2=d2z4&d2z1;
				 d2z4=d2z2;
				 d2z3=0x00;				 				 
				 }
				 if(d2z3==0x08)
				 {
				 d2z1=0x7f;
				 d2z2=d2z4&d2z1;
				 d2z4=d2z2;
				 d2z3=0x00;				 				 
				 }				 
				}
				if(d3z3>=0x09&&d3z3<=0x12) 	//����Ƭ
				{
				 if(d3z3==0x09)
				 {
				 d3z1=0xfd;
				 d3z2=d3z4&d3z1;
				 d3z4=d3z2;
				 d3z3=0x00;
				 }	  
				 if(d3z3==0x10)
				 {
				 d3z1=0xf7;
				 d3z2=d3z4&d3z1;
				 d3z4=d3z2;
				 d3z3=0x00;				 				 
				 }
				 if(d3z3==0x11)
				 {d3z1=0xdf;
				 d3z2=d3z4&d3z1;
				 d3z4=d3z2;
				 d3z3=0x00;				 				 
				 }
				 if(d3z3==0x12)
				 {d3z1=0x7f;
				 d3z2=d3z4&d3z1;
				 d3z4=d3z2;
				 d3z3=0x00;				 				 
				 }				 
				} 
                if(d4z3>=0x13&&d4z3<=0x16) 	 //����Ƭ
				{
				 if(d4z3==0x13)
				 {
				 d4z1=0xfd;
				 d4z2=d4z4&d4z1;
				 d4z4=d4z2;
				 d4z3=0x00;
				 }	  
				 if(d4z3==0x14)
				 {
				 d4z1=0xf7;
				 d4z2=d4z4&d4z1;
				 d4z4=d4z2;
				 d4z3=0x00;				 				 
				 }
				 if(d4z3==0x15)
				 {d4z1=0xdf;
				 d4z2=d4z4&d4z1;
				 d4z4=d4z2;
				 d4z3=0x00;				 				 
				 }
				 if(d4z3==0x16)
				 {d4z1=0x7f;
				 d4z2=d4z4&d4z1;
				 d4z4=d4z2;
				 d4z3=0x00;				 				 
				 }				 
				} 
				if(d5z3>=0x17&&d5z3<=0x20) 	 //����Ƭ
				{
				 if(d5z3==0x17)
				 {
				 d5z1=0xfd;
				 d5z2=d5z4&d5z1;
				 d5z4=d5z2;
				 d5z3=0x00;
				 }	  
				 if(d5z3==0x18)
				 {
				 d5z1=0xf7;
				 d5z2=d5z4&d5z1;
				 d5z4=d5z2;
				 d5z3=0x00;				 				 
				 }
				 if(d5z3==0x19)
				 {d5z1=0xef;
				 d5z2=d5z4&d5z1;
				 d5z4=d5z2;
				 d5z3=0x00;				 				 
				 }
				 if(d5z3==0x20)
				 {d5z1=0xbf;
				 d5z2=d5z4&d5z1;
				 d5z4=d5z2;
				 d5z3=0x00;				 				 
				 }				 
				} 
				if(d6z3>=0x21&&d6z3<=0x24) 	 //����Ƭ
				{
				 if(d6z3==0x21)
				 {
				 d6z1=0xfe;
				 d6z2=d6z4&d6z1;
				 d6z4=d6z2;
				 d6z3=0x00;
				 }	  
				 if(d6z3==0x22)
				 {
				 d6z1=0xfb;
				 d6z2=d6z4&d6z1;
				 d6z4=d6z2;
				 d6z3=0x00;				 				 
				 }
				 if(d6z3==0x23)
				 {d6z1=0xef;
				 d6z2=d6z4&d6z1;
				 d6z4=d6z2;
				 d6z3=0x00;				 				 
				 }
				 if(d6z3==0x24)
				 {d6z1=0xbf;
				 d6z2=d6z4&d6z1;
				 d6z4=d6z2;
				 d6z3=0x00;				 				 
				 }				 
				} 					 
				 pin1=dz2;
				 pin2=d2z2;
				 pin3=d3z2; 
				 pin4=d4z2;
				 pin5=d5z2;
				 pin6=d6z2;
               if(cmdIndex==0x32)		 //
			   {
			   if(pin1!=0xff)d1=1;
			   if(pin2!=0xff)d2=1;
			   if(pin3!=0xff)d3=1;
			   if(pin4!=0xff)d4=1;
			   if(pin5!=0xff)d5=1;
			   if(pin6!=0xff)d6=1;
			   ST=0;
			   break;
			   } 
			  }
			}     		  
	    else if(cmdIndex==0x32)	//��������
            {
			  if(d1==0)pin1=0xff;
			  if(d2==0)pin2=0xff;
			  if(d3==0)pin3=0xff;
			  if(d4==0)pin4=0xff;
			  if(d5==0)pin5=0xff;
			  if(d6==0)pin6=0xff;
			  ST=1;
			  clear();
			  while(1&ST)
			   {
			    OEd=0;
			    ind(pin6);
				ind(pin5);
				ind(pin4);
				ind(pin3);
				ind(pin2);
				ind(pin1);
				outd();
				Delay10ms(7);
               sleep();
				pin1=0xff;
				pin2=0xff;
				pin3=0xff;
				pin4=0xff;
				pin5=0xff;
				pin6=0xff;
				dz4=0xff;
			    d2z4=0xff;
			    d3z4=0xff;
				d4z4=0xff;
			    d5z4=0xff;
			    d6z4=0xff;
				d1=0;
				d2=0;
				d3=0;
				d4=0;
				d5=0;
				d6=0;
				ST=0;
				cmdIndex=0;
			    break;
			  }	
			}
	  else if(cmdIndex==0x35)//��������
	        {
			         OEd=0;
                     ind(0xff);
					 ind(0xff);
                     ind(0xff);
                     ind(0xff);
                     ind(0xff);
                     ind(0xaa);
                     outd();
                     Delay10ms(10);
					 ind(0xff);
					 ind(0xff);
                     ind(0xff);
					 ind(0xff);
                     ind(0xaa);
                     ind(0xff);
                     outd();
					 Delay10ms(10);
                     ind(0xff);
					 ind(0xff);
                     ind(0xff);
					 ind(0xaa);
                     ind(0xff);
                     ind(0xff);
                     outd();
                     Delay10ms(10);
					 ind(0xff);
					 ind(0xff);
                     ind(0xaa);
					 ind(0xff);
                     ind(0xff);
                     ind(0xff);
                     outd();
                     Delay10ms(10);
					 ind(0xff);
					 ind(0x5a);
                     ind(0xff);
					 ind(0xff);
                     ind(0xff);
                     ind(0xff);
                     outd();
                     Delay10ms(10);
					 ind(0x55);
					 ind(0xff);
                     ind(0xff);
					 ind(0xff);
                     ind(0xff);
                     ind(0xff);
                     outd();
                     Delay10ms(10);
					 cmdIndex=0;
					 sleep();
  	 
			}
			else if(cmdIndex==0x40)//�ӳ�
			{
		    
			int f;
			cmdIndex=0x00;
			ST=1;
			while(1&ST)
			{
		   if(ys==0x01)
				 {
				 f=5;
				 ys=0x00;
				 }	  	  
		   if(ys==0x02)
				 {
				 f=7;
				 			 ys=0x00;
				 }
		   if(ys==0x03)
				 {
				 f=15;
				 			 ys=0x00;
				 }
		   if(ys==0x04)
				 {
				 f=9;
				 			 ys=0x00;
				 }
		   if(ys==0x05)
				 {
				 f=11;
				 			 ys=0x00;
				 }
		   if(ys==0x06)
				 {
				 f=13;
				 			 ys=0x00;
				 }
		   if(ys==0x07)
				 {
				 f=15;
				 			 ys=0x00;
				 }
		  if(ys==0x08)
				 {
				 f=17;
				 			 ys=0x00;
				 }
		 if(ys==0x09)
				 {
				 f=19;
				 			 ys=0x00;
				 }
		if(ys==0x10)
				 {
				 f=21;
				 			 ys=0x00;
				 } 
			if(cmdIndex==0x42)
			{

            Delay10ms(f);
			cmdIndex=0x00;
	ST=0;
	break;
		 }	}
			}						
			}	  
      	} 
     }						  
void time0(void) interrupt 1	 //��ʱ���жϺ���
 {
    TH0=(65536-500)/256;
	TL0=(65536-500)%256;
	++t;
	++t2;
	++t3;
    ++t4;
 	++t5;
	
	if(t>20)
	  {
	  t=0;
	  }
	if(t<zkb)
	  {
	   OE=0;
	  }
	else 
	  {
	    OE=1;
	  }


  	  if(t2>20)
	  {
	  t2=0;
	  }
if(t2<zkb2)
	  {
	   OE1=0;
	  }
else 
	  {
	    OE1=1;
	  }


	if(t3>20)
	  {
	  t3=0;
	  }
	if(t3<zkb3)
	  {
	   OE2=0;
	  }
	else 
	  {
	    OE2=1;
	  }	 
		
	 	if(t4>20)
	  {
	  t4=0;
	  }
	if(t4<zkb4)
	  {
	   OE31=0;
	  }
	else 
	  {
	    OE31=1;
	  }


	if(t5>20)
	  {
	  t5=0;
	  }
	if(t5<zkb5)
	  {
	   OE32=0;
	  }
	else 
	  {
	    OE32=1;
	  }
  }
