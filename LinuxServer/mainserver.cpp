#include "mainserver.h"

MainServer::MainServer()
{
    serverSocket=new ISocket();
    CreateMatrix();
}
void MainServer::ConfigureSocket(char *ip, int port)
{
    if (port!=0)
        serverSocket->SetPort(port);
    serverSocket->SetIpAddr(ip);
    serverSocket->CreateSocket();
}
void MainServer::StartServer()
{
    if (serverSocket->IsSocketCreated())
    {
        while (1)
        {
           int descriptor= serverSocket->Accept(DEFAULT_CONEXIONS);
           char msg[50];
           Utilitis::nullBuffer(msg,50);
           read(descriptor,msg,50);
           switch (determinateCase(msg))
           {
               case 0:
           {
               transferMatrix(descriptor);
                break;
           }
           case 1:
           {
               GetSFpositions(descriptor);
               break;
           }
           default:
           {
               printf("%s\n","eroare de protocol:alegere inexistenta");
               break;
           }

           }
        }
    }
    else
        throw SOCKET_INITIALIZATION_FAILED;
}
MainServer::~MainServer()
{
    if (serverSocket!=nullptr)
    {
        delete serverSocket;
        serverSocket=nullptr;
    }
}
void MainServer::GetSFpositions(int socketDescriptor)
{
    char msg[5];
    write(socketDescriptor,"ok",3);
    read(socketDescriptor,msg,5);
    xStart=atoi(msg);
    write(socketDescriptor,"ok",3);
    read(socketDescriptor,msg,5);
    yStart=atoi(msg);
    write(socketDescriptor,"ok",3);
    read(socketDescriptor,msg,5);
    xFinal=atoi(msg);
    write(socketDescriptor,"ok",3);
    read(socketDescriptor,msg,5);
    yFinal=atoi(msg);
     write(socketDescriptor,"ok",3);
    printf("Graceful Shutdown:matrix transfered");
}

int MainServer::determinateCase(char *choise)
{
    if (strcmp(choise,"get matrix dimensionss")==0)
        return 0;
    if (strcmp(choise,"sending positions")==0)
        return 1;
    return 100;
}
char * MainServer::ConvertMatrixToString()
{
    char * buffer=new char [line*columns+1];
    int lim=line*columns;
    int k=0;
    for (int i=0;i<line;i++)
        for (int j=0;j<columns;j++)
        {
            buffer[k]=Utilitis::sint2char(matrix[i][j]);
            k++;
        }
    buffer[lim]=NULL;
    return buffer;
}

void MainServer::transferMatrix(int socketDescriptor)
{
    char *buf,msg[30];
    buf=Utilitis::int2char(this->line);
    write(socketDescriptor,buf,strlen(buf));
    read(socketDescriptor,msg,30);
    delete buf;
    buf=Utilitis::int2char(this->columns);
    write(socketDescriptor,buf,strlen(buf));
    read(socketDescriptor,msg,30);
    delete buf;
    buf=ConvertMatrixToString();
    write(socketDescriptor,buf,line*columns);
    read(socketDescriptor,msg,30);
    printf("Graceful Shutdown:matrix transfered");
    delete buf;
}
void MainServer::CreateMatrix()
{
    line=2;
    columns=3;
   matrix=new int*[2];
   matrix[0]=new int[3];
   matrix[1]=new int[3];
    matrix[0][0]=1;
    matrix[0][1]=1;
    matrix[0][2]=2;
    matrix[1][2]=0;
    matrix[1][1]=0;
    matrix[1][0]=1;
}
