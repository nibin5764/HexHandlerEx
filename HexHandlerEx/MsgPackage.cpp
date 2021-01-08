#include "MsgPackage.h"
#include<memory>

MsgHead MsgPackage::tempHead = {0};

//将字节流解析成NetMessage 结构体
NetMessage* MsgPackage::ParseMsg(unsigned char* data, unsigned int dataLen) {
	if (data == nullptr || dataLen < sizeof(_NetMessage) - sizeof(unsigned char*)) {		//可能没有消息体
		return nullptr;
	}
	if (data[0] != 0x5a || data[dataLen - 1] != 0xa5) {
		return nullptr;
	}
	NetMessage* pmsg = new NetMessage();
	int pos = 1;
	memcpy(&pmsg->head, data + pos, sizeof(pmsg->head));
	pos += sizeof(MsgHead);
	memcpy(&pmsg->msgBodyLen, data + pos, sizeof(pmsg->msgBodyLen));
	pos += sizeof(pmsg->msgBodyLen);
	pmsg->msgBody = new unsigned char[pmsg->msgBodyLen + 1];
	memcpy(pmsg->msgBody, data + pos, pmsg->msgBodyLen);
	pmsg->msgBody[pmsg->msgBodyLen - 1] = 0;
	pos += pmsg->msgBodyLen;
	memcpy(pmsg->mac, data + pos, sizeof(pmsg->mac));
	
	/*
		此处应有mac校验
	*/
	return pmsg;
}

//用类型和数据生成用于发送的完整数据
void MsgPackage::GenMsg(unsigned char* OutData, unsigned int OurDataLen, MSG_TYPE type, unsigned char* data, unsigned int dataLen, int curPack , int totalPack ) {
	//memset(&tempHead, 0, sizeof(tempHead));
	//tempHead.msgType = type;
	//tempHead

}