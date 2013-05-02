#pragma once

#include <SDL.h>
#include "./VistaNivel.h"
#include "ImageLoader.h"
#include "VistaEntidad.h"

class VistaLoop{
	private:
		SDL_Surface *pantalla;			
		bool dibujarEntidades(VistaNivel& vistaNivel, char** matriz);				
		void refrescarMatriz(VistaNivel& vistaNivel, char** matriz);
		char visibilidadDeLaEntidad(VistaEntidad* unaEntidad,char** matriz);
	public:
		VistaLoop(void);
		~VistaLoop(void);
		bool loop(VistaNivel& vistaNivel, char** matriz);

		// Levanta la pantalla
		void setPantalla(SDL_Surface *pantalla);
		
};
