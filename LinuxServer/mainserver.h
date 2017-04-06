#ifndef MAINSERVER_H
#define MAINSERVER_H
# include "isocket.h"
# define DEFAULT_CONEXIONS 10000
class MainServer
{
public:
    MainServer();
    void ConfigureSocket(char *ip,int port=0);
    void StartServer();
    ~MainServer();


    //intern functions
private:
    ISocket *serverSocket=nullptr;
    int determinateCase (char *choise);
    void transferMatrix (int socketDescriptor);
    char* ConvertMatrixToString ();
    void GetSFpositions(int socketDescriptor);
    void CreateMatrix();
    //intern variables
private:
    int line=0;
    int columns=0;
    int **matrix=nullptr;
    int xStart=0,yStart=0,xFinal=0,yFinal=0;

};

#endif // MAINSERVER_H
