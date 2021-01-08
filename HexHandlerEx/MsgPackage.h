#pragma once
#include"MsgDef.h"
class MsgPackage {
private:
	static MsgHead tempHead;	
public:
	//将字节流解析成NetMessage 结构体
	static NetMessage* ParseMsg(unsigned char* data, unsigned int dataLen);

	//用类型和数据生成用于发送的完整数据
	static void GenMsg(unsigned char* OutData, unsigned int OurDataLen, MSG_TYPE type, unsigned char* data, unsigned int dataLen ,int curPack = 0,int totalPack = 0);

};

