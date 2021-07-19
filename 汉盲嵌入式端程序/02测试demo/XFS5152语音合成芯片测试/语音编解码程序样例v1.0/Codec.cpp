
#include "StdAfx.h"
#include "Codec.h"


//�ļ�˵��
//���ļ�����ȫ���ñ�׼c��д����ֱ����ֲ��֧�ֱ�׼c��ƽ̨
//�û�������������ֱ��ʹ�ø��ļ�
//�����������뼼��֧������


#define CMD_START_ENCODE 0x41
#define CMD_START_DECODE 0x42
#define CMD_SEND_DECODE 0x43
#define CMD_STOP_CODEC 0x44	
#define CMD_SEND_VOLUME 0x45

typedef enum
{
	eRecvCommon,
	eRecvFrameLenH,
	eRecvFrameLenL,
	eRecvFrameCmd,
	eRecvFrameData
}ERecvDataType;

typedef struct tagCodecInfo
{
    char SampleRateId;
	char BitRateId;
	char Volume;
}CodecInfo;

typedef struct tagCommFrm
{
	char Header; // ��������Ϊ0xFD, ��������Ϊ0xFC
	char ComLenHH; // ����ȸ��ֽ�
	char ComLenLL; // ����ȵ��ֽ�
	char CommCode; // ������
	union
	{
		CodecInfo Param;
		char Data[64];
	}DataArea;
}CommFrame;

static ivCBSaveData 	*g_pfSaveData;
static ivCBLoadData 	*g_pfLoadData;
static ivCBSendCommand *g_pfSendCommand;
static char            g_tu8RecvFrame[70];
static int 			g_u16RecvBufIndex;
static int 			g_u16RecvFrameDataLen;
static int 			g_u32RecvFrameLen;
static int			    g_eRecvType;
static int             g_Mode;

//������ID�����֣�ȡֵΪ0~5,���±�enc_frame_byte
//�������ã�
//����ģʽ��������ȡֵ0~7, ����8Ϊ¼��ģ���Զ�����
//����ģʽ����ֵΪ0~7

//�����ʺ�ѹ�������ʶ����ÿһ֡�ֽ���
static const char enc_frame_byte[][6] = 
{
	{   6,  15, 20, 28, 38,	62	},
	{   10, 15, 20, 25, 32, 42	},
};

static void ResetRecvBuf(void)
{
	g_u16RecvBufIndex = 0;
	g_u16RecvFrameDataLen = 0;
}

static bool Frame_Proc(void)
{
    CommFrame *pCommFrm = (CommFrame *)g_tu8RecvFrame;

	switch (pCommFrm->CommCode)
	{
		case 0x21:  /* �д��󲿷��Ǵ����ٶȲ�֧�� */
		case 0x22:  /* ������� */
			return 1;

		case 0x23:  /* ������������������� */
		    if (g_pfLoadData != NULL)
		    {
		        int len;
				int rd;
				
				next_scan:			
				rd = 4;
				g_pfLoadData(&len, &rd);
				if (4 != rd)
				{												
				    return 1;
				}
				else
				{
					if (62 < len)
					{
						goto next_scan;
					}
					else
					{											
						//�����ݸ�5051оƬ���벥��
						CommFrame commframe;
						int lentemp;

					    lentemp = len;
					    g_pfLoadData(&commframe.DataArea, &len);

						if (lentemp != len)
						{
						    return 1;
						}
						else
						{		
							int comlen = len+1;
							
							commframe.Header = 0xFD;
							commframe.ComLenHH = (char)(comlen>>8);
							commframe.ComLenLL = (char)comlen;
							commframe.CommCode = CMD_SEND_DECODE;
								
							if (NULL != g_pfSendCommand)
							{
							    g_pfSendCommand((void*)&commframe, len+4);
							}
						}
					}
				}
		    }
			break;

		case 0x20: // �յ�һ֡��������
		    if (g_pfSaveData != NULL)
		    {
		        g_u32RecvFrameLen -= 1; /* ȥ��������һ���ֽ� */

				if (g_u32RecvFrameLen <= 62)
				{
					g_pfSaveData(&(g_u32RecvFrameLen), 4);
					g_pfSaveData((void *)&pCommFrm->DataArea, g_u32RecvFrameLen);
				}
		    }
			break;

		default:
			break;
	}

	return 0;
}

//��ʼ¼������빦��
//SamplerateID 
//Bitrateid
//volume 
void Codec_Start(CODECMODEID CodecMode, SAMPLERATEID SampleRate, BITRATEID BitRate, VOLUMEID Volume,
        ivCBLoadData *pfLoadData, ivCBSaveData *pfSaveData, ivCBSendCommand *pfSendCommand)
{    
	CommFrame SendComm;
		
    g_pfLoadData = pfLoadData;
	g_pfSaveData = pfSaveData;
	g_pfSendCommand = pfSendCommand;	
		
	SendComm.Header = 0xFD;
	SendComm.ComLenHH = 0;
	SendComm.ComLenLL = 4;
	
	SendComm.DataArea.Param.SampleRateId = SampleRate;
	SendComm.DataArea.Param.BitRateId = BitRate;	
	SendComm.DataArea.Param.Volume = Volume;
	
	g_Mode = CodecMode;
	if (Codec_encode == CodecMode)
	{
		SendComm.CommCode = CMD_START_ENCODE;  // ��ʼ����
	}
	else
	{
		SendComm.CommCode = CMD_START_DECODE; // ��ʼ����
		SendComm.DataArea.Param.Volume &= 0x07;
	}

	if (NULL != g_pfSendCommand)
	{
	    g_pfSendCommand((void*)&SendComm, 7);
	}	
}

//���������п���ʱ��������
void Codec_SetVolume(VOLUMEID Volume)
{
	CommFrame SendComm;
	
	SendComm.Header = 0xFD;
	SendComm.ComLenHH = 0;
	SendComm.ComLenLL = 1;
	SendComm.CommCode = CMD_SEND_VOLUME;
	SendComm.DataArea.Data[0] = Volume; // ������������
	
	if (NULL != g_pfSendCommand)
	{
	    g_pfSendCommand((void*)&SendComm, 5);
	}
}

//ֹͣ����빦��
void Codec_Stop(void)
{
	CommFrame SendComm;

	SendComm.Header = 0xFD;
	SendComm.ComLenHH = 0;
	SendComm.ComLenLL = 1;
	SendComm.CommCode = CMD_STOP_CODEC;
	
	if (NULL != g_pfSendCommand)
	{
	    g_pfSendCommand((void*)&SendComm, 4);
	}
}

//������ֽڴ�����
bool Codec_Byte_Proc(char ch)
{
    //������һ���ֽ����ݣ����������			
	switch (g_eRecvType)
	{
	    case eRecvCommon:
			if ( 0xFC == ch )	// һ֡����ʼ
			{
				ResetRecvBuf();
				g_eRecvType = eRecvFrameLenH;
				g_tu8RecvFrame[g_u16RecvBufIndex++] = ch;
			}
			break;
		
		case eRecvFrameLenH:				
			g_tu8RecvFrame[g_u16RecvBufIndex++] = ch;
			g_u16RecvFrameDataLen = (ch << 8);
			g_eRecvType = eRecvFrameLenL;				
			break;

		case eRecvFrameLenL:
			g_tu8RecvFrame[g_u16RecvBufIndex++] = ch;
			g_u16RecvFrameDataLen |= (ch & 0x00FF);
			g_u32RecvFrameLen = g_u16RecvFrameDataLen;

			if (g_u16RecvFrameDataLen > 66) // �֡Ϊ66
			{
			    g_u16RecvFrameDataLen = 66;
			}			
			break;

		case eRecvFrameCmd:
			g_eRecvType = eRecvFrameData;
		case eRecvFrameData:
			g_tu8RecvFrame[g_u16RecvBufIndex++] = ch;
			g_u16RecvFrameDataLen--;
			if ( 0 == g_u16RecvFrameDataLen )
			{
			    if (Frame_Proc())
				{
					return 1;
				}
				
				g_eRecvType = eRecvCommon;
			}
			break;

		default:
			break;
	}		

	return 0;
}

