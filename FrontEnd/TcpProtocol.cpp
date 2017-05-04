#include "TcpProtocol.h"



TcpProtocol::TcpProtocol()
{
}

Lista* TcpProtocol::RetrivingPrimariData()
{
	ISocket *socket = new ISocket();
	Lista *list = new Lista();
	char *msg=new char[1001];
	char *leng=new char[10];
	int len = 5;
	if (serverIp != nullptr &&serverPort != nullptr)
	{
		socket->InitializateSocket(serverIp, serverPort);
		socket->SendData("get matrix dimensionss", 15);
		socket->SimpleReceiveData(leng, 10);
		len = atoi(leng);
		/*socket->SendData("ready to get points", 15);
		socket->SimpleReceiveData(leng, 10);*/
		socket->SendData("ready to get points", 15);
		socket->ReceiveData(msg, len);
		msg[len] = NULL;
		socket->GracefulShutdown();
		msg[1000] = NULL;
		char *token = strtok(msg, " ");
		int points[4], k = 0;
		while (token != NULL)
		{
			if (k == 4)
			{
				list->push_back(points[0], points[1], points[2], points[3], GetStreetsTypes(atoi(token)));
				k = -1;
			}
			else
			{
				points[k] = atoi(token);
			}
			k++;
			token = strtok(NULL, " ");
		}
		//deleteTokendeBuffersEx(msg, 1001);
		delete msg;
		delete leng;
		delete socket;
	}
	return list;
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

void TcpProtocol::GetCarPositions(char *tip,char *secondmessage)
{
	ISocket *socket = new ISocket();
	char *msg = new char[501];
	int len;
	char *leng = new char[5];
	if (serverIp != nullptr &&serverPort != nullptr)
	{
		socket->InitializateSocket(serverIp, serverPort);
		socket->SendData(tip, 25);
		socket->SimpleReceiveData(leng, 10);
		len = atoi(leng);
		/*socket->SendData("ready to get points", 15);
		socket->SimpleReceiveData(leng, 10);*/
		socket->SendData(secondmessage,strlen(secondmessage)+1);
		socket->ReceiveData(msg, len);
		msg[len] = NULL;
		socket->GracefulShutdown();
		msg[1000] = NULL;
		char *token = strtok(msg, " ");
		int points[2], k = 0;
		Point *point;
		while (token != NULL)
		{
			if (k == 2)
			{
				point = new Point();
				point->x = points[0];
				point->y = points[1];
				point->tag = atoi(token);
				CarPositions.push_back(point);
				point = nullptr;
				k = -1;
			}
			else
			{
				points[k] = atoi(token);
			}
			k++;
			token = strtok(NULL, " ");
		}
	}
	delete msg;
	delete leng;
	delete socket;
}

void TcpProtocol::SendPositions(char * positions)
{
	ISocket *socket = new ISocket();
	char *msg = new char[5];
	if (serverIp != nullptr &&serverPort != nullptr)
	{
		socket->SendData("sendig car pos", 15);
		socket->SimpleReceiveData(msg, 5);
		socket->SendData(positions, strlen(positions) + 1);
		
	}
	delete socket;
	delete msg;
}

void TcpProtocol::RequestSpecificPositions(char * specificCarsPositions)
{
	GetCarPositions("specific cars positions",specificCarsPositions);
}


char * TcpProtocol::GetMap(char * map)
{
	ISocket *socket = new ISocket();
	char *msg = new char[15];
	char *leng;
	if (serverIp != nullptr &&serverPort != nullptr)
	{
		socket->InitializateSocket(serverIp, serverPort);
		socket->SendData("read map", 16);
		socket->SimpleReceiveData(msg, 10);
		int len = atoi(msg);
		leng = new char[len+1];
		socket->SendData("map1", 4);
		socket->SimpleReceiveData(leng, len);
		socket->GracefulShutdown();
	}
	delete msg;
	return leng;
	return nullptr;
}

TcpProtocol::~TcpProtocol()
{
}

streetTypes TcpProtocol::GetStreetsTypes(int x)
{
	switch (x)
	{
	case 0:
		return singleDotted;
	case 1:
		return singleContinuous;
	case 2:
		return doubleDotted;
	case 3:
		return doubleContinuous;
	default:
		return singleDotted;
	}
}
