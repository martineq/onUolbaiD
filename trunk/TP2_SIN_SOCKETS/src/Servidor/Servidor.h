#pragma once

#include <list>

#include "../utils/Observador/Observador.h"
#include "modelo/ModeloJuego.h"
#include "modelo/ModeloScroll.h"

class Servidor {
	private:
		ModeloJuego modeloJuego;

	public:
		Servidor();
		
		virtual ~Servidor();

		// Inicia el Modelo Juego
		bool iniciar();
		
		void agregarObservadoresJugador(std::list<Observador*>listaObservadoresJugador);

		void agregarObservadoresScroll(std::list<Observador*>listaObservadoresScroll);
		
		void agregarObservadoresEntidad(std::list<Observador*>listaObservadoresEntidad);
		
		Observador* obtenerObservadorEvento();
		
		// Inicia el loop de Modelo Juego
		bool loop();

		void destruirEntidades();
};
