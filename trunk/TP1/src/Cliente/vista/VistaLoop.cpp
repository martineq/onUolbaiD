#include "./VistaLoop.h"

VistaLoop::VistaLoop(void){

}

VistaLoop::~VistaLoop(void){

}

bool VistaLoop::loop(VistaNivel& vistaNivel){
/*
	SDL_Surface *pantalla = vistaNivel.getPantalla();
	SDL_Surface *fondo = vistaNivel.getFondo();
	this->dibujarPantalla(pantalla,fondo,vistaNivel);
*/
	return false;	// TODO: Implementar este return
}

/*
void VistaLoop::dibujarPantalla(SDL_Surface* pantalla, SDL_Surface* fondo, VistaNivel& vistaNivel){
	// Cargo el fondo
	SDL_Rect rcFondo;
	rcFondo.x = 0;
	rcFondo.y = 0;	
	SDL_BlitSurface(fondo, NULL, pantalla, &rcFondo);

	//// Dibujo el Mouse
	//SDL_Rect r;	
	//r.x = eventos.getPosicionMouseX() - 32;
	//r.y = eventos.getPosicionMouseY() - 24;
	//r.w = 64;
	//r.h = 48;	
	//SDL_FillRect(pantalla, &r, 0xff << (eventos.getClicMouseBotonIzquierdo() * 8));
	//SDL_FillRect(pantalla, &r, 0xff << (eventos.at(3) * 8));

	// Dibujo una etiqueta
	
	SDL_Surface* textSurface = vistaNivel.getTextSurface();
	SDL_BlitSurface(textSurface, NULL, pantalla, NULL);
	
	// actualiza la pantalla
	SDL_UpdateRect(pantalla, 0, 0, 0, 0);	
}
*/
