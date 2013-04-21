#include "Servidor.h"

Servidor::Servidor(void){

}

Servidor::~Servidor(void){

}

bool Servidor::iniciar(void){
	return this->modeloJuego.iniciar();
}

void Servidor::loop(void){
	// TODO: Ver si el while queda acá
	int fps = 50;
	int delay = 1000/fps;	
	bool quit = false;		
	while (quit == false){
		int tickViejo = SDL_GetTicks();		

		if( this->modeloJuego.loop() == false) quit = true;
	
		int intervaloTranscurrido = SDL_GetTicks() - tickViejo;
		if (intervaloTranscurrido < delay){
			SDL_Delay(delay - intervaloTranscurrido);
		}
	}
	 	 
	 return void();
}

void Servidor::destruirEntidades(void){
	this->modeloJuego.destruirEntidades();
}
