#pragma once

#include <SDL.h>
#include "./VistaNivel.h"
#include "ImageLoader.h"


class VistaLoop{
	private:
		SDL_Surface *pantalla;			
		bool dibujarEntidades(VistaNivel& vistaNivel);			

	public:
		VistaLoop(void);
		~VistaLoop(void);
		bool loop(VistaNivel& vistaNivel);

		// Levanta el fondo y la pantalla
		void setPantalla(SDL_Surface *pantalla);
		
};
