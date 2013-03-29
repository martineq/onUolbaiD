#pragma once

#include "VistaNivel.h"
#include <SDL.h>


class VistaLoop{
	private:
		VistaNivel vistaNivel;				
	public:
		VistaLoop(void);
		~VistaLoop(void);		
		void dibujarPantalla(SDL_Surface*,SDL_Surface*);		
		bool loop(void);
};
