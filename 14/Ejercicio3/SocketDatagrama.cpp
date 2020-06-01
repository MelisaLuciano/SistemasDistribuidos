#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include "SocketDatagrama.h"
#include "PaqueteDatagrama.h"
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <errno.h>

using namespace std;

SocketDatagrama::SocketDatagrama(int puerto){
   s = socket(AF_INET, SOCK_DGRAM, 0);
   bzero((char *)&direccionLocal, sizeof(direccionLocal));
   direccionLocal.sin_family = AF_INET;
   //direccionLocal.sin_addr.s_addr = inet_addr("10.100.76.249");
   direccionLocal.sin_addr.s_addr = INADDR_ANY;
   direccionLocal.sin_port = htons(puerto);
   bind(s, (struct sockaddr *)&direccionLocal,sizeof(direccionLocal));
}
 SocketDatagrama::~SocketDatagrama(){
   close(s) ;
 }
 //Recibe un paquete tipo datagrama proveniente de este socket
 int SocketDatagrama::recibeTimeout(PaqueteDatagrama & p,time_t segundos,suseconds_t microsegundos){
   	struct timeval timeout;
	   timeout.tv_sec = segundos;
	   timeout.tv_usec = microsegundos;
   	int i=0;
   	setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
   	unsigned int size = sizeof(direccionForanea);
   	i=recvfrom(s,(char*)p.obtieneDatos(),p.obtieneLongitud(),0,(struct sockaddr *)&direccionForanea,&size);
  	 	if(i<0){
   		if(errno==EWOULDBLOCK){
   			cout<<"Tiempo de recepcion transcurrido "<<i<<endl;
   		}
   		else{
   			cout<<"Error en recvfrom"<<endl;
   		}
   	}
   	else{
   		p.inicializaIP(inet_ntoa(direccionForanea.sin_addr));
   		p.inicializaPuerto(ntohs(direccionForanea.sin_port));
   	}
   	return i;
 }

int SocketDatagrama::recibe(PaqueteDatagrama &paquete)
{
    unsigned int clilen = sizeof(direccionForanea);
    char * aux = new char[paquete.obtieneLongitud()];

    int r = recvfrom(s, aux, paquete.obtieneLongitud(), 0, 
            (struct sockaddr *)&direccionForanea, &clilen);
    
    printf("Remitente: Puerto: %d Direccion IP: %s \n",
        ntohs(((struct sockaddr_in)direccionForanea).sin_port),
        inet_ntoa(((struct sockaddr_in)direccionForanea).sin_addr));

    paquete.inicializaIP(inet_ntoa(((struct sockaddr_in)direccionForanea).sin_addr));
    paquete.inicializaPuerto(ntohs(((struct sockaddr_in)direccionForanea).sin_port));
    paquete.inicializaDatos(aux);

    return r;
}
 //Envía un paquete tipo datagrama desde este socket
int SocketDatagrama::envia(PaqueteDatagrama & p){
   int i;
   direccionForanea.sin_family = AF_INET;
   direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
   direccionForanea.sin_port=htons(p.obtienePuerto());
   i=sendto(s,p.obtieneDatos(), p.obtieneLongitud(),0,(struct sockaddr*)&direccionForanea,sizeof(direccionForanea));
   return i;
}