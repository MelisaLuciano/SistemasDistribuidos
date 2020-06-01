#include "SocketDatagrama.h"
#include <iostream>
#include <string.h>
using namespace std;

int main(int argc, char const *argv[]) {
	
	if(argc<5){
        cout<<"Ejecute ingresando las direcciones ip y el numero de puerto"<<endl;
        return 0;
    }
    unsigned int num1[3], num2[3],num3[3], inicio=2, primero,segundo;
    unsigned int r1,r2,r3;
    char ip1[16],ip2[16],ip3[16];
	unsigned int n = 4294967291;
    //unsigned int n = 7296;
	primero=n/3;
    segundo=2*primero;
    
    num1[0]=n;
    num1[1]=inicio;
    num1[2]=primero;

    num2[0] = n;
    num2[1] = primero+1;
    num2[2] = segundo;

    num3[0] = n;
    num3[1] = segundo+1;
    num3[2] = n;

    strcpy(ip1,argv[1]);
    strcpy(ip2,argv[2]);
    strcpy(ip3,argv[3]);

    int puerto=atoi(argv[4]);
    SocketDatagrama cliente(0);
    printf("%s\n", "ENVIANDO PAQUETE...");

    PaqueteDatagrama paquete((char *)num1, 3*sizeof(int), (char *) ip1, puerto);
    printf("Mandando paquete a: %s:%d\n", paquete.obtieneDireccion(), paquete.obtienePuerto());
    cliente.envia(paquete);
    printf("%s\n", "PAQUETE ENVIADO");

	PaqueteDatagrama paquete2((char *)num2, 3*sizeof(int), (char *) ip2, puerto);
    printf("Mandando paquete a: %s:%d\n", paquete2.obtieneDireccion(), paquete2.obtienePuerto());
    cliente.envia(paquete2);
    printf("%s\n", "PAQUETE ENVIADO");

    PaqueteDatagrama paquete3((char *)num3, 3*sizeof(int), (char *) ip3, puerto);
    printf("Mandando paquete a: %s:%d\n", paquete3.obtieneDireccion(), paquete.obtienePuerto());
    cliente.envia(paquete3);
    printf("%s\n", "PAQUETE ENVIADO");

    PaqueteDatagrama respuesta1(sizeof(int));
    PaqueteDatagrama respuesta2(sizeof(int));
    PaqueteDatagrama respuesta3(sizeof(int));
    cliente.recibe(respuesta1);
    printf("Respuesta 1 recibida\n");
    cliente.recibe(respuesta2);
    printf("Respuesta 2 recibida\n");
    cliente.recibe(respuesta3);
    printf("Respuesta 3 recibida\n");
    memcpy(&r1,respuesta1.obtieneDatos(),sizeof(int));
    memcpy(&r2,respuesta2.obtieneDatos(),sizeof(int));
    memcpy(&r3,respuesta3.obtieneDatos(),sizeof(int));
    if(r1!=0 or r2!=0 or r3!=0){
    	cout<<"Es primo"<<endl;
    }
    else{
        cout<<"No es primo"<<endl;	
    }
    printf("%u %s, %u %s, %u %s\n", r1,respuesta1.obtieneDireccion(),r2,respuesta2.obtieneDireccion(),r3,respuesta3.obtieneDireccion());
    return 0;
}