#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "./ImageLoader.h"
#include "../../utils/SDLgfx/SDL_rotozoom.h"
#include "../../utils/Log/Log.h"

class SDLutil {
	private:
		double x;
		double y;

		SDL_Surface* mySurface;
		SDL_Surface* screen;
		SDL_Surface* fondo;
		SDL_Rect* area;


		int visible;
		int gris;
		int negro;
	public:
		SDLutil();
		SDLutil(double x, double y, int w, int h, std::string filename);
		void setX(double x);
		void setY(double y);
		void setPantalla(SDL_Surface* pantalla);
		double getX();
		double getY();
		SDL_Surface* getSurface();
		SDL_Rect* getRect();	
		bool graficar(char);
		bool graficar(double x, double y, char visibilidad);
		void limpiar();
		virtual ~SDLutil();
};
