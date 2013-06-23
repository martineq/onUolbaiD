#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include "ESArchivoCpp.h"

class FinalB{

	private:

		struct stPunto{
			long x;
			long y;
			unsigned char b; 
			unsigned char g;
			unsigned char r;
		};
		
		struct stColor{
			unsigned char b; 
			unsigned char g;
			unsigned char r;
		};

		struct stDatos{

			// Datos a obtener a partir del archivo de imagen
			unsigned int offsetDatos;
			unsigned int anchoPix;
			unsigned int altoPix;
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

		void pintar(stDatos &datos, stPunto pReemp, stColor c, bool* pintado);

	public:
		FinalB(void);
		~FinalB(void);

		void resolver(void);

};
