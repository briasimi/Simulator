#include "utilitis.h"

Utilitis::Utilitis()
{

}
char* Utilitis::my_strdup(char*buffer)
{
    int len=strlen(buffer);
    char *newBuffer=new char[len+1];
    if (!newBuffer)
        return nullptr;
    memcpy(newBuffer,buffer,len+1);
}
char* Utilitis::clear_and_realoc(char *buffer, int size)
{
    if (buffer!=nullptr && buffer!=NULL)
    {
        delete buffer;
        buffer=new char[size];
    }
    else
        buffer=new char[size];
    return buffer;
}
void Utilitis::nullBuffer(char *buffer, int size)
{
    for (int i=0;i<size;i++)
        buffer[i]=NULL;
}

char *Utilitis::read_file(char *sir)
{

        ifstream file;
        file.open(sir, std::istream::in | std::ios::binary);
        std::streampos fsize = 0;
        fsize = file.tellg();
        file.seekg(0, std::ios::end);
        fsize = file.tellg() - fsize;
        file.close();
        int n = fsize;
        file.open(sir, istream::in | ios::binary);
        std::cout << n << " " << endl;
        int z = 0;
        char *p = new  char[n + 1];
        for (int i = 0;i < n;i++)
        {
        char ch;
        file.get(ch);
        p[i] = ch;
        }
        p[n]=NULL;
        file.close();
        return p;
}
char *Utilitis::int2char(int atom)
{
    char buf[10];
    sprintf(buf,"%d",atom);
    char *aux=Utilitis::my_strdup(buf);
    return aux;
}
char Utilitis::sint2char(int character)
{
    if (character==1)
        return '1';
    if (character==2)
        return '2';
    return '0';
}
