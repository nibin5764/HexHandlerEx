#pragma once
#include"MsgDef.h"
class MsgPackage {
private:
	static MsgHead tempHead;	
public:
	//���ֽ���������NetMessage �ṹ��
	static NetMessage* ParseMsg(unsigned char* data, unsigned int dataLen);

	//�����ͺ������������ڷ��͵���������
	static void GenMsg(unsigned char* OutData, unsigned int OurDataLen, MSG_TYPE type, unsigned char* data, unsigned int dataLen ,int curPack = 0,int totalPack = 0);

};

