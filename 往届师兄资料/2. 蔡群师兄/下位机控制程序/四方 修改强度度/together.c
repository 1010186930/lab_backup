
#include<reg52.h>
#include<intrins.h>		
bit cmdArrived = 0; 
/*********************LED*********************/  
unsigned char cmdIndex,start1,start2,start3,start4,start5;//定义芯片锁存唯一缓存数据符号				                          //其1~5分别对应位移缓存器1~3与锁存器1~2
unsigned char ST;
sbit LE2=P3^7;//定义单片机数据引脚 573片2锁存引脚
sbit LE1=P3^5;	  //573片1锁存引脚
sbit OE31=P3^4;	  //573片1使能引脚
sbit OE32=P3^6;	  //573片2使能引脚
sbit SCL1=P2^0;	 //595第11引脚
sbit SCL2=P2^1;	 //595第12引脚
sbit SDA1=P2^2;	 //595第14引脚
sbit OE=P2^5;	 //595片1使能引脚
sbit OE1=P2^4;	 //595片2使能引脚
sbit OE2=P2^3;	 //595片3使能引脚
unsigned char zkb,zkb2,zkb3,zkb4,zkb5;// 定义zkb占空比
unsigned char t,t2,t3,t4,t5;//定灰度扫描时间线
unsigned char k,r1,r2,r3,r4,r5; //定义位移缓存数据写入标志位
unsigned char ce1,ce2,ce3,ce4;	   //定义595片1数据写入变量
unsigned char c2e1,c2e2,c2e3,c2e4; //定义595片2数据写入变量
unsigned char c3e1,c3e2,c3e3,c3e4; //定义595片3数据写入变量
unsigned char c4e1,c4e2,c4e3,c4e4; //定义573片1数据写入变量
unsigned char c5e1,c5e2,c5e3,c5e4; //定义573片2数据写入变量
unsigned char ys;
/*********************动点*********************/
unsigned char pin1,pin2,pin3,pin4,pin5,pin6;
unsigned char ST;
sbit SCL1d=P2^6;	 //595第11引脚
sbit SCL2d=P2^7;	 //595第12引脚
sbit SDA1d=P3^3;	 //595第14引脚
sbit OEd=P3^2;	 //595片1使能引脚 
/*sbit SCL1d=P0^7;	 //595第11引脚
sbit SCL2d=P0^6;	 //595第12引脚
sbit SDA1d=P0^5;	 //595第14引脚
sbit OEd=P0^4;	 //595片1使能引脚 */
unsigned char d1,d2,d3,d4,d5,d6; //定义位移缓存数据写入标志位
unsigned char dz1,dz2,dz3,dz4;	   //定义595片1数据写入变量
unsigned char d2z1,d2z2,d2z3,d2z4; //定义595片2数据写入变量
unsigned char d3z1,d3z2,d3z3,d3z4; //定义595片3数据写入变量
unsigned char d4z1,d4z2,d4z3,d4z4; //定义573片1数据写入变量
unsigned char d5z1,d5z2,d5z3,d5z4; //定义573片2数据写入变量
unsigned char d6z1,d6z2,d6z3,d6z4; //定义573片2数据写入变量
void init()  //初始化函数
  {
     TMOD|=0X01;//初始化定时器
	 TH0=(65536-500)/256;	 //初值配置
	 TL0=(65536-500)%256;
	 EA=1;					 //开总中断
	 ET0=1;					 //定时/计数器T0中断允许
	 TR0=1;					 
  }
void Delay10ms(unsigned int c)   //延时函数 误差 0us
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
	SCON=0X50;			//设置为工作方式1
	TMOD|=0X20;			//设置计数器工作方式2
	PCON=0X00;			//波特率加倍 0x80波特率加倍
	TH1=0Xfd;				//计数器初始值设置，注意波特率是9600的
	TL1=0Xfd;
	ES=1;						//打开接收中断
	EA=1;						//打开总中断
	TR1=1;						//打开计数器
	IP=0X10;
	PS=1;

 }

/*********************LED*********************/ 
 void in(unsigned char Data)//位移缓存器数据输入函数
  {
unsigned char i;
      for(i = 0; i < 8; i++)  //循环8次刚好移完8次
    {
       SCL1 = 0;
	   SCL2 = 0;        //移位寄存器控制端引脚置低    
       _nop_();
       if((Data & 0x80)== 0x80)
            SDA1 =1;
       else
           SDA1 =0;
 
       Data <<= 1;//将数据次高位移动到最高位
 
       SCL1 = 1;//在置为高，产生移位时钟上升沿，上升沿时数据寄存器的数据位移位
       _nop_();
	   _nop_();
	   SCL1 = 0;
     }
  }
 


void out(void)//位移缓存器数据输出函数
  {
      SCL2 = 1;//先将存储寄存器引脚拉高
     _nop_();
	 _nop_();
      SCL2 = 0;//再置高，产生移位时钟上升沿，上升沿时移位寄存器的数据进入数据存储寄存器，更新显示数据
  }
void Usart() interrupt 4
{
    if (RI) //接收到字节
    {																	           
		cmdIndex = SBUF;  //数据接收（SBUF数据接收寄存器）
		ce3 = SBUF;		  //595片1数据接收
		c2e3 = SBUF;	  //595片2数据接收
		c3e3 = SBUF;	  //595片3数据接收
		c4e3 = SBUF;	  //573片1数据接收
		c5e3 = SBUF;	  //573片2数据接收
	    dz3 = SBUF;		  //动点595片1数据接收
		d2z3 = SBUF;	  //动点595片2数据接收
		d3z3 = SBUF;	  //动点595片3数据接收
		d4z3 = SBUF;	  //动点573片1数据接收
		d5z3 = SBUF;	  //动点573片2数据接收
		d6z3 = SBUF;	  //动点573片2数据接收
		ys = SBUF;
		RI = 0;  //清零接收中断标志位
		SBUF = cmdIndex;//将接收到的数据放入到发送寄存器
		cmdArrived = 1;  
    }
    if (TI)//字节发送完
    {													 
        TI = 0;//清零发送中断标志位
    }
}
  void ind(unsigned char Data)//位移缓存器数据输入函数
  {
unsigned char i;
      for(i = 0; i < 8; i++)  //循环8次刚好移完8次
    {
       SCL1d = 0;
	   SCL2d = 0;        //移位寄存器控制端引脚置低    
       _nop_();
       if((Data & 0x80)== 0x80)
            SDA1d =1;
       else
           SDA1d =0;
 
       Data <<= 1;//将数据次高位移动到最高位
 
       SCL1d = 1;//在置为高，产生移位时钟上升沿，上升沿时数据寄存器的数据位移位
       _nop_();
	   _nop_();
	   SCL1d = 0;
     }
  }
 


void outd(void)//位移缓存器数据输出函数
  {
      SCL2d = 1;//先将存储寄存器引脚拉高
     _nop_();
	 _nop_();
      SCL2d = 0;//再置高，产生移位时钟上升沿，上升沿时移位寄存器的数据进入数据存储寄存器，更新显示数据
  }
void LEDinit() //LED初始化函数
{
    zkb=10; //初始9片1化占空比
	zkb2=10;//初始9片2化占空比
	zkb3=10;//初始9片3化占空比
	zkb4=10;//初始3片1化占空比
	zkb5=10;//初始3片2化占空比	                
	ST=0;
    OE=0;//使能端清零
    OE1=0;
    OE2=0;
    OE31=0;
    OE32=0;
    IP=0X10;
	r1=0;//数据写入标志位清零
	r2=0;
	r3=0;
	ce2=0x00;	 //写入变量清零
	ce4=0x00;
	c2e2=0x00;
	c2e4=0x00;
	c3e2=0x00;
	c3e4=0x00;
	c5e4=0xff;
	c4e4=0xff;
}
void PINinit()  //动点初始化函数
{
	d1=0;//数据写入标志位清零
	d2=0;
	d3=0;	 //写入变量清零
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
	k=0;//赋值595输入退出参数
	UsartConfiguration();//初始化计数器
	init();//初始化定时器
   	LEDinit();
	PINinit();
	clear();
    Delay10ms(10);
	sleep();
	Delay10ms(10);

	while(1)
	 {  
	  if(cmdArrived)//进入中断，接受完数据且使得cmdIndex = SBUF后才执行
		{
		  cmdArrived = 0;	
			if(cmdIndex==0x38)//595区域一亮度减少
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
        else if(cmdIndex==0x37)//595区域一亮度增加
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
			
		
	    else if(cmdIndex==0x23)//595区二亮度减少
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
        else if(cmdIndex==0x39)//595区域二亮度增加
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
			
		else if(cmdIndex==0x25)//595区三亮度减少
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
        else if(cmdIndex==0x3F)//595区域三亮度增加
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
		else if(cmdIndex==0x2B)//573区域一亮度减少
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
        else if(cmdIndex==0x36)//573区域一亮度增加
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
		else if(cmdIndex==0x2E)//573区域二亮度减少
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
        else if(cmdIndex==0x2c)//573区域二亮度增加
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
		else if(cmdIndex==0x7E)//灯整体亮灭		 
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
				else if(cmdIndex==0x26)		   //26点亮   7E熄灭
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
        else if(cmdIndex==0x30)//595区域一送数据
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
	    else if(cmdIndex==0x33)	//行区域输入数据点亮
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
		 else if(cmdIndex==0x34)	//列区域送数据
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

		else if(cmdIndex==0x41)		//573点亮  
		{
              if(r4==0)start4=0xff;
			  if(r5==0)start5=0xff;
			  ST=1;
			  while(1&ST)
			   {
				 LE2=0;	//列区域一
				 LE1=1;
				 P1 = start4;
				 LE1=0;

                 LE2=1;	//列区域二
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
  	   else if(cmdIndex==0x31)//动点选择
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
			    if(dz3>=0x01&&dz3<=0x04)  //第一片
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
				if(d2z3>=0x05&&d2z3<=0x08)	 //第二片
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
				if(d3z3>=0x09&&d3z3<=0x12) 	//第三片
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
                if(d4z3>=0x13&&d4z3<=0x16) 	 //第四片
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
				if(d5z3>=0x17&&d5z3<=0x20) 	 //第五片
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
				if(d6z3>=0x21&&d6z3<=0x24) 	 //第六片
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
	    else if(cmdIndex==0x32)	//动点启动
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
	  else if(cmdIndex==0x35)//动点清屏
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
			else if(cmdIndex==0x40)//延迟
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
void time0(void) interrupt 1	 //定时器中断函数
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
