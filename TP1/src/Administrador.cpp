#include "./Administrador.h"

Administrador::Administrador(void){

}

Administrador::~Administrador(void){
	this->servidor.destruirEntidades();
	this->cliente.destruirEntidades();
}

bool Administrador::iniciar(){
	
	// TODO: Tomar los booleanos del iniciar
	if( this->servidor.iniciar() == false ){
		Log::getInstance().log(1,__FILE__,__LINE__,"No se pudo iniciar el juego");
		return false;
	}

	if( this->cliente.iniciar() == false ){
		Log::getInstance().log(1,__FILE__,__LINE__,"No se pudo iniciar el juego");
		return false;
	}

	this->vincularObservadores();

	return true;
}

// TODO: Completar loop con cliente y servidor
void Administrador::loop(){
	int fps = 50;
	int delay = 1000/fps;	
	bool quit = false;		
	while (quit == false){
		int tickViejo = SDL_GetTicks();		

		if( this->cliente.loopControl() == false)  
			quit = true;
		if( this->servidor.loop() == false ) 
			quit = true;
		if( this->cliente.loopVista() == false ) 
			quit = true;

		int intervaloTranscurrido = SDL_GetTicks() - tickViejo;
		if (intervaloTranscurrido < delay){
			SDL_Delay(delay - intervaloTranscurrido);
		}
	}
}

void Administrador::vincularObservadores(void){

	// Agrego los eventos que observan
	this->cliente.agregarObservadorEventos(this->servidor.obtenerObservadorEvento());

	// Agrego los jugadores que observan
	std::list<Observador*> listaObservadoresJugador;	// En el futuro habra mas de un cliente, por eso es una lista
	listaObservadoresJugador.push_back(this->cliente.obtenerObservadorJugador());
	this->servidor.agregarObservadoresJugador(listaObservadoresJugador);

	// Agrego las entidades que observan
	this->servidor.agregarObservadoresEntidad(this->cliente.obtenerObservadoresEntidad());

	// Agrego los scroll que observan
	std::list<Observador*> listaObservadoresScroll;	// En el futuro habra mas de un cliente, por eso es una lista
	listaObservadoresScroll.push_back(this->cliente.obtenerObservadorScroll());
	this->servidor.agregarObservadoresScroll(listaObservadoresScroll);

}

void Administrador::correrPruebas(void){

	Pruebas p;
	//p.PruebaSdl(); // Prueba SDL + log
	p.PruebaYAML();	// Prueba YAML
	//p.PruebaModeloEntidad();
	//p.PruebaControladorJuego();
	//p.PruebaHilos();
}
