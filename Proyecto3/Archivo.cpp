#include "Archivo.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

Archivo::Archivo(){
	origen=-1;
	destino=-1;
}

void Archivo::ObtenerArchivoOrigen(char nombre){
	origen=open(nombre,O_RDONLY);
	if(origen==-1){
		printf("Error\n");
		exit(-1);
	}
}

void Archivo::CrearArchivoDestino(char nombre){
	destino=open(nombre,O_WRONLY|O_TRUNC|O_CREAT,0666);
	if(destino==-1){
		printf("Error\n");
		exit(-1);
	}
}

void Archivo::CopiarArchivo(){
	while((nbytes=read(origen,buffer,sizeof(buffer)))>0){
		write(destino,buffer,nbytes);
	}
}

void Archivo::CerrarArchivo()
{
	close(destino);
	close(origen);
}

void  Archivo::ActualizarBuffer(char datos){
	memcpy(buffer,datos,sizeof(datos));
}