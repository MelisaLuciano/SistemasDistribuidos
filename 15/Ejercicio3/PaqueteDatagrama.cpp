#include "PaqueteDatagrama.h"
#include<string.h>

PaqueteDatagrama::PaqueteDatagrama(char *dato,unsigned int longi,char *direccion,int pto){
	datos=new char[longi];
	memcpy(datos,dato,longi);
	longitud=longi;
	strcpy(ip,direccion);
	puerto=pto;
}

PaqueteDatagrama::PaqueteDatagrama(unsigned int longi){
	datos=new char[longi];
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

char *PaqueteDatagrama::obtieneDatos(){
	return datos;
}

void PaqueteDatagrama::inicializaPuerto(int pto){
	puerto=pto;
}

void PaqueteDatagrama::inicializaIP(char *direccion){
	strcpy(ip,direccion);
}

void PaqueteDatagrama::inicializaDatos(char *dato){
	memcpy(datos,dato,longitud);
}

PaqueteDatagrama::~PaqueteDatagrama(){
	delete[] datos;
}