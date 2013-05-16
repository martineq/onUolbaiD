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

	this->visible = 0;
	this->gris = 0;
	this->negro = 0;
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

bool SDLutil::graficar(char visibilidad) {
	//int colorClave;		
	//colorClave = SDL_MapRGB(this->mySurface->format, 0, 0, 0);	
	//SDL_Surface* prueba = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCALPHA, 100, 50, 32, 0, 0, 0, 0);		

	/*if (SDL_SetColorKey(this->mySurface, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorClave) != 0) {
    	Log::getInstance().log(1, __FILE__, __LINE__, "Error al agregar un componente a la pantalla");
		return false;
    }
	
	if (this->fondo == NULL)
		this->fondo = SDL_CreateRGBSurface(SDL_SWSURFACE, this->area->w, this->area->h, 32, 0, 0, 0, 0);
	SDL_BlitSurface(this->screen, &posicionPantalla, this->fondo, NULL);*/

	if (visibilidad == 1) {
		//opcion 1
		//Uint32 colorGris = SDL_MapRGB(this->screen->format, 127, 127, 127); 
		//SDL_FillRect(this->mySurface, NULL, colorGris);		
		//opcion 2
		//SDL_SetAlpha(this->mySurface, SDL_SRCALPHA|SDL_RLEACCEL, 127);
		//opcion 3 
			/* Create a display surface with a grayscale palette */
			/*SDL_Surface *screen;
			SDL_Color colors[256];
			int i;
			/* Fill colors with color information */
			/*for(i=0;i<256;i++){
				colors[i].r=i;
				colors[i].g=i;
				colors[i].b=i;
			}
			SDL_SetPalette(this->mySurface, SDL_LOGPAL|SDL_PHYSPAL, colors, 0, 256);*/
		//opcion con la que anda la prueba
		//SDL_FillRect(prueba, NULL, SDL_MapRGB(this->screen->format, 0, 0, 255));//AZUL
		SDL_SetAlpha(this->mySurface, SDL_SRCALPHA, SDL_ALPHA_OPAQUE / 2);
	}
	else if (visibilidad == 0) {
		//opcion 1 negro fillrect
		//Uint32 colorNegro = SDL_MapRGB(this->screen->format, 255, 255, 255); 
		//SDL_FillRect(this->mySurface, NULL, colorNegro);		
		//opcion 2 alpha
		//SDL_SetAlpha(this->mySurface, SDL_SRCALPHA|SDL_RLEACCEL, 127);
		//opcion 3
		/* Create a display surface with a grayscale palette */
			/*SDL_Surface *screen;
			SDL_Color colors[256];
			int i;*/
			/* Fill colors with color information */
			/*for(i=0;i<256;i++){
				colors[i].r=i;
				colors[i].g=i;
				colors[i].b=i;
			}
			SDL_SetPalette(this->mySurface, SDL_LOGPAL|SDL_PHYSPAL, colors, 0, 256);*/
		//bueno pruebo esto sino		
		//SDL_FillRect(prueba, NULL, SDL_MapRGB(this->screen->format, 0, 0, 0));//NEGRO
		SDL_SetAlpha(this->mySurface, SDL_SRCALPHA, SDL_ALPHA_TRANSPARENT);
	}
	else if (visibilidad == 2) {
		//SDL_SetAlpha(this->mySurface, SDL_SRCALPHA|SDL_RLEACCEL, 127);
		//SDL_FillRect(prueba, NULL, SDL_MapRGB(this->screen->format, 255, 255, 0));//AMARILLO	
		//SDL_FillRect(this->mySurface, NULL, SDL_MapRGB(this->screen->format, 255, 255, 0));//AMARILLO
		SDL_SetAlpha(this->mySurface, SDL_SRCALPHA, SDL_ALPHA_OPAQUE);
	}
	
	SDL_Rect posicionPantalla;
	posicionPantalla.h = this->area->h;
	posicionPantalla.w = this->area->w;
	posicionPantalla.x = this->x;
	posicionPantalla.y = this->y;

	//if (SDL_BlitSurface(prueba, this->area, this->screen, &posicionPantalla) != 0) {
	if (SDL_BlitSurface(this->mySurface, this->area, this->screen, &posicionPantalla) != 0) {
    	Log::getInstance().log(1, __FILE__, __LINE__, "Error al agregar un componente a la pantalla");
		return false;
    }
	
	//SDL_FreeSurface(prueba);	
	return true;
}

bool SDLutil::graficar(double x, double y, char visibilidad) {
	this->x = x;
	this->y = y;
	
	return this->graficar(visibilidad);
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


// TODO: Borrar todo el código que no se usa mas de esta clase