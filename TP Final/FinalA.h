#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include "ESArchivoCpp.h"

class FinalA{

	private:

		struct stDatos{

			// Datos a obtener a partir del archivo. Los tipos de los datos están dados en el enunciado.
			int anchoPix;
			int altoPix;
			unsigned int tamanioArchivo;
			unsigned int offsetDatos;
			unsigned int anchoFila;			// Valor en bytes. Ya incluye el padding.
			unsigned int cantidadFilas;
			unsigned int paddingAplicado;
			unsigned int bytesPorPixel;
			unsigned char* arrayPixeles;

			// Resultados de duplicar
			unsigned char* arrayPixelesDuplicados;
			unsigned int anchoFilaDoble;			// Valor en bytes. Ya incluye el padding.
			unsigned int paddingAplicadoDoble;

			// Resultados de encontrar el color de transparencia
			unsigned char fondoR;
			unsigned char fondoG;
			unsigned char fondoB;
		};

		struct stColor{
			unsigned char b;
			unsigned char g;
			unsigned char r;
			unsigned long cantidad;
		};

		void leerArchivo(stDatos &datos);
		void duplicarTamanioImagen(stDatos &datos);
		void calcularColorTransparente(stDatos &datos);
		void reemplazarColorTransparente(stDatos &datos);
		void guardarArchivo(stDatos &datos);

	public:
		FinalA(void);
		~FinalA(void);

		void resolver(void);
		void pruebaPintaVerde(void);

};
