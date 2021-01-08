#pragma once
#pragma pack(push,1)

enum MSG_TYPE {
	MT_SEARCH_SENDER_NAME = 0,	//局域网广播询问当前IP对应的计算机名称
	MT_ONLINE,					//广播通知上线
	MT_OFFLINE,					//广播通知下线
	MT_NORMAL_MESSAGE,			//普通广播消息
	MT_FILE_MESSAGE,			//发送文件广播消息
	MT_FILE_BODY,				//文件内容包
	MT_GET_FILE,				//获取文件
	
	//MSG_TYPE_ERROR  //出错类的消息类型
	ME_MISS_PACK = 128,			//丢失包

};
typedef struct _MsgHead {
	unsigned char msgType;			//通讯标识，定义数据包的基本性质
	unsigned int senderIP;			//消息发送者的IP
	unsigned char msgID[8];			//消息ID
	unsigned char timeStamp[4];		//时间戳
	unsigned int totalPack;			//总包数
	unsigned int curPack;			//当前包数
}MsgHead;

typedef struct _NetMessage {
	_NetMessage() {
		startTag = 0x5a;
		endTag = 0xa5;
		msgBody = nullptr;
		msgBodyLen = 0;
	}
	unsigned char startTag;	//消息开始标记	0x5a
	MsgHead	head;
	unsigned int msgBodyLen;//消息体长度
	unsigned char* msgBody;//消息体
	unsigned char mac[4];	//4字节校验(待实现，未校验)
	unsigned char endTag;	//消息结束标记 0xa5
}NetMessage;
#pragma pack(pop)