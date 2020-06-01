#include <iostream>
#include <string.h>
#include <cmath>
#include "gfx.h"
#include "Respuesta.h"
#include "mensaje.h"
#include <unistd.h>
#include <sys/time.h>
using namespace std;

#define pto 7200

int main(){
	struct timeval tiempo;
	tiempo.tv_sec=400000;
	tiempo.tv_usec=0;
	cout<<settimeofday(&tiempo, NULL)<<endl;
	Respuesta respuesta(pto);
	mensaje *hora;
	int horaExacta[2];
	time_t t;
	struct tm *tm;
	while(1){
		cout<<"Esperando solicitud"<<endl;
		hora=respuesta.getRequets();
		gettimeofday(&tiempo,NULL);
		horaExacta[0]=tiempo.tv_sec;
		horaExacta[1]=tiempo.tv_usec;
		respuesta.sendReply((char*)horaExacta,hora->IP,hora->puerto);
		cout<<"Envio hora"<<endl;
	}
}