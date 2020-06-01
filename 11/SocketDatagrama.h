#include "PaqueteDatagrama.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#ifndef SocketDatagrama_h_
#define SocketDatagrama_h_

class SocketDatagrama{
	public:
		SocketDatagrama(int puerto);
		~SocketDatagrama();
		int recibe(PaqueteDatagrama & p);
		int envia(PaqueteDatagrama & p);
	private:
		struct sockaddr_in direccionLocal;
		struct sockaddr_in direccionForanea;
		int s;
};

#endif