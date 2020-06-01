#include "mongoose.h"
#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"
#include <iostream>
#include <string.h>
#include "Solicitud.h"
#include "mensaje.h"
#include <unistd.h>
#include <sys/time.h>
using namespace std;

static const char *s_http_port = "8000";
SocketDatagrama s(0);

static void handle_size(struct mg_connection *nc, struct http_message *hm){
  char query[256];

  mg_get_http_var(&hm->body, "query", query, sizeof(query));
  sprintf(query, "longitud de la cadena = %d caracteres", (int)strlen(query));
  printf("Cadena enviada: %s\n", query);

    mg_send_head(nc,200,strlen(query), "Content-Type: text/plain");
    mg_printf(nc, "%s", query);

}

static void ev_handler(struct mg_connection *c, int ev, void *p) {

  if (ev == MG_EV_HTTP_REQUEST) {
    struct http_message *hm = (struct http_message *) p;

    mg_send_head(c, 200, hm->message.len, "Content-Type: text/plain");
    mg_printf(c, "%.*s", (int)hm->message.len, hm->message.p);
  }
}

int main(char *argv[]) {
  struct mg_mgr mgr;
  struct mg_connection *c;
  char respuesta[16];
  Solicitud cliente;

  mg_mgr_init(&mgr, NULL);
  c = mg_bind(&mgr, s_http_port, ev_handler);
  mg_set_protocol_http_websocket(c);

  for (;;) {
    mg_mgr_poll(&mgr, 1000);
  }
  mg_mgr_free(&mgr);

  while(1){
    memcpy(respuesta,cliente.doOperation(argv[1],7200,1,(char*)"",1),16*sizeof(char));
    sleep(1);
    cout<<respuesta<<endl;
  }
  return 0;
}