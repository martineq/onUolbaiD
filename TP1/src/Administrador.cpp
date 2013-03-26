#include "Administrador.h"

Administrador::Administrador(void){

}

Administrador::~Administrador(void){
}

// Dani
void Administrador::loopPrincipal(){	
	int fps = 50;
	int delay = 1000/fps;	
	bool quit = false;	
	this->vistaLoop.levantarPantalla();
	while (!quit)
	{
		int tickViejo = SDL_GetTicks();
		
		//por ahora solo detecta mouse
		this->controlador.loop();
		quit = this->controlador.getQuit();
		
		//por ahora solo dibuja
		this->vistaLoop.loop();		
		
		int intervaloTranscurrido = SDL_GetTicks() - tickViejo;
		if (intervaloTranscurrido < delay){
			SDL_Delay(delay - intervaloTranscurrido);
		}
	}

}

void Administrador::correrPruebas(void){

	Pruebas p;
	//p.PruebaSdl(); // Prueba SDL + log
	//p.PruebaYAML();	// Prueba YAML
	//p.PruebaModeloEntidad();
	p.PruebaControladorJuego();

}
