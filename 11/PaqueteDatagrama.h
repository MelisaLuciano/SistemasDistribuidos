#ifndef PaqueteDatagrama_h_
#define PaqueteDatagrama_h_

class PaqueteDatagrama{
	public:
		PaqueteDatagrama(char *dato,unsigned int longi,char *direccion,int pto);
		PaqueteDatagrama(unsigned int longi);
		~PaqueteDatagrama();
		char *obtieneDireccion();
		unsigned int obtieneLongitud();
		int obtienePuerto();
		char *obtieneDatos();
		void inicializaPuerto(int);
		void inicializaIP(char *);
		void inicializaDatos(char *);
	private:
		char *datos;
		char ip[16];
		unsigned int longitud;
		int puerto;
};

#endif