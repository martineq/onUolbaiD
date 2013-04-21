#pragma once

#include "./ControladorLoop.h"
#include "../../utils/Observador/Observador.h"

class ControladorJuego{

	private:
		ControladorLoop controladorLoop;	

	public:
		ControladorJuego(void);
		~ControladorJuego(void);
		void agregarObservadorScroll(Observador* observadorScroll);
		bool loop(void);		// Inicia el ModeloLoop y le pasa el ModeloNivel

};
