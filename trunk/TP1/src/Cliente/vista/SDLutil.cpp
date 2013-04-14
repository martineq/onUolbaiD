#include "SDLutil.h"

SDLutil::SDLutil() {
	this->mySurface = NULL;
	this->screen = NULL;
	this->fondo = NULL;
	this->area = NULL;
}

SDLutil::SDLutil(double x, double y, int w, int h, std::string filename) {
	this->mySurface = ImageLoader::getInstance().load_image(filename);
	this->mySurface = ImageLoader::getInstance().stretch(this->mySurface, w, h);

	this->screen = NULL;
	this->fondo = NULL;

	this->area = new SDL_Rect();
	this->area->h = h;
	this->area->w = w;
	this->area->x = x;
	this->area->y = y;
}

void SDLutil::setX(double x) {
	this->x = x;
}

void SDLutil::setY(double y) {
	this->y = y;
}

void SDLutil::setPantalla(SDL_Surface* pantalla) {
	this->screen = pantalla;
}

double SDLutil::getX() {
	return this->x;
}

double SDLutil::getY() {
	return this->y;
}

SDL_Surface* SDLutil::getSurface() {
	return this->mySurface;
}


SDL_Rect* SDLutil::getRect() {
	return this->area;
}

bool SDLutil::graficar() {
	int colorClave;
	SDL_Rect posicionPantalla;
	
	colorClave = SDL_MapRGB(this->mySurface->format, 0, 0, 0);	

	posicionPantalla.h = this->area->h;
	posicionPantalla.w = this->area->w;
	posicionPantalla.x = this->x;
	posicionPantalla.y = this->y;

	if (SDL_SetColorKey(this->mySurface, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorClave) != 0) {
    	Log::getInstance().log(1, __FILE__, __LINE__, "Error al agregar un componente a la pantalla");
		return false;
    }
	
	if (this->fondo == NULL)
		this->fondo = SDL_CreateRGBSurface(SDL_SWSURFACE, this->area->w, this->area->h, 32, 0, 0, 0, 0);
	SDL_BlitSurface(this->screen, &posicionPantalla, this->fondo, NULL);

    if (SDL_BlitSurface(this->mySurface, this->area, this->screen, &posicionPantalla) != 0) {
    	Log::getInstance().log(1, __FILE__, __LINE__, "Error al agregar un componente a la pantalla");
		return false;
    }
	
	return true;
}

bool SDLutil::graficar(double x, double y) {
	this->limpiar();

	this->x = x;
	this->y = y;
	
	return this->graficar();
}

void SDLutil::limpiar() {
	if (this->fondo == NULL)
		return;

	SDL_Rect posicionPantalla;
	posicionPantalla.h = this->area->h;
	posicionPantalla.w = this->area->w;
	posicionPantalla.x = this->x;
	posicionPantalla.y = this->y;

	SDL_BlitSurface(this->fondo, NULL, this->screen, &posicionPantalla);
}

SDLutil::~SDLutil() {
	if (this->mySurface != NULL)
		SDL_FreeSurface(this->mySurface);

	if (this->area != NULL)
		delete this->area;
}
