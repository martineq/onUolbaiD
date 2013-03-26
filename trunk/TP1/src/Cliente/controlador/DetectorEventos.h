#pragma once

#include <SDL.h>
#include "../vista/UIState.h"

class DetectorEventos{

	private:
		bool quit;

	public:
		DetectorEventos(void);
		~DetectorEventos(void);
		void detectar();
		bool getQuit();
};
