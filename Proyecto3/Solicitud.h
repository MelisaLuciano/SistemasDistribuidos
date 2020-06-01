#define OBTENER 1
#define ENVIAR 2
#define OPEN 1
#define READ 2
#define WRITE 3
#define CLOSE 4
#ifndef Solicitud_h_
#define Solicitud_h_

#include "SocketDatagrama.h"

class Solicitud{
    public:
        Solicitud();
        char * doOperation(char *IP, int puerto, int operationId, char *arguments, char *datos,int op,int size);
    private:
        SocketDatagrama *socketlocal;
};

#endif