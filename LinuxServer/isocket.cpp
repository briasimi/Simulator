#include "isocket.h"

ISocket::ISocket()
{
    fromlen=sizeof (from);
}
void ISocket::SetIpAddr(char *desired_ip)
{
    if (this->ipAddr!=nullptr)
    {
        delete ipAddr;
        ipAddr=nullptr;
    }
    if (desired_ip!=nullptr)
    {
        ipAddr=Utilitis::my_strdup(desired_ip);
    }
}
void ISocket::SetPort(int desired_port)
{
    this->port=desired_port;
}
void ISocket::CreateSocket()
{
    this->socketDescriptor=socket(AF_INET,SOCK_STREAM,0);
    if (this->socketDescriptor<0)
        throw SOCKET_FUNCT_FAILED;
    to.sin_family=AF_INET;
    to.sin_port=htons(this->port);
    inet_aton(this->ipAddr,&to.sin_addr);
    int yes=1;
    setsockopt(socketDescriptor,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes));
       // setsockopt(sockDescriptor,SOL_SOCKET,SO_REUSEPORT,&yes,sizeof(yes));
        //int x=bind(this->sockDescriptor,(sockaddr *)&to,sizeof(to));
    if (bind(this->socketDescriptor,(sockaddr *)&to,sizeof(to))<0)
        throw BIND_FUNCT_FAILED;

}
int ISocket::Accept(int nrConexiuni)
{
    int newsock;
    //listen(this->sockDescriptor,1000);
    if(listen(this->socketDescriptor,nrConexiuni))
        throw LISTEN_FUNCT_FAILED;
    newsock=accept(this->socketDescriptor,(struct sockaddr *)&from,&fromlen);
    if (newsock==-1)
        throw ACCEPT_FUNCT_FAILED;
    return newsock;
}
bool ISocket::IsSocketCreated()
{
    if (socketDescriptor<0)
        return false;
    else
        return true;
}
ISocket::~ISocket()
{
    if (this->ipAddr!=nullptr)
    {
        delete ipAddr;
        ipAddr=nullptr;
    }
    /*if (socketDescriptor!=-1)
    {
        free(to);
    }*/
}
