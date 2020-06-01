#include <thread>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"
using namespace std;

SocketDatagrama* sock=new SocketDatagrama(0);

void Enviar(){
	char ip[16];
	int dato[2];
	dato[0]=1;
	dato[1]=1;
	for(int i=50;i<96;i++){
		for(int j=1;j<255;j++){
			strcpy(ip,"");
			sprintf(ip,"10.100.%d.%d",i,j);
			PaqueteDatagrama paquete((char*)dato,2*sizeof(int),ip,7200);
			sock->envia(paquete);
			usleep(5000);
		}
	}
	cout<<"Termine de enviar peticiones"<<endl;
}

void Recibir(){
	PaqueteDatagrama paquete(sizeof(int));
	while(1){
		sock->recibe(paquete);
	}
}

int main(int argc, char *argv[]){
	thread th1(Enviar),th2(Recibir);
	th1.join();
	th2.join();
}