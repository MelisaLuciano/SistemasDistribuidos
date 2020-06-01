#define OBTENER 1
#define ENVIAR 2
#define OPEN 1
#define READ 2
#define WRITE 3
#define CLOSE 4
#ifndef SOLICITUD_DATAGRAMA_H_
#define SOLICITUD_DATAGRAMA_H_

#include "SocketDatagrama.h"
#include "Mensaje.h"

class Respuesta{
    public:
        Respuesta(int puertoServidor);
        struct mensaje *getRequest(void);
        void sendReply(char *respuesta, char *ipCliente, int puertoCliente, int request, char *data);
    private:
        SocketDatagrama *socketlocal;
};
#endif