#include "Servidor.h"

Servidor::Servidor(void){

}

Servidor::~Servidor(void){

}

bool Servidor::iniciar(void){
	// Acá le mando el pSocket y lo inicia adentro
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

bool Servidor::correrJuego(void){
	if( this->iniciar() == true ){
		this->loop();
		// TODO: ¿Acá cerraria todo lo de sockets? Ver eso
	}else{
		Log::getInstance().log(1,__FILE__,__LINE__,"Error al iniciar el juego el cliente.");
		return false;
	}
	return true;
}

void Servidor::destruirEntidades(void){
	this->modeloJuego.destruirEntidades();
}
