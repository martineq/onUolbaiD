#include "./VistaLoop.h"

VistaLoop::VistaLoop(void){

}

bool VistaLoop::loop(VistaNivel& vistaNivel){

	this->dibujarPantalla(vistaNivel);

	return true;	// TODO: Implementar este return
}

//levanta el fondo y la pantalla
bool VistaLoop::levantarPantalla(int altoPantalla, int anchoPantalla){

	ImageLoader::getInstance().iniciarSDL();	

	// Creo la ventana
	this->pantalla = ImageLoader::getInstance().levantarPantalla(anchoPantalla,altoPantalla);

	this->fondo = ImageLoader::getInstance().load_image(SDL_RUTA_FONDO);	

	return true; // TODO: Implementar el return del método
}

void VistaLoop::dibujarPantalla(VistaNivel& vistaNivel){
	// Cargo el fondo
	SDL_Rect rcFondo = ImageLoader::getInstance().createRect(0,0);
	SDL_BlitSurface(this->fondo, NULL, this->pantalla, &rcFondo);

	// Dibujo el Mouse
	//SDL_Rect r;	
	//r.x = eventos.getPosicionMouseX() - 32;
	//r.y = eventos.getPosicionMouseY() - 24;
	//r.w = 64;
	//r.h = 48;	
	//SDL_FillRect(pantalla, &r, 0xff << (eventos.getClicMouseBotonIzquierdo() * 8));
	//SDL_FillRect(pantalla, &r, 0xff << (eventos.at(3) * 8));

	SDL_UpdateRect(this->pantalla, 0, 0, 0, 0);	
}

VistaLoop::~VistaLoop(void){
/*	SDL_FreeSurface(pantalla);
	SDL_FreeSurface(fondo);	
	ImageLoader::getInstance().cerrarSDL();	*/
}