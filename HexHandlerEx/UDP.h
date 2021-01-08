#pragma once
#include <winsock2.h>
class UDP
{
public:
	const static int MAX_SINGLE_PKG_LEN;
public:
	UDP(unsigned short port);
	~UDP();
	int Init();
	int Run();
	void SetCallbackFunc(void(*callback)(unsigned char* data ,int& dataLen ));
private:

	void CallHandleDataThread(unsigned char* data, int& dataLen);

	unsigned short m_port;
	SOCKET m_socketSrv;	//用于接收数据
	SOCKET m_socketClt;	//用于发送数据
	void(*m_callback)(unsigned char* data, int& dataLen);
};

