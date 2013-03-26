#include "DetectorEventos.h"

DetectorEventos::DetectorEventos(void){
	this->quit = false;
}

DetectorEventos::~DetectorEventos(void){
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
			case SDL_MOUSEMOTION:
				// update mouse position
				UIState::getInstancia().mousex = event.motion.x;
				UIState::getInstancia().mousey = event.motion.y;
			break;
			case SDL_MOUSEBUTTONDOWN:
				// update button down state if left-clicking
				if (event.button.button == 1)
				UIState::getInstancia().mousedown = 1;
			break;
			case SDL_MOUSEBUTTONUP:
				// update button down state if left-clicking
				if (event.button.button == 1)
				UIState::getInstancia().mousedown = 0;
			break;
			case SDL_KEYUP:
				if ( event.key.keysym.sym == SDLK_ESCAPE )
				quit = true;
			break;
			case SDL_QUIT:
				quit = true;
			break;
			default: break;
		}
	}
}
