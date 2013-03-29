#pragma once

#include <list>
#include "./VistaScroll.h"
#include "./VistaEntidad.h"
#include "../../utils/Observador/Observador.h"


class VistaNivel{

	private:
		VistaScroll* vistaScroll;
		std::list<VistaEntidad *> listaVistaEntidad;

	public:
		VistaNivel();
		~VistaNivel();

		Observador* obtenerObservadorScroll(void);
		std::list<Observador*> obtenerObservadoresEntidad(void);

};

