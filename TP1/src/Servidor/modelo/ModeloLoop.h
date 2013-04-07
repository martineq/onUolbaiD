#pragma once

#include <list>
#include "ModeloNivel.h"
#include "ModeloEvento.h"
#include "../../utils/Observador/Observador.h"

class ModeloLoop {
	private:
		ModeloEvento _modeloEvento;

	public:
		ModeloLoop();
		
		virtual ~ModeloLoop();

		Observador* obtenerObservadorEvento();
		
		// Asigna el nivel que va a manejar el loop
		void asignarModeloNivel(ModeloNivel* modeloNivel);

		bool loop(ModeloNivel& modeloNivel);
};
