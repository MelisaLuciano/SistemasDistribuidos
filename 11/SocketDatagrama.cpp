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
 int SocketDatagrama::recibe(PaqueteDatagrama & p){
   int i;
   unsigned int size = sizeof(direccionForanea);
   i=recvfrom(s,(char*)p.obtieneDatos(),p.obtieneLongitud(),0,(struct sockaddr *)&direccionForanea,&size);
   p.inicializaIP(inet_ntoa(direccionForanea.sin_addr));
   p.inicializaPuerto(ntohs(direccionForanea.sin_port));
   cout<<"Remitente: Puerto: "<<p.obtienePuerto()<<" Direccion IP: "<<p.obtieneDireccion()<<endl;
   return i;
 }
 //Envía un paquete tipo datagrama desde este socket
 int SocketDatagrama::envia(PaqueteDatagrama & p){
   int i;
   direccionForanea.sin_family = AF_INET;
   direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
   direccionForanea.sin_port=htons(p.obtienePuerto());
   i=sendto(s,p.obtieneDatos(), p.obtieneLongitud(),0,(struct sockaddr*)&direccionForanea,sizeof(direccionForanea));
   cout<<"Remitente: Puerto: "<<p.obtienePuerto()<<" Direccion IP: "<<p.obtieneDireccion()<<endl;
   return i;
}