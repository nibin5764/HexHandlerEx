#pragma once
#pragma pack(push,1)

enum MSG_TYPE {
	MT_SEARCH_SENDER_NAME = 0,	//�������㲥ѯ�ʵ�ǰIP��Ӧ�ļ��������
	MT_ONLINE,					//�㲥֪ͨ����
	MT_OFFLINE,					//�㲥֪ͨ����
	MT_NORMAL_MESSAGE,			//��ͨ�㲥��Ϣ
	MT_FILE_MESSAGE,			//�����ļ��㲥��Ϣ
	MT_FILE_BODY,				//�ļ����ݰ�
	MT_GET_FILE,				//��ȡ�ļ�
	
	//MSG_TYPE_ERROR  //���������Ϣ����
	ME_MISS_PACK = 128,			//��ʧ��

};
typedef struct _MsgHead {
	unsigned char msgType;			//ͨѶ��ʶ���������ݰ��Ļ�������
	unsigned int senderIP;			//��Ϣ�����ߵ�IP
	unsigned char msgID[8];			//��ϢID
	unsigned char timeStamp[4];		//ʱ���
	unsigned int totalPack;			//�ܰ���
	unsigned int curPack;			//��ǰ����
}MsgHead;

typedef struct _NetMessage {
	_NetMessage() {
		startTag = 0x5a;
		endTag = 0xa5;
		msgBody = nullptr;
		msgBodyLen = 0;
	}
	unsigned char startTag;	//��Ϣ��ʼ���	0x5a
	MsgHead	head;
	unsigned int msgBodyLen;//��Ϣ�峤��
	unsigned char* msgBody;//��Ϣ��
	unsigned char mac[4];	//4�ֽ�У��(��ʵ�֣�δУ��)
	unsigned char endTag;	//��Ϣ������� 0xa5
}NetMessage;
#pragma pack(pop)