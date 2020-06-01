#ifndef SOKCET_DATAGRAMA_H_
#define SOCKET_DATAGRAMA_H_

#include "PaqueteDatagrama.h"
#include <netdb.h>

class SocketDatagrama
{
    public:
        SocketDatagrama(int);
        ~SocketDatagrama();
        
        int recibe(PaqueteDatagrama &p);
        int envia(PaqueteDatagrama &p);
    private:
        struct sockaddr_in direccionLocal;
        struct sockaddr_in direccionForanea;
        int socketId;
};
#endif