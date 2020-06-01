#ifndef Archivo_h
#define Archivo_h

class Archivo{
	private:
		char buffer[BUFSIZ];
		int origen;
		int destino;
		int nbytes;
	public:
		Archivo();
		void ObtenerArchivoOrigen(char nombre);
		void CrearArchivoDestino(char nombre);
		void ActualizarBuffer(char datos);
		void CopiarArchivo();
		void CerrarArchivo();
};

#endif