#pragma once

#include <SDL.h>
#include "./VistaNivel.h"
#include "ImageLoader.h"


class VistaLoop{
	private:
		SDL_Surface *pantalla,*fondo;			
		bool dibujarEntidades(VistaNivel& vistaNivel);			

	public:
		VistaLoop(void);
		~VistaLoop(void);						
		bool loop(VistaNivel& vistaNivel);

		//levanta el fondo y la pantalla
		bool levantarFondo(double,double);
		void setPantalla(SDL_Surface *pantalla);
		
};
