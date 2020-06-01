#include "SocketDatagrama.h"

int main(int argc, char const *argv[]) {
    printf("%s\n", "SERVIDOR");
    SocketDatagrama cliente(710);
    PaqueteDatagrama paquete(3*sizeof(unsigned int));
    PaqueteDatagrama respuesta(sizeof(unsigned int));
    unsigned int num=0;
    while(1) {
        unsigned int n[3];
        unsigned int i;

        printf("%s\n", "ESPERANDO...");
        cliente.recibe(paquete);
        printf("Mensaje de: %s:%d\n", paquete.obtieneDireccion(), paquete.obtienePuerto());
        memcpy((char *)n, paquete.obtieneDatos(), 3*sizeof(unsigned int));
        printf("%d %d %d\n", n[0],n[1],n[2]);
        for(i=2;i<n[2];i++){
            if(n[2]%i==0){
                num=0;
                break;
            }
            else{
                num=n[2];
            }
        }

        respuesta.inicializaPuerto(paquete.obtienePuerto());
        respuesta.inicializaIp(paquete.obtieneDireccion());
        respuesta.inicializaDatos((char *)&num);
        cliente.envia(respuesta);

    }

    return 0;
}
