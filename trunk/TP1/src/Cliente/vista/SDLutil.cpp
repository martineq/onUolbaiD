#include "SDLutil.h"

SDLutil::SDLutil() {
	this->mySurface = NULL;
	this->area = NULL;
}


SDLutil::SDLutil(double x, double y, int w, int h, std::string filename){
	//The image that's loaded
	this->mySurface = ImageLoader::getInstance().load_image(filename);
	this->mySurface = ImageLoader::getInstance().stretch(this->mySurface,w,h);

	this->area = new SDL_Rect();
	area->h = h;
	area->w = w;
	area->x = x;
	area->y = y;
	//Load the image
}


void SDLutil::setX(double x){
	this->x = x;
}

void SDLutil::setY(double y){
	this->y = y;
}

void SDLutil::setPantalla(SDL_Surface* pantalla){
	this->screen = pantalla;
}

double SDLutil::getX(){
	return this->x;
}

double SDLutil::getY(){
	return this->y;
}

SDL_Surface* SDLutil::getSurface(){
	return this->mySurface;
}


SDL_Rect* SDLutil::getRect(){
	return this->area;
}

bool SDLutil::graficar(){
	int colorkey;
    //Holds offsets
	SDL_Rect offset;
	offset.x = this->x;
	offset.y = this->y;

	//colorkey = SDL_MapRGB(this->screen->format, 255, 0, 255);	
	colorkey = SDL_MapRGB(this->mySurface->format, 0, 0, 0);	
	int res = SDL_SetColorKey(this->mySurface, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
	if (res!=0) {
    	Log::getInstance().log(1,__FILE__,__LINE__,"Error al agregar un componente a la pantalla");
		return false;
    }
	//SDL_DisplayFormat(source);	
    //Blit
	res = SDL_BlitSurface( this->mySurface, this->area, this->screen, &offset );
    if (res!=0) {
    	Log::getInstance().log(1,__FILE__,__LINE__,"Error al agregar un componente a la pantalla");
		return false;
    }
	return true;
}

bool SDLutil::graficar(double x, double y){
	this->x = x;
	this->y = y;
	return this->graficar();
}


SDLutil::~SDLutil() {
	if (this->mySurface!=NULL) {
		SDL_FreeSurface(this->mySurface);
	}	
	if (this->area != NULL) {
		delete this->area;
	}
}
