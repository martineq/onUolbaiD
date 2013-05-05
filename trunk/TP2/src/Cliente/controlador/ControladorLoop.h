#pragma once

#include <vector>
#include "DetectorEventos.h"
#include "ControladorEvento.h"

class ControladorLoop{
	private:
		DetectorEventos detector;
		ControladorEvento evento;
		int posicionMouseXAnterior;
		int posicionMouseYAnterior;
		int clicMouseBotonIzquierdoAnterior;
		int clicMouseBotonDerechoAnterior;	
		bool loopInicial;
		bool dentroDePantalla;

public:
		ControladorLoop(void);
		~ControladorLoop(void);
		void loop();		
		bool getQuit();
		ControladorEvento* getControladorEvento(void);
};
