#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include<iostream>
using namespace std;

int main(){
	int puerto=7200;
	
	char ip[16];
	cin>>ip;
	cout<<ip<<endl;
	int dato[2];
	dato[0]=5;
	dato[1]=2;
	PaqueteDatagrama paquete((char*)dato,2*sizeof(int),(char*)ip,puerto);
	SocketDatagrama Socket(puerto);
	while(1){
		Socket.recibe(paquete);
		cout<<"1";
		Socket.envia(paquete);
	}
	Socket.~SocketDatagrama();
}