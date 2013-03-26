#pragma once
//#include <SDL_image.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "../../utils/Constantes.h"
#include <iostream>
#include <string>
#include <vector>
//#include "UIState.h"
//#include "UIControl.h"


//class VistaPantalla:UIControl {
class VistaPantalla{
private:
	SDL_Surface *pantalla,*fondo,*textSurface;	
	TTF_Font* font;
public:
	VistaPantalla();
	void levantar();
	void dibujar(std::vector<int> eventos);
	~VistaPantalla();
};

