#include "Solicitud.h"
#include <iostream>
#include <string.h>

using namespace std;

int main(int argc, char *argv[]){
    if(argc<4)
    {
        cout<<"Ingrese direccion ip,puerto y numero de operaciones al servidor"<<endl;
    }
    Solicitud cliente1;
    int cantidad[2];
    cantidad[0]=0;
    cantidad[1]=10;
    int n=atoi(argv[3]);
    int i;
    for(i=0;i<n;i++){
        int saldoinicial;
        int respuesta;
        memcpy(&saldoinicial,cliente1.doOperation(argv[1], atoi(argv[2]), 1, (char *)cantidad),sizeof(int));
        cout<<"El saldo anterior es "<<saldoinicial<<endl;
        memcpy(&respuesta,cliente1.doOperation(argv[1], atoi(argv[2]), 2, (char *)&cantidad),sizeof(int));
        cout << "Saldo actualizado:" << respuesta << endl;
        if(saldoinicial+1!=respuesta){
            cout<<"Error"<<endl;
            break;
        }
    }
    return 0;
}
