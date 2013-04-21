#pragma once

#include "./ControladorLoop.h"

class ControladorJuego{

	private:
		ControladorLoop controladorLoop;	

	public:
		ControladorJuego(void);
		~ControladorJuego(void);
		bool loop(void);		// Inicia el ModeloLoop y le pasa el ModeloNivel
		ControladorLoop* getControladorLoop(void);
};
