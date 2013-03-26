#pragma once


#include "./VistaScroll.h"
#include "./VistaEntidad.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include "../../utils/Constantes/Constantes.h"
#include "../../utils/Controles/UIState.h"
#include "../../utils/Controles/UIControl.h"


class VistaNivel:UIControl{

	private:
		VistaScroll vistaScroll;
		VistaEntidad vistaEntidad;

		SDL_Surface *pantalla,*fondo,*textSurface;	// Dani
		TTF_Font* font; // Dani

	public:
		VistaNivel(void);
		~VistaNivel(void);
		void levantar();
		void dibujar();

};
