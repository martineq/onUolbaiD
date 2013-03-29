#pragma once

#include <list>
#include "./modelo/ModeloJuego.h"
#include "../utils/Observador/Observador.h"

class Servidor{
	
	private:
		ModeloJuego modeloJuego;

	public:
		Servidor(void);
		~Servidor(void);

		bool iniciar(void);		// Inicia el Modelo Juego
		void agregarObservadoresScroll(std::list<Observador*>);
		void agregarObservadoresEntidad(std::list<Observador*>);
		Observador* obtenerObservadorEvento(void);
		bool loop(void);		// Inicia el loop de Modelo Juego
		

};
