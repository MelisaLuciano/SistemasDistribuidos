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
   direccionForanea.sin_port=htons(puerto);
   bzero((char *)&direccionForanea, sizeof(direccionForanea));
   direccionForanea.sin_family = AF_INET;
   direccionForanea.sin_addr.s_addr = INADDR_ANY;
   direccionForanea.sin_port=htons(puerto);
   bind(s, (struct sockaddr *)&direccionForanea,sizeof(direccionForanea));
}
 SocketDatagrama::~SocketDatagrama(){
   close(s) ;
 }
 //Recibe un paquete tipo datagrama proveniente de este socket
 int SocketDatagrama::recibe(PaqueteDatagrama & p){
   direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
   socklen_t forlen=sizeof(direccionForanea);
   cout<<"Recibo datos de"<<p.obtieneDireccion()<<endl;
 	return recvfrom(s, &p, sizeof(p), 0, (struct sockaddr *)&direccionForanea, &forlen);
 }
 //Envía un paquete tipo datagrama desde este socket
 int SocketDatagrama::envia(PaqueteDatagrama & p){
   /*bzero((char *)&direccionForanea, sizeof(direccionForanea));
   direccionForanea.sin_family = AF_INET;
   direccionForanea.sin_addr.s_addr = INADDR_ANY;*/
   direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
   cout<<"Envio datos a"<<p.obtieneDireccion()<<endl;
   return sendto(s,&p, sizeof(p),0,(struct sockaddr*)&direccionForanea,sizeof(direccionForanea));
}