#ifndef SOLICITUD_DATAGRAMA_H_
#define SOLICITUD_DATAGRAMA_H_

#include "SocketDatagrama.h"
#include "Mensaje.h"

class Respuesta{
    public:
        Respuesta(int puertoServidor);
        struct mensaje *getRequest(void);
        void sendReply(char *respuesta, char *ipCliente, int puertoCliente);
    private:
        SocketDatagrama *socketlocal;
};
#endif