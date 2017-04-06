#ifndef ISOCKET_H
#define ISOCKET_H
# include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
# include <iostream>
# include <string>
# include <unistd.h>
# include "utilitis.h"
# include "errors.h"
# define DEFAULT_PORT 20000
class ISocket
{
public:
    ISocket();
    void SetIpAddr (char *desired_ip);
    void SetPort (int desired_port);
    void CreateSocket ();
    int Accept (int nrConexiuni=10000);
    bool IsSocketCreated ();
    ~ISocket();
private:
    char* ipAddr=nullptr;
    int port=DEFAULT_PORT;
    int socketDescriptor=-1;
    struct sockaddr_in to;
    struct sockaddr_in from;
    socklen_t fromlen = 0;

};

#endif // ISOCKET_H
