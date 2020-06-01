#include "Respuesta.h" 
#include "string.h"
#include <iostream>
#include <stdlib.h>

using namespace std;


Respuesta::Respuesta(int puertoServidor)
{
    socketlocal = new SocketDatagrama(puertoServidor);
}
struct mensaje * Respuesta::getRequest(void){
    PaqueteDatagrama paqueteRecibido(sizeof(mensaje));
    socketlocal->recibe(paqueteRecibido);
    
    mensaje *m = (mensaje*)malloc(sizeof(mensaje));

    memcpy(m, paqueteRecibido.obtieneDatos(), paqueteRecibido.obtieneLongitud());
    m->puerto = paqueteRecibido.obtienePuerto();
    strcpy(m->IP,paqueteRecibido.obtieneDireccion());

    return m;
}
void Respuesta::sendReply(char *respuesta, char *ipCliente, int puertoCliente, int request,char *data)
{
    mensaje *msj = (mensaje*)malloc(sizeof(mensaje));
    msj->messageType = 1;
    msj->requestId = request;
    msj->operationId = 1;
    msj->puerto = puertoCliente;
    strcpy(msj->data,data);

    strcpy(msj->IP, ipCliente);
    memcpy(msj->arguments, respuesta,sizeof(char));

    PaqueteDatagrama paqueteReply((char *) msj, sizeof(mensaje), (char *)ipCliente, puertoCliente);
    socketlocal->envia(paqueteReply);
}