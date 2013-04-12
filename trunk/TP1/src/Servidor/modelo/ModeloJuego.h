#pragma once

#include "./ModeloFactory.h"
#include "./ModeloNivel.h"
#include "./ModeloLoop.h"
#include "../../utils/Observador/Observador.h"

class ModeloJuego {
	private:
		ModeloFactory _modeloFactory;
		ModeloNivel _modeloNivel;
		ModeloLoop _modeloLoop;

	public:
		ModeloJuego();
		
		virtual ~ModeloJuego();

		// Inicia el ModeloFactory
		bool iniciar();
		
		void agregarObservadoresJugador(std::list<Observador*>listaObservadoresJugador);

		void agregarObservadoresScroll(std::list<Observador*>listaObservadoresScroll);
		
		void agregarObservadoresEntidad(std::list<Observador*>listaObservadoresEntidad);
		
		Observador* obtenerObservadorEvento();
		
		bool loop();
};
