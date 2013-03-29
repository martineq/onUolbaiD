#pragma once

#include <list>
#include "./ModeloEvento.h"
#include "../../utils/Observador/Observador.h"

class ModeloLoop{

	ModeloEvento evento;

	public:
		ModeloLoop(void);
		~ModeloLoop(void);

		Observador* obtenerObservadorEvento(void);

};
