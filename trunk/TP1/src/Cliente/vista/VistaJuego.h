#pragma once

#include "./VistaFactory.h"
#include "./VistaNivel.h"
#include "./VistaLoop.h"
#include "../../utils/Observador/Observador.h"

class VistaJuego{

	private:
		VistaFactory vistaFactory;
		VistaNivel vistaNivel;
		VistaLoop vistaLoop;

	public:
		VistaJuego(void);
		~VistaJuego(void);

		Observador* obtenerObservadorScroll(void);
		std::list<Observador*> obtenerObservadoresEntidad(void);
		bool iniciar(void);		// Inicia el VistaFactory
		bool loop(void);		// Inicia el VistaLoop y le pasa el VistaNivel

};
