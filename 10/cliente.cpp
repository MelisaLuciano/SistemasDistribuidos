#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <strings.h>
#include<iostream>
using namespace std;

int main(){
	int puerto=7200;
	int dato[2];
	dato[0]=5;
	dato[1]=2;
	char ip[16];
	cout<<"Ingrese la ip del servidor"<<endl;
	cin>>ip;
	PaqueteDatagrama paquete((char*)dato,2*sizeof(int),(char*)ip,puerto);
	SocketDatagrama Socket(puerto);
	int enviar=Socket.envia(paquete);
	int recibir=Socket.recibe(paquete);
	cout<<enviar<<" "<<recibir<<endl;
	Socket.~SocketDatagrama();
}