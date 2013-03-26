#pragma once

#include <SDL.h>
#include "../../utils/Controles/UIState.h"


class DetectorEventos{

	private:
		bool quit;

	public:
		DetectorEventos(void);
		~DetectorEventos(void);
		void detectar();
		bool getQuit();
};
