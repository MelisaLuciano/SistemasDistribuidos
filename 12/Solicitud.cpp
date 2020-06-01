#include "PaqueteDatagrama.h"
#include "Solicitud.h"
#include "Mensaje.h"
#include <iostream>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

Solicitud::Solicitud()
{
    socketlocal=new SocketDatagrama(0);
}

char * Solicitud::doOperation(char *IP, int puerto, int operationId, char *arguments){
    mensaje *msj=(mensaje*)malloc(sizeof(mensaje));
    
    msj->messageType=0;
    msj->requestId=0;
    //Identificador del mensaje
    strcpy(msj->IP,IP);
    msj->puerto=puerto;
    msj->operationId=operationId;
    
    //Identificador de la operación
    strcpy(msj->arguments, arguments);

    PaqueteDatagrama paqueteDatagrama((char *)msj, sizeof(mensaje), (char *)IP, puerto);
    socketlocal->envia(paqueteDatagrama);

    PaqueteDatagrama paqueteRespuesta(sizeof(mensaje));
    socketlocal->recibe(paqueteRespuesta);
    
    mensaje *m = (mensaje*)malloc(sizeof(mensaje));
    memcpy(m, paqueteRespuesta.obtieneDatos(), paqueteRespuesta.obtieneLongitud());

	return m->arguments;
}
