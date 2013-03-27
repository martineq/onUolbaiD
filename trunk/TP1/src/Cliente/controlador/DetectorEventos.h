#pragma once

#include <SDL.h>
//#include "../../utils/Controles/UIState.h"


class DetectorEventos{

	private:
		bool quit;		
	public:
		int posicionMouseX;
		int posicionMouseY;
		int clicMouseBotonIzquierdo;
		int clicMouseBotonDerecho;

		DetectorEventos(void);
		~DetectorEventos(void);
		void detectar();
		bool getQuit();
};
