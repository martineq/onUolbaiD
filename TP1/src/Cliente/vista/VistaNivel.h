#pragma once

#include <list>
#include "./VistaScroll.h"
#include "./VistaEntidad.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include "../../utils/Constantes/Constantes.h"
#include "../../utils/Observador/Observador.h"

class VistaNivel{

	private:
		VistaEntidad vistaEntidad;
		VistaScroll* vistaScroll;
		std::list<VistaEntidad *> listaVistaEntidad;
		SDL_Surface *pantalla,*fondo,*textSurface;	
		TTF_Font* font;	 

	public:
		VistaNivel();
		void levantarPantalla();
		SDL_Surface* getPantalla ();
		SDL_Surface* getFondo ();
		TTF_Font* getFont();
		SDL_Surface* getTextSurface();
		~VistaNivel();
		Observador* obtenerObservadorScroll(void);
		std::list<Observador*> obtenerObservadoresEntidad(void);

};


