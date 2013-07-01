#pragma once

#include "ESArchivoCpp.h"

class FinalE{

	private: 
	
		struct stDatos{

			// Datos a obtener a partir del archivo de imagen
			unsigned int offsetDatos;
			unsigned int anchoPix;
			unsigned int altoPix;
			unsigned int anchoFila;			// Valor en bytes. Ya incluye el padding.
			unsigned int cantidadFilas;
			unsigned int paddingAplicado;
			unsigned char* origen;
			unsigned char* histoB;
			unsigned char* histoG;
			unsigned char* histoR;

		};

		void leerArchivoImagen(stDatos &datos);
		void calcularHistogramas(stDatos &datos);
		void guardarArchivos(stDatos &datos);

	public:
		FinalE(void);
		~FinalE(void);
		
		void resolver(void);
};
