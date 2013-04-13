#include "DetectorEventos.h"

DetectorEventos::DetectorEventos(void){
	this->quit = false;
	this->posicionMouseX = 0;
	this->posicionMouseY = 0;
	this->clicMouseBotonDerecho = 0;
	this->clicMouseBotonIzquierdo = 0;
}

bool DetectorEventos::getQuit() {
	return this->quit;
}

void DetectorEventos::detectar(){
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
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
			// presiono escape
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				quit = true;
			break;
			// hago clic en la ventana para cerrarla
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

DetectorEventos::~DetectorEventos(void){

}