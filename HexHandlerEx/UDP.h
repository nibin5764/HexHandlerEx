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
	SOCKET m_socketSrv;	//���ڽ�������
	SOCKET m_socketClt;	//���ڷ�������
	void(*m_callback)(unsigned char* data, int& dataLen);
};

