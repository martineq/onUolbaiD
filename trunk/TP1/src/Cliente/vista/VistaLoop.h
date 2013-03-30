#pragma once

#include <SDL.h>
#include "./VistaNivel.h"


class VistaLoop{

	public:
		VistaLoop(void);
		~VistaLoop(void);		
		void dibujarPantalla(SDL_Surface*,SDL_Surface*,VistaNivel& vistaNivel);		
		bool loop(VistaNivel& vistaNivel);
};
