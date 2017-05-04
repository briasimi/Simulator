#pragma once
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
class ISocket
{
public:
	ISocket();
	int InitializateSocket(char *ip,char* DEFAULT_PORT);
	bool SendData(char *sendbuf, int buf_lenght);
	bool ReceiveData(char *&recvbuf,int recvbuflen);
	bool SimpleReceiveData(char *&recvbuf, int recvbuflen);
	void GracefulShutdown();
	void FreeSocket();
	~ISocket();
private:
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	int iResult;
	bool iShouldDelete = false;
};

