#pragma once

#include <vector>
#include "DetectorEventos.h"
#include "ControladorEvento.h"

class ControladorLoop{
	private:
		DetectorEventos detector;
		ControladorEvento evento;

public:
		ControladorLoop();
		virtual ~ControladorLoop();
		void loop();		
		bool getQuit();
		ControladorEvento* getControladorEvento();
};
