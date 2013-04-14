#pragma once

#include <SDL.h>
#include "./VistaNivel.h"
#include "ImageLoader.h"


class VistaLoop{
	private:
		SDL_Surface *pantalla,*fondo;			
		void dibujarEntidades(VistaNivel& vistaNivel);			

	public:
		VistaLoop(void);
		~VistaLoop(void);						
		bool loop(VistaNivel& vistaNivel);

		//levanta el fondo y la pantalla
		bool levantarFondo(double,double);
		void setPantalla(SDL_Surface *pantalla);
		
};

// TODO: Ver implementación de los métodos para iniciar el sdl y para dibujar. Seguramente vn todo en el loop