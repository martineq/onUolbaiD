#pragma once

#include "DetectorEventos.h"

class ControladorJuego{
	private:
		DetectorEventos detector;
	public:
		ControladorJuego(void);
		~ControladorJuego(void);
		void loop();
		bool getQuit();

};
