#ifndef _CSK4002_H
#define _CSK4002_H
/****************************************************************************

* Copyright (C), 2021-2022,֮��ʵ����

* �ļ���: CSK4002.h

* ���ݼ�����Ӣ��ѧϰ��Ver1.0.0.20210516_a��CSK4002�����ϳ�оƬ�ĺ궨��

*

* �ļ���ʷ��

* �汾�� ���� ���� ˵��

* 1.0.0.20210516_a 2021-05-17 �¿��� �������ļ�

*/

#define COMMON_FRAME_LENGTH		4


/* CSK4002������֡ [���] */

#define FLAG		0XFD



/* CSK4002���´�����֡ [ϵͳ������] */
typedef enum {
	QUERY=		0X21,
	SLEEP=		0X88,
	AWAKEN=		0XFF
} SYSTEM_COMMAND;




/* CSK4002���´�����֡ [����������] */

typedef enum {
	START=		0X01,
	STOP=		0X02,
	PAUSE=		0x03,
	CONTINUE=	0X04,
	CACHE=		0X31,
	CPLAY=		0X32,
} CONTROL_COMMAND;





/* CSK4002��ʼ�����еĴ���ҳ [PAGE] */

typedef enum {
	GB2312=		0X00,
	GBK=		0X01,
	BIG5=		0X02,
	UTF16LE=	0X03,
	UTF8=		0X04
} PAGE;

/* CSK4002ͨ��״̬������״̬ [STA] */
typedef enum {
	UNKNOWN_STA=			0X00,
	SEND_CORRET=			0X41,
	SEND_COMMAND_ERROE=		0X45,
	SEND_DATA_INCOMPLETE=	0x46,
	SEND_FLAG_ERROR=		0X47,
	CSK_INIT_OK=			0X4A,
	CSK_BUSY=				0X4E,
	CSK_IDLE=				0X4F
} STA;
extern u8 CSK4002_STA;
void CSK4002_QueryState(void);
void CSK4002_Start(CONTROL_COMMAND command,PAGE page,u8* Inputbuf);


#endif
