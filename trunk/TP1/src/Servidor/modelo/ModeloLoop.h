#pragma once

#include <list>
#include "./ModeloEvento.h"

class ModeloLoop{

	std::list <ModeloEvento> listaDeEventos;

	public:
		ModeloLoop(void);
		~ModeloLoop(void);

};
