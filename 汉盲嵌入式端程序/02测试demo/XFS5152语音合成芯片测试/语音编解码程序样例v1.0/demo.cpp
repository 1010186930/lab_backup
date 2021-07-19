#include "StdAfx.h"
#include "Codec.h"

static FILE *Fp;
static CODECMODEID g_systate;
static VOLUMEID g_volume;

//�洢���ݻص�
//¼������ʱ��洢ѹ������
bool app_savedata(
	void*		pSrcBuffer,
	int			nBufferBytes
	)
{
	//windowsƽ̨�洢�ļ�
    fwrite(pSrcBuffer, 1, nBufferBytes, Fp);

	return 0;
}

//��ȡ���ݻص�
//���벥��ʱ���ȡѹ������
bool app_loadsave(
	void*		pDstBuffer,
	int* 	pnBufferBytes
	)
{
	//windowsƽ̨��ȡ�ļ�
    *pnBufferBytes = fwrite(pDstBuffer, 1, *pnBufferBytes, Fp);

	return 0;
}

//������ص�
//���𽫱���������ͨ�����ڷ��ͳ�ȥ
bool app_sendcommand(
	void*		pSrcBuffer,
	int			nBufferBytes
	)
{
    //���ݾ����ƽ̨����buf�������ô��ڷ��ͳ�ȥ
    
	return 0;
}

//��ȡ���ڽ�������
char UART_Get_byte(void)
{
	char ch;

	//�Ӵ��ڽ���buf��ȡһ������

	return ch;
}

// ����¼������
void StartEncode(void)
{    
    VOLUMEID volume = BR_volume7;
	
    g_systate = Codec_encode;
	g_volume = BR_volume7;
	
    Fp = fopen("codec.bts", "wb");

	//��ʼ����,���ò�����16k��������5������7
    Codec_Start(g_systate, SR_16000, BR_bitrate5, g_volume, NULL, app_savedata, app_sendcommand);

	while (1)
	{
	    //������ݴ����ֽڷ��ط�0���д����˳�
	    if (Codec_Byte_Proc(UART_Get_byte()))
	    {
	        Codec_Stop();
	    }

		//�Ƿ���Ҫ�˳�
		if (g_systate != Codec_encode)
		{
		    Codec_Stop();
		}

		//�Ƿ���������
		if (g_volume != volume)
		{
		    g_volume = volume;
		    Codec_SetVolume(g_volume);
		}
	}

	fclose(Fp);
}

void StartDecode(void)
{
    VOLUMEID volume = BR_volume7;

	// ���벥������
    g_systate = Codec_decode;
	g_volume = BR_volume7;
	
    Fp = fopen("codec.bts", "rb");
	
    Codec_Start(g_systate, SR_16000, BR_bitrate5, g_volume, app_loadsave, NULL, app_sendcommand);

	while (1)
	{
	    //������ݴ����ֽڷ��ط�0���д��������ɣ��˳�
	    if (Codec_Byte_Proc(UART_Get_byte()))
	    {
	        Codec_Stop();
	    }

		//�Ƿ���Ҫ�˳�
		if (g_systate != Codec_encode)
		{
		    Codec_Stop();
		}

		//�Ƿ���������
		if (g_volume != volume)
		{
		    g_volume = volume;
		    Codec_SetVolume(g_volume);
		}
	}

	fclose(Fp);
}

