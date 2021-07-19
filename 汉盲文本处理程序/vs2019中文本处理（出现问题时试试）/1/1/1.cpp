#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>

FILE* ft1 = NULL;
FILE* ft2 = NULL;
FILE* fd1 = NULL;
FILE* fd2 = NULL;

int main()
{
	fopen_s(&ft1,"C:\\Users\\10101\\Desktop\\分词结果.txt", "r");//分词结果用ft1表示
	fopen_s(&ft2,"C:\\Users\\10101\\Desktop\\text.txt", "w");//点显机读的text用ft2表示
	fopen_s(&fd1,"C:\\Users\\10101\\Desktop\\盲文块.txt", "r+");//盲文块用fd1表示
	fopen_s(&fd2,"C:\\Users\\10101\\Desktop\\data.txt", "w");//点显机读的data用fd2表示

	/*ft1=fopen("C:\\Users\\Administrator\\Desktop\\分词结果.txt","r");//分词结果用ft1表示
	ft2=fopen("C:\\Users\\Administrator\\Desktop\\text.txt","w");//点显机读的text用ft2表示
	fd1=fopen("C:\\Users\\Administrator\\Desktop\\盲文块.txt","r+");//盲文块用fd1表示
	fd2=fopen("C:\\Users\\Administrator\\Desktop\\data.txt","w");//点显机读的data用fd2表示*/
	char bufferd[127];//实际上最多只读存126，最后一位是'\0'
	char buffert[38];//实际上最多只能存37，最后一位是'\0'
	char bd[7];
	char br0[7];
	char br1[7];
	char br2[7];
	char kong[7] = "000000";
	int l, n, i, j, k, s = 0;
	// int yan=0;
	int j1 = 0, t = 0, j2 = 0, j3 = 0;
	int m1 = 0, m2 = 0, m = 0;
	while (1)
	{
		fseek(ft1, t, 0);//从ft1的t位置开始读
		fseek(fd1, s, 0);//从fd1的s位置开始读
		fgets(bufferd, 127, fd1);//从fd1读 126个字符存到bufferd
		fgets(buffert, 38, ft1);//从ft1读37个字符到buffert
		for (i = 0; i < strlen(bufferd); i++)//计算字符串 butterd 的长度，直到空结束字符，但不包括空结束字符，strlen最大为126，即计算数组的有效长度
			bufferd[i] = bufferd[i];//就是赋值，没什么含义
		bufferd[i] = '\0';//最大情况下127置结束标志符
		for (l = 0; l < strlen(buffert); l++)//计算字符串 buttert 的长度，直到空结束字符，但不包括空结束字符
			buffert[i] = buffert[i];
		buffert[l] = '\0';//这三行似乎没有用到
		if (i < 126)//小于126只可能是小于等于120，末尾直接输出
		{
			fputs(bufferd, fd2);//把bufferd字符串写入fd2中，但不包括空字符  
			fputs(buffert, ft2);//把buffert字符串写入ft2中，但不包括空字符
			break;
		}
		else//大于120即126，构成了20方和21方
		{
			for (k = 0; k < 6; k++)//拿出第20方到br1
				br1[k] = bufferd[6 * 19 + k];
			br1[6] = '\0';
			for (k = 0; k < 6; k++)//拿出第21方到br2
				br2[k] = bufferd[6 * 20 + k];
			br2[6] = '\0';
			if ((br1[0] != '0' || br1[1] != '0' || br1[2] != '0' || br1[3] != '0' || br1[4] != '0' || br1[5] != '0') && (br2[0] != '0' || br2[1] != '0' || br2[2] != '0' || br2[3] != '0' || br2[4] != '0' || br2[5] != '0'))//br1、br2都不为空方
			{
				//计算多少个空格
				for (j = 18, j1 = 0; j >= 0; j--)//遍历盲文块的前19格
				{
					for (n = 0; n < 6; n++)
						br0[n] = bufferd[6 * j + n];
					br0[6] = '\0';//每6个存入字符数组br0，最后一位添置结束符
					if (br0[0] == '0' && br0[1] == '0' && br0[2] == '0' && br0[3] == '0' && br0[4] == '0' && br0[5] == '0')//如果6个点都是0，则代表空方
						j1 = j1 + 1;//前19格盲文块有j1个空方
				}
				printf("%d\n", j1);//第一次printf输出前19格的空方数

				//处理分词结果文本
				for (j = 0, j2 = 0; j < 37; j++)//循环37次
				{
					if (buffert[j] == ' ')//如果buffert[j]是空格
						j2++;//j2计数
					fputc(buffert[j], ft2);//把buffert[j]写入ft2
					if (j2 == j1) break;//当分词结果的前37个字符的空格数等于前19格盲文块的空格数时，跳出循环
				}
				for (j3 = 0; j3 < 36 - j; j3++)//计算要补多少个空格ft2才能满37个字符
					fputc(' ', ft2);//补空格
				t = t + j + 1;//偏移量为上次读到位置的后面一位，由于上面的for循环是调用的全局变量j，所以值可以传下去！这点和在for循环里面int j不同！

				for (j = 18; j > 0; j--)//遍历盲文块的前18格，2-19个
				{
					for (n = 0; n < 6; n++)
						br0[n] = bufferd[6 * j + n];
					br0[6] = '\0';
					if (br0[0] == '0' && br0[1] == '0' && br0[2] == '0' && br0[3] == '0' && br0[4] == '0' && br0[5] == '0')//倒着判断，如果遇到空方
						break;//跳出该循环
				}
				for (k = 0; k <= j; k++)
					for (n = 0; n < 6; n++)
						fputc(bufferd[6 * k + n], fd2);//把包括空方的前j个方写入fd2
				for (k = 0; k < 19 - j; k++)
					for (n = 0; n < 6; n++)
						fputc('0', fd2);//补满120个点
				s = s + 6 * j + 6;//记录位置

			}



			else
			{
				for (k = 0; k < 120; k++)
					fputc(bufferd[k], fd2);//先读取前120个点到fd2

				for (k = 0; k < 6; k++)
					bd[k] = bufferd[114 + k];
				bd[6] = '\0';//把第20方放进bd[6]

				for (j = 19, j1 = 0; j >= 0; j--)//取前20方
				{
					for (n = 0; n < 6; n++)
						br0[n] = bufferd[6 * j + n];
					br0[6] = '\0';
					if (br0[0] == '0' && br0[1] == '0' && br0[2] == '0' && br0[3] == '0' && br0[4] == '0' && br0[5] == '0')
						j1 = j1 + 1;//判断前20方有几个空格
				}
				if (bd[0] == '0' && bd[1] == '0' && bd[2] == '0' && bd[3] == '0' && bd[4] == '0' && bd[5] == '0')//如果第20方是空格
				{
					for (j = 0, j2 = 0; j < 37; j++)//判断前37个字符有多少个空格
					{
						if (buffert[j] == ' ') 
							j2++;
						fputc(buffert[j], ft2);
						if (j2 == j1) 
							break;//两者空格数一样后跳出该循环
					}
				}
				else//如果第20方不是空格，分词结果的空格就要多数一格，不然会漏掉最后的一个字
				{
					for (j = 0, j2 = 0; j < 37; j++)
					{
						if (buffert[j] == ' ') 
							j2++;
						if (j2 == j1 + 1)
						{
							j = j - 1;
							break;
						}
						fputc(buffert[j], ft2);
					}
				}
				for (j3 = 0; j3 < 36 - j; j3++)//补满37个
					fputc(' ', ft2);
				t = t + j + 1;//更新偏移量
				s = s + 120;//更新偏移量
				printf("%d\n", j1);//输出前20格盲文块的空格数

			}
		}

	}



	fseek(fd2, 0, SEEK_END);
	fseek(ft2, 0, SEEK_END);
	m1 = ftell(fd2);
	m2 = ftell(ft2);
	if (m1 % 120 == 0)
	{
		m = m2 % 37;
		for (j = 0; j < 37 - m; j++)
			fputc(' ', ft2);
	}

	fclose(fd1);
	fclose(fd2);
	fclose(ft1);
	fclose(ft2);




	return 0;
}