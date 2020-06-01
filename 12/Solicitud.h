#ifndef SOLICITUD_DATAGRAMA_H_
#define SOLICITUD_DATAGRAMA_H_

#include "SocketDatagrama.h"

class Solicitud{
    public:
        Solicitud();
        char * doOperation(char *IP, int puerto, int operationId, char *arguments);
    private:
        SocketDatagrama *socketlocal;
};

#endif