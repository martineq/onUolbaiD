#include "./Administrador.h"

Administrador::Administrador(void){
	
}

Administrador::~Administrador(void){

}

void Administrador::iniciar(){
	// TODO: Tomar los booleanos del iniciar
	this->servidor.iniciar();
	this->cliente.iniciar();
	this->vincularObservadores();
}

// TODO: Completar loop con cliente y servidor
void Administrador::loop(){
	int fps = 50;
	int delay = 1000/fps;	
	bool quit = false;		
	while (!quit)
	{
		int tickViejo = SDL_GetTicks();		

		quit = this->cliente.loop();		
		
		int intervaloTranscurrido = SDL_GetTicks() - tickViejo;
		if (intervaloTranscurrido < delay){
			SDL_Delay(delay - intervaloTranscurrido);
		}
	}
}

void Administrador::vincularObservadores(void){

	// Agrego los eventos que observan
	this->cliente.agregarObservadorEventos(this->servidor.obtenerObservadorEvento());

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
	//p.PruebaYAML();	// Prueba YAML
	//p.PruebaModeloEntidad();
	//p.PruebaControladorJuego();
	//p.PruebaHilos();
}