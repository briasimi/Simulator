#include "ISocket.h"



ISocket::ISocket()
{
}

int ISocket::InitializateSocket(char *ip, char* DEFAULT_PORT)
{
	iShouldDelete = true;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(ip, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL;ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}

		// Connect to server.
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		return 1;
	}
	return 0;
}

bool ISocket::SendData(char * sendbuf, int buf_lenght)
{
	int sendData = 0;
	while (sendData < buf_lenght)
	{
		iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return false;
		}
		sendData += iResult;
	}
	return true;
}

bool ISocket::ReceiveData(char *& recvbuf, int recvbuflen)
{
	char *buf = new char[recvbuflen];
	int poz = 0;
	do {

		iResult = recv(ConnectSocket, buf, recvbuflen, 0);
		if (iResult > 0)
		{
			printf("Bytes received: %d\n", iResult);
			strcpy(recvbuf + poz, buf);
			poz += iResult;
		}
		if (poz == recvbuflen)
			break;
		else if (iResult == 0)
		{
			printf("Connection closed\n");
			break;
		}
		else {
			printf("recv failed with error: %d\n", WSAGetLastError());
			return false;
		}

	} while (iResult > 0);
	delete buf;
	recvbuf[poz] = NULL;
	return true;
}

bool ISocket::SimpleReceiveData(char *& recvbuf, int recvbuflen)
{
	iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
	if (iResult > 0)
		return true;
	return false;
}

void ISocket::GracefulShutdown()
{
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
	}
}

void ISocket::FreeSocket()
{
	closesocket(ConnectSocket);
	WSACleanup();
}


ISocket::~ISocket()
{

}
