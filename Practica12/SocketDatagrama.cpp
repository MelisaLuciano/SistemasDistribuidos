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
   	char *num;
   	int i=0;
   	setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
   	while(i==0){
      	unsigned int size = sizeof(direccionForanea);
      	i=recvfrom(s,(char*)p.obtieneDatos(),p.obtieneLongitud(),0,(struct sockaddr *)&direccionForanea,&size);
     	 	if(i<0){
      		if(errno==EWOULDBLOCK){
      			cout<<"Tiempo de recepcion transcurrido"<<endl;
      		}
      		else{
      			cout<<"Error en recvfrom"<<endl;
      		}
      	}
      	else{
      		p.inicializaIP(inet_ntoa(direccionForanea.sin_addr));
      		p.inicializaPuerto(ntohs(direccionForanea.sin_port));
      	}
   	}
   	return i;
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