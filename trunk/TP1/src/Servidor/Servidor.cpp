#include "Servidor.h"

Servidor::Servidor(void){

}

Servidor::~Servidor(void){

}

bool Servidor::iniciar(void){
	return this->modeloJuego.iniciar();
}

void Servidor::agregarObservadoresJugador(std::list<Observador*>listaObservadoresJugador){
	this->modeloJuego.agregarObservadoresJugador(listaObservadoresJugador);
}

void Servidor::agregarObservadoresScroll(std::list<Observador*> listaObservadoresScroll){
	this->modeloJuego.agregarObservadoresScroll(listaObservadoresScroll);
}

void Servidor::agregarObservadoresEntidad(std::list<Observador*> listaObservadoresEntidad){
	this->modeloJuego.agregarObservadoresEntidad(listaObservadoresEntidad);
}

Observador* Servidor::obtenerObservadorEvento(void){
	return this->modeloJuego.obtenerObservadorEvento();
}

bool Servidor::loop(void){
	return this->modeloJuego.loop();
}

void Servidor::destruirEntidades(void){
	this->modeloJuego.destruirEntidades();
}
