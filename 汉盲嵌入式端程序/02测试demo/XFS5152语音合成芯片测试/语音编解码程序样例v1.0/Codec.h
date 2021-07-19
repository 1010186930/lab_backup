#ifndef __CODEC_H__
#define __CODEC_H__

/* Save data callback type */
typedef bool (ivCBSaveData)(
	void*		pSrcBuffer,
	int			nBufferBytes
	);

/* Load data callback type */
typedef bool (ivCBLoadData)(
	void*		pDstBuffer,
	int* 	pnBufferBytes
	);

/* Save command callback type */
typedef bool (ivCBSendCommand)(
	void*		pSrcBuffer,
	int			nBufferBytes
	);

typedef enum
{
    Codec_encode,  // ¼������ģʽ
	Codec_decode   // ���벥��ģʽ
}CODECMODEID;

//¼�������ʣ�֧��8k��16k����
typedef enum
{
	SR_8000,
	SR_16000
}SAMPLERATEID;

//�����bitrate����
//����������ɵ͵��߹�6��
typedef enum
{
	BR_bitrate0,
	BR_bitrate1,
	BR_bitrate2,
	BR_bitrate3,
	BR_bitrate4,
	BR_bitrate5
}BITRATEID;

//�����volume����
typedef enum
{
	BR_volume0,
	BR_volume1,
	BR_volume2,
	BR_volume3,
	BR_volume4,
	BR_volume5,
	BR_volume6,
	BR_volume7,
	BR_volumeauto  // ������ʱ����
}VOLUMEID;

void Codec_Start(CODECMODEID CodecMode, SAMPLERATEID SampleRate, BITRATEID BitRate, VOLUMEID Volume,
        ivCBLoadData pfLoadData, ivCBSaveData pfSaveData, ivCBSendCommand pfSendCommand);
void Codec_Stop(void);
void Codec_SetVolume(VOLUMEID Volume);
bool Codec_Byte_Proc(char ch);

#endif
