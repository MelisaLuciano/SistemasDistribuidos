#include <iostream>
#include <string.h>
#include "Solicitud.h"
#include "mensaje.h"
#include <unistd.h>
#include <sys/time.h>
using namespace std;

int main(int argc, char *argv[]){
    if(argc<2)
    {
        cout<<"Ingrese direccion ip broadcast"<<endl;
        return 0;
    }
	int puerto=7200;
	int dato[2];
	dato[0]=5;
	dato[1]=2;
	char respuesta[16];
	Solicitud cliente;
	while(1){
		memcpy(respuesta,cliente.doOperation(argv[1],7200,1,(char*)"",1),16*sizeof(char));
		sleep(1);
		cout<<respuesta<<endl;
	}
}