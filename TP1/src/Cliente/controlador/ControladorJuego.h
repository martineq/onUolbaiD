#pragma once

#include "./ControladorLoop.h"

// TODO: Ver si va dentro del controlador
#include "./DetectorEventos.h" // Dani

class ControladorJuego{

	private:
		ControladorLoop controladorLoop;

		DetectorEventos detector; // Dani

	public:
		ControladorJuego(void);
		~ControladorJuego(void);
		void loop(); // Dani
		bool getQuit(); // Dani

};
