#include "PaqueteDatagrama.h"
#include "Solicitud.h"
#include "mensaje.h"
#include <iostream>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

Solicitud::Solicitud()
{
    socketLocal=new SocketDatagrama(0);
    printf("Socket creado con exito\n");
    socketLocal->setBroadcast();
}

char * Solicitud::doOperation(char *IP, int puerto, int operationId, char *arguments,int requestId){
    mensaje *msj=(mensaje*)malloc(sizeof(mensaje));
    
    msj->messageType=0;
    msj->requestId=requestId;
    //Identificador del mensaje
    strcpy(msj->IP,IP);
    msj->puerto=puerto;
    msj->operationId=operationId;
    
    //Identificador de la operación
    memcpy(msj->arguments, arguments,4000);

    PaqueteDatagrama paqueteDatagrama((char *)msj, sizeof(mensaje), (char *)IP, puerto);
    socketLocal->envia(paqueteDatagrama);

    PaqueteDatagrama paqueteRespuesta(sizeof(mensaje));
    socketLocal->recibeTimeout(paqueteRespuesta,1,0);
    
    mensaje *m = (mensaje*)malloc(sizeof(mensaje));
    memcpy(m, paqueteRespuesta.obtieneDatos(), paqueteRespuesta.obtieneLongitud());

    return paqueteRespuesta.obtieneDireccion();
}

Solicitud::~Solicitud(){
    socketLocal->unsetBroadcast();
    socketLocal->~SocketDatagrama();
}