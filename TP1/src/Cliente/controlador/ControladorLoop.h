#pragma once

#include "./ControladorEvento.h"
#include "./DetectorEventos.h"
#include "../../utils/Observador/Observador.h"
#include "../../utils/Timer/Timer.h"

class ControladorLoop{

	private:
		DetectorEventos detectorEventos;
		ControladorEvento evento;

	public:
		ControladorLoop(void);
		~ControladorLoop(void);

		void agregarObservadorEventos(Observador* observador);
		bool loop(void);

};
