#include "TcpProtocol.h"



TcpProtocol::TcpProtocol()
{
}

void TcpProtocol::RetrivingPrimariData(int **& matrix, int &n, int &m)
{
	ISocket *socket = new ISocket();
	char *msg=new char[5];
	int len = 5;
	if (serverIp != nullptr &&serverPort != nullptr)
	{
		socket->InitializateSocket(serverIp, serverPort);
		socket->SendData("get matrix dimensionss", 15);
		socket->SimpleReceiveData(msg, 5);
		n = atoi(msg);
		realloc_simple_buffer(msg, 5);
		socket->SendData("received first dimension", 30);
		socket->SimpleReceiveData(msg, 5);
		m = atoi(msg);
		realloc_simple_buffer(msg, n*m+1);
		socket->SendData("get matrix", 10);
		socket->ReceiveData(msg, n*m);
		socket->GracefulShutdown();
		msg[n*m] = NULL;
		int i = 0;
		int pozCol=0,pozLine = 0;
		matrix = new int*[n];
		for (int j = 0;j < n;j++)
		{
			matrix[j] = new int[m];
			for (int k = 0;k < m;k++)
				matrix[j][k] = 2;
		}
		len = strlen(msg);
		for (i = 0;i < len;i++)
		{
			if (msg[i] == '0')
				matrix[pozLine][pozCol] = 0;
			if (msg[i] == '1')
				matrix[pozLine][pozCol] = 1;
			if (msg[i] == '2')
				matrix[pozLine][pozCol] = 2;
			pozCol++;
			if (pozCol >= m)
			{
				pozCol = 0;
				pozLine++;
			}
		}
		delete socket;
	}

}

void TcpProtocol::SetServerConfiguration(char * ipAddr, char * port)
{
	if (serverIp != nullptr)
	{
		delete serverIp;
		serverIp = nullptr;
	}
	serverIp = _strdup(ipAddr);
	if (serverPort != nullptr)
	{
		delete serverPort;
		serverPort = nullptr;
	}
	serverPort = _strdup(port);
}

void TcpProtocol::SetPositions(char * xStart, char * yStart, char * xFinal, char * yFinal)
{
	ISocket *socket = new ISocket();
	char *msg = new char[5];
	if (serverIp != nullptr &&serverPort != nullptr)
	{
		socket->InitializateSocket(serverIp, serverPort);
		socket->SendData("sending positions", 16);
		socket->SimpleReceiveData(msg, 3);
		socket->SendData(xStart, strlen(xStart));
		socket->SimpleReceiveData(msg, 3);
		socket->SendData(yStart, strlen(yStart));
		socket->SimpleReceiveData(msg, 3);
		socket->SendData(xFinal, strlen(xFinal));
		socket->SimpleReceiveData(msg, 3);
		socket->SendData(yFinal, strlen(yFinal));
		socket->SimpleReceiveData(msg, 3);
		socket->GracefulShutdown();
		delete socket;
	}
}


TcpProtocol::~TcpProtocol()
{
}
