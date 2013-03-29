#pragma once

#include "DetectorEventos.h"
#include "ControladorEvento.h"
#include "../../utils/Observador/Observador.h"
#include "../../utils/Timer/Timer.h"
#include <vector>

class ControladorLoop{
	private:
		DetectorEventos detector;
		ControladorEvento evento;
		int posicionMouseXAnterior;
		int posicionMouseYAnterior;
		int clicMouseBotonIzquierdoAnterior;
		int clicMouseBotonDerechoAnterior;				
	public:
		ControladorLoop(void);
		~ControladorLoop(void);
		void loop();		
		bool getQuit();
		void agregarObservadorEventos(Observador* observador);
};
