#pragma once

#include <vector>
#include "ESArchivoCpp.h"

class FinalB{

	private:

		struct stPunto{
			unsigned long x;
			unsigned long y;
			unsigned char b; 
			unsigned char g;
			unsigned char r;
		};

		struct stDatos{

			// Datos a obtener a partir del archivo de imagen
			unsigned int offsetDatos;
			unsigned int anchoFila;			// Valor en bytes. Ya incluye el padding.
			unsigned int cantidadFilas;
			unsigned int paddingAplicado;
			unsigned char* arrayPixeles;

			// Datos a obtener a partir del archivo de datos
			std::vector<stPunto> puntos;

		};

		void leerArchivoImagen(stDatos &datos);
		void leerArchivoDatos(stDatos &datos);
		void pintarAreas(stDatos &datos);
		void guardarArchivo(stDatos &datos);

	public:
		FinalB(void);
		~FinalB(void);

		void resolver(void);

};
