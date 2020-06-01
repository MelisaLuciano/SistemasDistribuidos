#include "PaqueteDatagrama.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include<sys/time.h>
#ifndef SocketDatagrama_h_
#define SocketDatagrama_h_

class SocketDatagrama{
	public:
		SocketDatagrama(int puerto);
		~SocketDatagrama();
		int recibeTimeout(PaqueteDatagrama & p,time_t segundos,suseconds_t microsegundos);
		int recibe(PaqueteDatagrama &paquete);
		int envia(PaqueteDatagrama & p);
	private:
		struct sockaddr_in direccionLocal;
		struct sockaddr_in direccionForanea;
		int s;
};

#endif