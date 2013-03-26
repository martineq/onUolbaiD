#pragma once

#include "../vista/VistaPantalla.h"
#include "DetectorEventos.h"

class ControladorJuego{
	private:
		VistaPantalla pantalla;
		DetectorEventos detector;
	public:
		ControladorJuego(void);
		~ControladorJuego(void);
		void loop();

};
