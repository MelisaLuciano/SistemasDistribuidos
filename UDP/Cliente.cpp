#include "SocketDatagrama.h"
#include "PaqueteDatagrama.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>


int puerto = 7200;

int main(void){
   struct sockaddr_in msg_to_server_addr, client_addr;
   int s, num[2], res;
   char cadena[10];
   int clilen = sizeof(msg_to_server_addr);
   
   s = socket(AF_INET, SOCK_DGRAM, 0);
   /* rellena la dirección del servidor */
   bzero((char *)&msg_to_server_addr, sizeof(msg_to_server_addr));
   msg_to_server_addr.sin_family = AF_INET;
   msg_to_server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
   msg_to_server_addr.sin_port = htons(puerto);
   sprintf(cadena,"%d",msg_to_server_addr.sin_addr.s_addr);
   for(int i = 0; i < strlen(cadena); i++)
   {
      printf("%c\n", cadena[i]);
   }

   /* rellena la direcciòn del cliente*/
   bzero((char *)&client_addr, sizeof(client_addr));
   client_addr.sin_family = AF_INET;
   client_addr.sin_addr.s_addr = INADDR_ANY;
   
   /*cuando se utiliza por numero de puerto el 0, el sistema se encarga de asignarle uno */
   client_addr.sin_port = htons(0);
   bind(s, (struct sockaddr *)&client_addr,sizeof(client_addr));
   num[0] = 5;
   num[1] = 9; /*rellena el mensaje */
   sendto(s, (char *)num, 2 * sizeof(int), 0, (struct sockaddr *) &msg_to_server_addr, sizeof(msg_to_server_addr));
   
   /* se bloquea esperando respuesta */
   recvfrom(s, (char *)&res, sizeof(int), 0, (struct sockaddr*)&msg_to_server_addr, (socklen_t*)&clilen);
   printf("\nDireccion IP: %s\n", inet_ntoa(msg_to_server_addr.sin_addr));
   printf("\nPuerto: %hu\n", ntohs(msg_to_server_addr.sin_port));
   printf("\n%d + %d = %d\n", num[0], num[1],res);
   close(s);
}