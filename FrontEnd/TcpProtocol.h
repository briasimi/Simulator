#pragma once
# include <vector>
# include "ISocket.h"
# include "SimpleUtilitis.h"
# include "Lista.h"

class TcpProtocol
{
public:
	TcpProtocol();
	Lista * RetrivingPrimariData();
	void SetServerConfiguration(char *ipAddr, char * port);
	void SetPositions(char *xStart, char *yStart, char*xFinal, char*yFinal);
	void GetCarPositions(char *tip, char *secondmessage);
	void SendPositions(char *positions);
	void RequestSpecificPositions(char *specificCarsPositions);

	//get map
	char * GetMap(char *map);
	~TcpProtocol();
private:
	char *serverIp = nullptr;
	char *serverPort = nullptr;

private:
	streetTypes GetStreetsTypes(int x);
	std::vector <Point *> CarPositions;
};

