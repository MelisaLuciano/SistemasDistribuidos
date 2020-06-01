#include "SocketDatagrama.h"
#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {
	
	unsigned int num1[3], num2[3],num3[3], inicio=2, primero,segundo;
    unsigned int r1[1],r2[1],r3[1],primo;
    char ip1[16],ip2[16],ip3[16];
	unsigned int n = 429493;
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

    cout<<"Ingrese primera direccion IP:"<<endl;
    cin>>ip1;
    cout<<"Ingrese segunda direccion IP:"<<endl;
    cin>>ip2;
    cout<<"Ingrese tercera direccion IP:"<<endl;
    cin>>ip3;

    printf("%s\n", "CLIENTE");
    SocketDatagrama cliente(6700);
    printf("%s\n", "ENVIANDO PAQUETE...");

    PaqueteDatagrama paquete((char *)num1, 3*sizeof(unsigned int), (char *) ip1, 7200);
    printf("Mandando paquete a: %s:%d\n", paquete.obtieneDireccion(), paquete.obtienePuerto());
    cliente.envia(paquete);
    printf("%s\n", "PAQUETE ENVIADO");

	PaqueteDatagrama paquete2((char *)num2, 3*sizeof(unsigned int), (char *) ip2, 7200);
    printf("Mandando paquete a: %s:%d\n", paquete2.obtieneDireccion(), paquete2.obtienePuerto());
    cliente.envia(paquete2);
    printf("%s\n", "PAQUETE ENVIADO");

    PaqueteDatagrama paquete3((char *)num3, 3*sizeof(unsigned int), (char *) ip3, 7200);
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
    memcpy((char *)r1,respuesta1.obtieneDatos(),sizeof(unsigned int));
    memcpy((char *)r2,respuesta2.obtieneDatos(),sizeof(unsigned int));
    memcpy((char *)r3,respuesta3.obtieneDatos(),sizeof(unsigned int));
    if(r1[0]>r2[0] and r1[0]>r3[0]){
    	primo=r1[0];
    }
    else{
    	if(r2[0]>r1[0] and r2[0]>r3[0]){
    		primo=r2[0];
    	}
    	else{
    		primo=r3[0];
    	}
    }
    printf("%d %s, %d %s, %d %s\n", r1[0],respuesta1.obtieneDireccion(),r2[0],respuesta2.obtieneDireccion(),r3[0],respuesta3.obtieneDireccion());
    printf("El numero primo mayor es: %d\n",primo);
    return 0;
}