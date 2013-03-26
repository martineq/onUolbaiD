#pragma once

#include <SDL.h>
#include "../../utils/Constantes.h"
#include <iostream>
#include "UIState.h"
#include "UIControl.h"
#include <string>
//#include <SDL_image.h>
#include <SDL_ttf.h>


class VistaPantalla:UIControl {
private:
	SDL_Surface *pantalla,*fondo;
public:
	VistaPantalla();
	void levantar();
	void dibujar();
	~VistaPantalla();
};

