#pragma once

#include <fstream>
#include <string>

class ESArchivoCpp{

	std::fstream archivo;

	public:
		ESArchivoCpp(const char* ruta, bool esEntrada, bool esTexto);
		~ESArchivoCpp(void);

		void leerArchivo(char* cadena, unsigned long offset, unsigned long tamanio);
		unsigned long leerArchivo(char** cadena);
		std::string leerArchivo(void);

		void escribirEnArchivo(const char* cadena,  unsigned long offset, unsigned long tamanio);
		void escribirEnArchivo(const char* cadena, unsigned long tamanio);
		void escribirEnArchivo(std::string cadena);

};
