#pragma once

#include <SDL.h>
#include "./VistaNivel.h"


class VistaLoop{

	public:
		VistaLoop(void);
		~VistaLoop(void);		
		//void dibujarPantalla(SDL_Surface*,SDL_Surface*,VistaNivel& vistaNivel);		
		bool loop(VistaNivel& vistaNivel);
};

// TODO: Ver implementaci�n de los m�todos para iniciar el sdl y para dibujar. Seguramente vn todo en el loop