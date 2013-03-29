#pragma once

#include "./ModeloFactory.h"
#include "./ModeloNivel.h"
#include "./ModeloLoop.h"
#include "../../utils/Observador/Observador.h"

class ModeloJuego{

	private:
		ModeloFactory modeloFactory;
		ModeloNivel modeloNivel;
		ModeloLoop modeloLoop;

	public:
		ModeloJuego(void);
		~ModeloJuego(void);

		bool iniciar(void);		// Inicia el ModeloFactory
		void agregarObservadoresScroll(std::list<Observador*>);
		void agregarObservadoresEntidad(std::list<Observador*>);
		Observador* obtenerObservadorEvento(void);
		bool loop(void);		// Inicia el ModeloLoop y le pasa el ModeloNivel


};
