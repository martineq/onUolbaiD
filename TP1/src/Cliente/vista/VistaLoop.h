#pragma once

#include <SDL.h>
#include "./VistaNivel.h"
#include "ImageLoader.h"


class VistaLoop{
	 // TODO: Ver si estos punteros SDL se usan as�, o se usan con la nueva clase utilidad SDL
		SDL_Surface *pantalla,*fondo;			
	public:
		VistaLoop(void);
		~VistaLoop(void);						
		bool loop(VistaNivel& vistaNivel);
     // TODO: Ver si estos metodos que manejan SDL se usan as�, o se usan con la nueva clase utilidad SDL
		//levanta el fondo y la pantalla
		bool levantarPantalla(int,int);
		void dibujarPantalla(VistaNivel& vistaNivel);			
};

// TODO: Ver implementaci�n de los m�todos para iniciar el sdl y para dibujar. Seguramente vn todo en el loop