#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include "../../utils/Constantes/Constantes.h"
#include <iostream>
#include <string>
#include <vector>


class VistaNivel{
private:
	SDL_Surface *pantalla,*fondo,*textSurface;	
	TTF_Font* font;
public:
	VistaNivel();
	void levantar();
	void dibujar(std::vector<int> eventos);
	~VistaNivel();
};

