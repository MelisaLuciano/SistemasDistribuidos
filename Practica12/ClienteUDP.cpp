#include "Solicitud.h"
#include "PaqueteDatagrama.h"
#include <iostream>
#include <string.h>

using namespace std;

char cantidad[1]={'1'};

int main(int argc, char *argv[]){
    Solicitud cliente1;
    int n=atoi(argv[3]);
    int saldoinicial=0;
    for(int i=0;i<n;i++){
        char respuesta[4000];
        saldoinicial=atoi(cliente1.doOperation(argv[1], atoi(argv[2]), 1, (char *)cantidad));
        cout<<"El saldo anterior es "<<saldoinicial<<endl;
        memcpy(respuesta,cliente1.doOperation(argv[1], atoi(argv[2]), 2, (char *)cantidad),4000);
        cout << "Saldo actualizado:" << atoi(respuesta) << endl;
        if(saldoinicial+1!=atoi(respuesta)){
            cout<<"Error"<<endl;
            break;
        }
    }
    return 0;
}
