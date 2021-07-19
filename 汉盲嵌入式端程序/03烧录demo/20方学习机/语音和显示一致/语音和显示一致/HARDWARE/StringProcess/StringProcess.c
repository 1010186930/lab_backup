#include "StringProcess.h"
#include "tts.h"
char* BufDisplay(char* buffer,char *bufdisplay)
{
	char* q = buffer;
	char* p = bufdisplay;
	char* k = q;
	int tune = 0;
	while (*q != '\0')
	{
		if (*q >= 0x61 && *q <= 0x7A)
		{
			k = q;
			tune = *(++k);
			if (tune >= 0x31 && tune <= 0x34)
			{
				*p = *q;
				q += 2;
				p++;
			}
			else
			{
				*p = *q;
				p++;
				q++;

			}
		}
		else
		{
			*p = *q;
			p++;
			q++;
		}
	}
	*p = '\0';
	return bufdisplay;
}
char* ReplaceSubStr(const char* str, const char* srcSubStr, const char* dstSubStr, char* out)
{
	char* out_temp = out;
	int src_len = strlen(srcSubStr);//�Ӵ�����
	int dst_len = strlen(dstSubStr);//�滻������
	int i=0;
	if (!str && !out)
	{
		return NULL;
	}
	if (!srcSubStr && !dstSubStr)
	{
		return out;
	}
	
	while (*str != '\0')//str��ԭ�ַ���
	{
		if (*str == *srcSubStr)//srcSubStr��Ҫ���ҵ��Ӵ�
		{
			//���ܷ����滻
			const char* str_temp = str;
			int flag = 0;
			for (i = 0; i < src_len; i++)
			{
				if (str_temp[i] != srcSubStr[i])
				{
					flag = 1;
					break;
				}
			}
			if (flag)
			{
				//˵�������滻
				*out_temp++ = *str++;
			}
			else
			{
				//˵��Ҫ�滻
				for (i = 0; i < dst_len; i++)
				{
					*out_temp++ = dstSubStr[i];
				}
				str = str + src_len;
			}
		}
		else
		{
			//�����滻
			*out_temp++ = *str++;
		}
	}
	*out_temp = 0;
	return out;
}
void SpecialSynthesis(char *str)
{
	if(strstr(str,"����"))
		{
			
			SPeech("��ʮһ�� ��ĸ u�� u��i u�� u�� v�� ��r");
		}
		else if(strstr(str,"����n"))
		{
			
			SPeech("��ʮ��� ��ĸ v��n ��n i��ng");
		}
		else if(!strcmp(str,"��һ�� �����������"))
		{
			SPeech("��һ�� �����������");
		}
		else if(!strcmp(str,"�������̳�"))
		{
			SPeech("�������̳�");
		}
		else if(!strcmp(str,"ͨ��ä�ı������̳�"))
		{
			SPeech("ͨ��ä�ı������̳�");
		}
		else
			SPeech(str);
}
void SpecialSynthesisInBk(char * synbuf, char * srcbuf)
{
	char *q;
	if(strstr(srcbuf,"����"))
		{
			q = strchr(srcbuf, ' ');
			*(q+1) = '\0';
			strcpy(synbuf, srcbuf);//
			strcat(synbuf, "��ʮһ�� ��ĸu�� u��i u�� u�� v�� ��r");
			
			SPeech(synbuf);
		}
		else if(strstr(srcbuf,"����n"))
		{
			q=strchr(srcbuf,' ');
			*(q+1) = '\0';
			strcpy(synbuf, srcbuf);//
			strcat(synbuf,"��ʮ��� ��ĸ v��n ��n i��ng");
			
			SPeech(synbuf);
		}	
		else if(strstr(srcbuf,"�����������"))
		{
			q=strchr(srcbuf,' ');
			*(q+1) = '\0';
			strcpy(synbuf, srcbuf);//
			strcat(synbuf,"��һ�� �����������");
			
			SPeech(synbuf);
		}	
		else	
		SPeech(srcbuf);
}