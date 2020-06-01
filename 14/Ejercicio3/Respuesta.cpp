#include "mensaje.h"
#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"
#include "Respuesta.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

Respuesta::Respuesta(int p1){
	socketLocal=new SocketDatagrama(p1);
}

struct mensaje *Respuesta::getRequets(){
	PaqueteDatagrama cliente(sizeof(mensaje));
	int i=socketLocal->recibe(cliente);
	mensaje *datos=(mensaje*)malloc(sizeof(mensaje));
	if(i>=0)
	{
		cout<<"Recibi paquete"<<endl;
		memcpy((char *)datos, cliente.obtieneDatos(), cliente.obtieneLongitud());
    	datos->puerto = cliente.obtienePuerto();
    	strcpy(datos->IP,cliente.obtieneDireccion());
    }
	return datos;
}

void Respuesta::sendReply(char * respuesta, char *ipCliente, int PuertoCliente){
	mensaje *mensaje1=(mensaje*)malloc(sizeof(mensaje));
	mensaje1->messageType=1;
	mensaje1->requestId=1;
	memcpy(mensaje1->IP,ipCliente,sizeof(ipCliente));
 	mensaje1->puerto=PuertoCliente;
 	mensaje1->operationId=1;
 	memcpy(mensaje1->arguments,respuesta,sizeof(respuesta));

 	PaqueteDatagrama paquete((char *)mensaje1,sizeof(mensaje),ipCliente,PuertoCliente);
 	socketLocal->envia(paquete);
}