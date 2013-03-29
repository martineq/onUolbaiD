#pragma once

#include <list>
#include "./VistaScroll.h"
#include "./VistaEntidad.h"
#include "../../utils/Observador/Observador.h"


class VistaNivel{

	private:
		VistaScroll vistaScroll;
		VistaEntidad vistaEntidad;

	public:
		VistaNivel();
		~VistaNivel();

		Observador * obtenerObservadorScroll(void);
		std::list<Observador*> obtenerObservadoresEntidad(void);

};

