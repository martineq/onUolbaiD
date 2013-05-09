#include "DetectorEventos.h"

DetectorEventos::DetectorEventos() {
	this->quit = false;
	this->posicionMouseX = 0;
	this->posicionMouseY = 0;
	this->clicMouseBotonDerecho = 0;
	this->clicMouseBotonIzquierdo = 0;
	this->dentroDePantalla = true;
	this->teclaAApretada = false;
	this->teclaSApretada = false;
	this->enter = false;
	this->escape = false;
	this->retroceso = false;
	this->caracter = 0;
}

bool DetectorEventos::getQuit() {
	return this->quit;
}

bool DetectorEventos::getDentroDePantalla() {
	return this->dentroDePantalla;
}

void DetectorEventos::detectar() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		// Si el mouse esta dentro de la pantalla
		if (event.type == SDL_APPMOUSEFOCUS) {		
            if (event.active.gain == 0) {
				this->dentroDePantalla = false;
				return;
			}
			else
				this->dentroDePantalla = true;							
		}

		switch (event.type) {
			// si el mouse se mueve.
			case SDL_MOUSEMOTION:
				this->posicionMouseX = event.motion.x;
				this->posicionMouseY = event.motion.y;
				break;
			// presiono el boton izquierdo del mouse
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button) {
					case SDL_BUTTON_LEFT:	
						this->clicMouseBotonIzquierdo = 1;
						break;
					case SDL_BUTTON_RIGHT:	
						this->clicMouseBotonDerecho = 1;
						break;
				}
				break;
			// suelto el boton izquierdo del mouse
			case SDL_MOUSEBUTTONUP:
				switch (event.button.button) {
					case SDL_BUTTON_LEFT:	
						this->clicMouseBotonIzquierdo = 0;
						break;
					case SDL_BUTTON_RIGHT:	
						this->clicMouseBotonDerecho = 0;
						break;
				}
				break;
			// presiono una tecla
			case SDL_KEYDOWN:
				// Si presiono un caracter valido lo capturo
				if ((event.key.keysym.unicode >= 32) && (event.key.keysym.unicode <= 126))
					this->caracter = (char)event.key.keysym.unicode;
				else
					this->caracter = 0;

				switch (event.key.keysym.sym) {
					case SDLK_RETURN:
						this->enter = true;
						break;
					case SDLK_ESCAPE:
						this->escape = true;
						break;
					case SDLK_BACKSPACE:
						this->retroceso = true;
						break;
					case SDLK_s:								
						this->teclaSApretada = true;
						break;
					case SDLK_a:								
						this->teclaAApretada = true;
						break;
				}
				break;
			// solto una tecla
			case SDL_KEYUP:
				// Limpio el caracter
				this->caracter = 0;

				switch (event.key.keysym.sym) {
					case SDLK_RETURN:
						this->enter = false;
						break;
					case SDLK_ESCAPE:
						this->escape = false;
						break;
					case SDLK_BACKSPACE:
						this->retroceso = false;
						break;
					case SDLK_s:
						this->teclaSApretada = false;
						break;
					case SDLK_a:
						this->teclaAApretada = false;
						break;
					default:
						break;
				}
				break;
			case SDL_QUIT:
				quit = true;
				break;
		}
	}	
}

int DetectorEventos::getPosicionMouseX() {
	return this->posicionMouseX;
}

int DetectorEventos::getPosicionMouseY() {
	return this->posicionMouseY;
}

int DetectorEventos::getClicMouseBotonIzquierdo() {
	bool valorAnterior = this->clicMouseBotonIzquierdo;
	this->clicMouseBotonIzquierdo = false;
	return valorAnterior;
	//return this->clicMouseBotonIzquierdo;
}

int DetectorEventos::getClicMouseBotonDerecho() {
	bool valorAnterior = this->clicMouseBotonDerecho;
	this->clicMouseBotonDerecho = false;
	return valorAnterior;
	//return this->clicMouseBotonDerecho;
}

bool DetectorEventos::getTeclaAApretada() {
	bool valorAnterior = this->teclaAApretada;
	this->teclaAApretada = false;
	return valorAnterior;
	//return this->teclaAApretada;
}

bool DetectorEventos::getTeclaSApretada() {
	bool valorAnterior = this->teclaSApretada;
	this->teclaSApretada = false;
	return valorAnterior;
	//return this->teclaSApretada;
}

bool DetectorEventos::getEnter() {
	bool valorAnterior = this->enter;
	this->enter = false;
	return valorAnterior;
	//return this->enter;
}

bool DetectorEventos::getEscape() {
	bool valorAnterior = this->escape;
	this->escape = false;
	return valorAnterior;
	//return this->escape;
}

bool DetectorEventos::getRetroceso() {
	bool valorAnterior = this->retroceso;
	this->retroceso = false;
	return valorAnterior;
	//return this->retroceso;
}

char DetectorEventos::getCaracter() {
	char valorAnterior = this->caracter;
	this->caracter = 0;
	return valorAnterior;
	//return this->caracter;
}

DetectorEventos::~DetectorEventos() {
}
