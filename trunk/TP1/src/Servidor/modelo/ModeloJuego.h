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
		
		void agregarObservadoresScroll(std::list<Observador*>);
		
		void agregarObservadoresEntidad(std::list<Observador*>);
		
		Observador* obtenerObservadorEvento();
		
		bool loop();
};
