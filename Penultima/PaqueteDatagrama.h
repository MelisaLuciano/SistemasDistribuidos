#ifndef PAQUETE_DATAGRAMA_H_
#define PAQUETE_DATAGRAMA_H_

class PaqueteDatagrama
{
    public:
        //Constructor
        PaqueteDatagrama(char *, unsigned int, char * , int);
        PaqueteDatagrama(unsigned int);
        ~PaqueteDatagrama();
        
        //Getter
        char* obtieneDireccion();
        char* obtieneDatos();
        int obtienePuerto();
        unsigned int obtieneLongitud();
    
        //Setter
        void inicializaPuerto(int);
        void inicializaIp(char *);
        void inicializaDatos(char *);
        
    private:
        char* datos;
        char ip[16];
        unsigned int longitud;
        int puerto;
};
#endif