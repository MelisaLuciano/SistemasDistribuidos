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
    PaqueteDatagrama paqueteRespuesta(sizeof(mensaje));

    int recepcionStatus = 0;
    bool recibiRespuesta = false;
    for(int i = 0; i<1; i++)
    {
        socketLocal->envia(paqueteDatagrama);
        recepcionStatus = socketLocal->recibeTimeout(paqueteRespuesta, 0,10000);
        if(recepcionStatus > 0){
            mensaje *resp=(mensaje*)malloc(sizeof(mensaje));
            memcpy(resp,paqueteRespuesta.obtieneDatos(),paqueteRespuesta.obtieneLongitud());
            cout << "Recibí respuesta del servidor "<<paqueteRespuesta.obtieneDireccion() << endl;
            recibiRespuesta = true;
                break;
        }
    }
    if(!recibiRespuesta){
        return (char*)"";
    }
    
    mensaje *m = (mensaje*)malloc(sizeof(mensaje));
    memcpy(m, paqueteRespuesta.obtieneDatos(), paqueteRespuesta.obtieneLongitud());

	return m->arguments;
}
