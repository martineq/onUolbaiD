#pragma once

#include <iostream>
#include <string.h>

#include "../../utils/Constantes/Constantes.h"
#include "../../utils/Posicion/Posicion.h"

class EstadoNivel {
	private:
		int _alto;
		int _ancho;
		Posicion _posicion;
		char* _nivel;

		EstadoNivel(const EstadoNivel &estadoNivel);

		EstadoNivel& operator=(const EstadoNivel &estadoNivel);

	public:
		EstadoNivel(int alto, int ancho, int x, int y);

		virtual ~EstadoNivel();

		void visitar(int x, int y);

		char visibilidad(int x, int y);

		std::string getMatriz();
};
