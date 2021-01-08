#include "UDP.h"
#include <process.h>
#pragma comment(lib,"ws2_32.lib")
#include <ws2tcpip.h>
const int UDP::MAX_SINGLE_PKG_LEN = 1300;

UDP::UDP(unsigned short port) {
	m_port = port;
	m_socketSrv = INVALID_SOCKET;
}
UDP::~UDP() {
	closesocket(m_socketSrv);
	WSACleanup();
}
int UDP::Init() {
	WSADATA wsd;
	int iRet = 0;

	// 初始化套接字动态库
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0) {
		iRet = WSAGetLastError();
		return iRet;
	}

	struct sockaddr_in srv;//本机地址相关结构体  

	srv.sin_family = AF_INET;
	srv.sin_port = htons(m_port); ///监听端口   
	srv.sin_addr.s_addr = INADDR_ANY; ///本机   
	m_socketSrv = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_socketSrv == INVALID_SOCKET) {
		WSACleanup();
		return -1;
	}
	if (bind(m_socketSrv, (struct sockaddr*) & srv, sizeof(srv)) == SOCKET_ERROR) {
		closesocket(m_socketSrv);
		WSACleanup();
		return -1;
	}

	//多网卡的情况下，不太好用这种方法获取本地ip 
	//char name[1024] = { 0 };
	//gethostname(name, sizeof(name));
	//PADDRINFOA pAddrInfo;

	//int rv = getaddrinfo(name, NULL, nullptr, &pAddrInfo);   //利用主机名称获取本地地址
	//if (rv != 0) {
	//	rv = 0;
	//}
	//char buff[100];
	//DWORD bufflen = 100;
	////将本地地址转换成字符串显示
	//for (; pAddrInfo != nullptr; pAddrInfo = pAddrInfo->ai_next) {
	//	struct sockaddr_in* pSockaddr = (sockaddr_in*)pAddrInfo->ai_addr;
	//	//char* pIP = inet_ntoa(pSockaddr->sin_addr);
	//	inet_ntop(AF_INET, &pSockaddr->sin_addr, buff, bufflen);
	//	rv = 0;
	//}

	return 0;
}
UINT __stdcall ThreadRecvMsg(LPVOID lpParam) {
	SOCKET socketSrv = (SOCKET)lpParam;
	char buffer[UDP::MAX_SINGLE_PKG_LEN] = { 0 };
	struct sockaddr_in fromAddr;//客户端地址相关结构体  
	int fromlen = sizeof(fromAddr);

	int iRet = recvfrom(socketSrv, buffer, UDP::MAX_SINGLE_PKG_LEN, 0, (sockaddr*)&fromAddr, &fromlen);
	if (SOCKET_ERROR == iRet)
	{
		closesocket(socketSrv);
		WSACleanup();
		return -1;
	}
	//未完待续
}

int UDP::Run() {
	unsigned int threadid = 0;
	_beginthreadex(NULL, 0, ThreadRecvMsg, (void*)m_socketSrv, 0, &threadid);
	return 0;
}

void UDP::SetCallbackFunc(void(*callback)(unsigned char* data, int& dataLen)) {
	m_callback = callback;
}
void UDP::CallHandleDataThread(unsigned char* data, int& dataLen) {
	unsigned int threadid = 0;
	//_beginthreadex(NULL, 0, m_callback, (void*)hwnd, 0, &threadid);
}