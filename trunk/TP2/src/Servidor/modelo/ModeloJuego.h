#pragma once

#include "./ModeloFactory.h"
#include "./ModeloNivel.h"
#include "./ModeloLoop.h"

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
				
		bool loop();

		void destruirEntidades();
};
