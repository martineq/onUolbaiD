#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <list>
#include "./VistaScroll.h"
#include "./VistaEntidad.h"
#include "../../utils/Constantes/Constantes.h"
#include "../../utils/Observador/Observador.h"

class VistaNivel{

	private:
		VistaScroll* scroll;
		std::list<VistaEntidad*> listaEntidades;

		// TODO: Ver si estos punteros SDL se usan así, o se usan con la nueva clase utilidad SDL
/*		SDL_Surface *pantalla,*fondo,*textSurface;	
		TTF_Font* font;	 */

	public:
		VistaNivel();
		~VistaNivel();

		// Getters
		Observador* obtenerObservadorScroll(void);
		std::list<Observador*> obtenerObservadoresEntidad(void);
		VistaScroll* getScroll(void);
		std::list<VistaEntidad*> getListaEntidades(void);

		// Setters
		void agregarJugador(VistaEntidad* pJugador);
		void agregarEntidad(VistaEntidad* pEntidad);
		void agregarScroll(VistaScroll* pScroll);

		// TODO: Ver si estos metodos que manejan SDL se usan así, o se usan con la nueva clase utilidad SDL
/*		bool levantarPantalla();
		SDL_Surface* getPantalla ();
		SDL_Surface* getFondo ();
		TTF_Font* getFont();
		SDL_Surface* getTextSurface();
*/		

};