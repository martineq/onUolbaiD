#pragma once

#include "ModeloNivel.h"
#include "ModeloEvento.h"

class ModeloLoop {

	private:
		ModeloEvento _modeloEvento;

	public:
		ModeloLoop();
		virtual ~ModeloLoop();
		bool loop(ModeloNivel& modeloNivel);
};
