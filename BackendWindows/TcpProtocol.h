#pragma once
# include "ISocket.h"
# include "SimpleUtilitis.h"
class TcpProtocol
{
public:
	TcpProtocol();
	void RetrivingPrimariData(int **&matrix, int &n, int &m);
	void SetServerConfiguration(char *ipAddr, char * port);
	void SetPositions(char *xStart, char *yStart, char*xFinal, char*yFinal);
	~TcpProtocol();
private:
	char *serverIp = nullptr;
	char *serverPort = nullptr;
};

