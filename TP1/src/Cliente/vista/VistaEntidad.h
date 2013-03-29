#pragma once

#include "./VistaAnimaciones.h"
#include "../../Servidor/modelo/ModeloEntidad.h"

class VistaEntidad{

	VistaAnimaciones vistaAnimaciones;

	public:
		VistaEntidad(void);
		~VistaEntidad(void);

		void actualizar(class Observable* s);
};
