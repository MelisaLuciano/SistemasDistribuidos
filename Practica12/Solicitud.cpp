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

char * Solicitud::doOperation(char *IP, int puerto, int operationId, char *arguments){
    mensaje *msj=(mensaje*)malloc(sizeof(mensaje));
    
    msj->messageType=0;
    msj->requestId=0;
    //Identificador del mensaje
    strcpy(msj->IP,IP);
    msj->puerto=puerto;
    msj->operationId=operationId;
    
    //Identificador de la operación
    strcpy((char*)msj->arguments, arguments);

    PaqueteDatagrama paqueteDatagrama((char *)msj, sizeof(mensaje), (char *)IP, puerto);
    PaqueteDatagrama paqueteRespuesta(sizeof(mensaje));

    int recepcionStatus = 0;
    bool recibiRespuesta = false;
    for(int i = 0; i<7; i++)
    {
        socketLocal->envia(paqueteDatagrama);        
        recepcionStatus = socketLocal->recibeTimeout(paqueteRespuesta, 10,0);
        if(recepcionStatus > 0){
            cout << "Recibí respuesta del servidor" << endl;
            recibiRespuesta = true;
            break;
        }
    }
    if(!recibiRespuesta){
        cout << "El servidor no esta disponible" << endl;
    }
    
    mensaje *m = (mensaje*)malloc(sizeof(mensaje));
    memcpy((char *)m, paqueteRespuesta.obtieneDatos(), paqueteRespuesta.obtieneLongitud());

	return m->arguments;
}
