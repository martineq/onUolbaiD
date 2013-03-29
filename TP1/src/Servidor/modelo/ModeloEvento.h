#pragma once

#include "../../utils/Observador/Observador.h"
#include "../../Cliente/controlador/ControladorEvento.h"

class ModeloEvento: public Observador{

		public:
			ModeloEvento(void);
			~ModeloEvento(void);

		void actualizar(class Observable* s);
};
