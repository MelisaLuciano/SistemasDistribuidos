#include "Solicitud.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;
int nbytes;

char buffer[BUFSIZ];

int main(int argc, char *argv[]){
    if(argc!=6){
    	cout<<"Agregue: direccion_ip puerto archivo_original nuevo_nombre archivo_deseado"<<endl;
    	return 0;
    }
    Solicitud cliente1;
    cout<<"Se procedera a enviar el archivo..."<<endl;
    int a,b;
    int origen=open(argv[3],O_RDONLY);
    cliente1.doOperation(argv[1],atoi(argv[2]),ENVIAR,argv[4],argv[4],OPEN,0);
    while((nbytes=read(origen,buffer,sizeof(buffer)))>0){
        cliente1.doOperation(argv[1],atoi(argv[2]),ENVIAR,argv[4],buffer,WRITE,nbytes);
    }
    cliente1.doOperation(argv[1],atoi(argv[2]),ENVIAR,argv[4],buffer,CLOSE,0);
    close(origen);
    return 0;
}
