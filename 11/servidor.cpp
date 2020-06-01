#include "SocketDatagrama.h"
#include<iostream>
#include<string.h>
using namespace std;

int main(int argc, char const *argv[]) {
    printf("%s\n", "SERVIDOR");
    SocketDatagrama cliente(7200);
    PaqueteDatagrama paquete(3*sizeof(int));
    PaqueteDatagrama respuesta(sizeof(int));
    unsigned int num=0;
    while(1) {
        unsigned int n[3];
        unsigned int i;

        printf("%s\n", "ESPERANDO...");
        cliente.recibe(paquete);
        printf("Mensaje de: %s:%d\n", paquete.obtieneDireccion(), paquete.obtienePuerto());
        memcpy(n, paquete.obtieneDatos(), 3*sizeof(int));
        printf("%u %u %u\n", n[0],n[1],n[2]);
        for(i=n[1];i<n[2];i++){
            if(n[0]%i==0){
                num=1;
                break;
            }
        }


        respuesta.inicializaPuerto(paquete.obtienePuerto());
        respuesta.inicializaIP(paquete.obtieneDireccion());
        respuesta.inicializaDatos((char *)&num);
        cout<<"ENVIANDO RESPUESTA"<<endl;
        cliente.envia(respuesta);
    }

    return 0;
}
