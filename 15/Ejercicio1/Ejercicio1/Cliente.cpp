#include "Solicitud.h"
#include<iostream>
#include<string.h>
using namespace std;

int main(){
	char ip[16];
	int dato[2];
	dato[0]=5;
	dato[1]=2;
	Solicitud solicitud;
	for(int i=66;i<96;i++){
		for(int j=1;j<255;j++){
			strcpy(ip,"");
			sprintf(ip,"10.100.%d.%d",i,j);
			solicitud.doOperation(ip,7200,1,(char*)dato,i*j);
		}
	}
}