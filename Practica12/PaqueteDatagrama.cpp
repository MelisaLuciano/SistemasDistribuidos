#include "PaqueteDatagrama.h"
#include "mensaje.h"
#include<string.h>

PaqueteDatagrama::PaqueteDatagrama(char *dato,unsigned int longi,char *direccion,int pto){
	datos=new mensaje;
	memcpy(datos,dato,longi);
	longitud=longi;
	strcpy(ip,direccion);
	puerto=pto;
}

PaqueteDatagrama::PaqueteDatagrama(unsigned int longi){
	datos=new mensaje;
	longitud=longi;
}

char *PaqueteDatagrama::obtieneDireccion(){
	return ip;
}

unsigned int PaqueteDatagrama::obtieneLongitud(){
	return longitud;
}

int PaqueteDatagrama::obtienePuerto(){
	return puerto;
}

mensaje *PaqueteDatagrama::obtieneDatos(){
	return datos;
}

void PaqueteDatagrama::inicializaPuerto(int pto){
	puerto=pto;
}

void PaqueteDatagrama::inicializaIP(char *direccion){
	strcpy(ip,direccion);
}

void PaqueteDatagrama::inicializaDatos(mensaje *dato){
	memcpy(datos,dato,longitud);
}

PaqueteDatagrama::~PaqueteDatagrama(){
	delete[] datos;
}