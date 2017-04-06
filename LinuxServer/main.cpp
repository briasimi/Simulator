#include <QCoreApplication>
# include "mainserver.h"

int main(int argc, char *argv[])
{
    /*QCoreApplication a(argc, argv);

    return a.exec();*/
    MainServer a;
    a.ConfigureSocket("192.168.0.92",20000);
    a.StartServer();
}
