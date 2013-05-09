#include "DetectorEventos.h"

DetectorEventos::DetectorEventos(void){
	this->quit = false;
	this->posicionMouseX = 0;
	this->posicionMouseY = 0;
	this->clicMouseBotonDerecho = 0;
	this->clicMouseBotonIzquierdo = 0;
	this->dentroDePantalla = true;
	this->teclaAApretada = false;
	this->teclaSApretada = false;
	this->ticks = 0;
}

bool DetectorEventos::getQuit() {
	return this->quit;
}

bool DetectorEventos::getDentroDePantalla(){
	return this->dentroDePantalla;
}

void DetectorEventos::detectar(){
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_APPMOUSEFOCUS){
		//if (SDL_ACTIVEEVENT){
           //if( event.active.state & SDL_APPACTIVE || event.active.state & SDL_APPINPUTFOCUS ) {
                if (event.active.gain == 0) {
					this->dentroDePantalla = false;
					return void();
				}
				else this->dentroDePantalla = true;				
			//}
		}
		switch (event.type)
		{			
			// si el mouse se mueve.
			case SDL_MOUSEMOTION:				
				this->posicionMouseX = event.motion.x;
				this->posicionMouseY = event.motion.y;
			break;
			// presiono el boton izquierdo del mouse
			case SDL_MOUSEBUTTONDOWN:						
				//if (event.button.button == 1)	
				switch (event.button.button)
				{
					case SDL_BUTTON_LEFT:	
						this->clicMouseBotonIzquierdo = 1;
						break;

					case SDL_BUTTON_RIGHT:	
						this->clicMouseBotonDerecho = 1;
						break;
				}
				/*
				if (event.button == SDL_BUTTON_LEFT)
					this->clicMouseBotonIzquierdo = 1;
				else
					this->clicMouseBotonDerecho = 1;
					*/
			break;
			// suelto el boton izquierdo del mouse
			case SDL_MOUSEBUTTONUP:				
				//if (event.button.button == 1)		
				switch (event.button.button)
				{
					case SDL_BUTTON_LEFT:	
						this->clicMouseBotonIzquierdo = 0;
						break;

					case SDL_BUTTON_RIGHT:	
						this->clicMouseBotonDerecho = 0;
						break;
				}
				/*if (this->clicMouseBotonIzquierdo == 1)
					this->clicMouseBotonIzquierdo = 0;
				else 
					this->clicMouseBotonDerecho = 0;
					*/
			break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_s:								
						//if (GetTickCount() - this->ticks > 2000) {
							this->teclaSApretada = true;
							//this->ticks = GetTickCount();
						//}
						break;
					case SDLK_a:								
						//if (GetTickCount() - this->ticks > 2000) {
							this->teclaAApretada = true;
							//this->ticks = GetTickCount();
						//}							
						break;
					default:
						break;
				}							 
			break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym){
					case SDLK_s:
						this->teclaSApretada = false;
						break;
					case SDLK_a:
						this->teclaAApretada = false;
						break;
					default:
						break;
				}
				if (event.key.keysym.sym == SDLK_ESCAPE)
				quit = true;
			break;						   
			case SDL_QUIT:
				quit = true;
			break;
			default: break;
		}
	}	
}

int DetectorEventos::getPosicionMouseX(){
	return this->posicionMouseX;
}

int DetectorEventos::getPosicionMouseY(){
	return this->posicionMouseY;
}

int DetectorEventos::getClicMouseBotonIzquierdo(){
	return this->clicMouseBotonIzquierdo;
}

int DetectorEventos::getClicMouseBotonDerecho(){
	return this->clicMouseBotonDerecho;
}

bool DetectorEventos::getTeclaAApretada(){
	return this->teclaAApretada;
}

bool DetectorEventos::getTeclaSApretada(){
	return this->teclaSApretada;
}

DetectorEventos::~DetectorEventos(void){

}