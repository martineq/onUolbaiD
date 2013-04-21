#include "./Cliente.h"

Cliente::Cliente(void){

}

Cliente::~Cliente(void){

}

bool Cliente::iniciar(void){
	
	// Instancia el nivel en vistaJuego
	if( this->vistaJuego.iniciar() == false ) return false;
	this->controladorJuego.agregarObservadorScroll(this->vistaJuego.obtenerObservadorScroll());
	return true;
}

void Cliente::loop(void){
	// TODO: Ver si el while queda acá
	int fps = 50;
	int delay = 1000/fps;	
	bool quit = false;		
	while (quit == false){
		int tickViejo = SDL_GetTicks();		

		if( this->controladorJuego.loop() == false) quit = true;
		if( this->vistaJuego.loop() == false) quit = true;

		int intervaloTranscurrido = SDL_GetTicks() - tickViejo;
		if (intervaloTranscurrido < delay){
			SDL_Delay(delay - intervaloTranscurrido);
		}
	}
	 	 
	 return void();
}


void Cliente::destruirEntidades(void){
	return this->vistaJuego.destruirEntidades();
}


