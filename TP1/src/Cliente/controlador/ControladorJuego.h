#pragma once

#include "./ControladorLoop.h"
#include <vector>

// TODO: Ver si va dentro del controlador
#include "./DetectorEventos.h" // Dani

class ControladorJuego{

	private:
		ControladorLoop controladorLoop;

		DetectorEventos detector; // Dani

		std::vector<int> eventos;
	public:
		ControladorJuego(void);
		~ControladorJuego(void);
		void loop(); // Dani
		bool getQuit(); // Dani
		std::vector<int> getEventos ();

};
