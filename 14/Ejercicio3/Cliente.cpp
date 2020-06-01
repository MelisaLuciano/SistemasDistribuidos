#include <iostream>
#include <string.h>
#include <cmath>
#include "gfx.h"
#include "Solicitud.h"
#include "mensaje.h"
#include <unistd.h>
#include <sys/time.h>
using namespace std;

int main(int argc, char *argv[]){
    if(argc<3)
    {
        cout<<"Ingrese direccion ip y puerto al servidor"<<endl;
        return 0;
    }
    Solicitud cliente;
    struct timeval tiempoInicio,tiempoFin,horaFin,modificar,valor;
    valor.tv_sec=7;valor.tv_usec=999999;
    int hora[2],contador=0;
	cout<<"Enviando paquete"<<endl;
	while(contador<10){
		gettimeofday(&tiempoInicio,NULL);
		memcpy(hora,cliente.doOperation(argv[1],atoi(argv[2]),1,(char*)"",1),2*sizeof(int));
		gettimeofday(&tiempoFin,NULL);
		if(((tiempoFin.tv_sec-tiempoInicio.tv_sec)/2)<valor.tv_sec){
			valor.tv_sec=(tiempoFin.tv_sec-tiempoInicio.tv_sec)/2;
			valor.tv_usec=(tiempoFin.tv_usec-tiempoInicio.tv_usec)/2;
		}
		horaFin.tv_sec=hora[0];
		horaFin.tv_usec=hora[1];
		contador++;
	}
	timeradd(&horaFin,&valor,&modificar);
	settimeofday(&modificar,NULL);
	cout<<"Reloj sincronizado"<<endl;
}