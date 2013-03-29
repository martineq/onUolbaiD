#include "ModeloJuego.h"

ModeloJuego::ModeloJuego(void){

}

ModeloJuego::~ModeloJuego(void){

}

bool ModeloJuego::iniciar(void){
	return this->modeloFactory.crearModeloNivel(this->modeloNivel);
}

void ModeloJuego::agregarObservadoresScroll(std::list<Observador*> listaObservadoresScroll){
	this->modeloNivel.agregarObservadoresScroll(listaObservadoresScroll);
}

void ModeloJuego::agregarObservadoresEntidad(std::list<Observador*> listaObservadoresEntidad){
	this->modeloNivel.agregarObservadoresEntidad(listaObservadoresEntidad);
}

Observador* ModeloJuego::obtenerObservadorEvento(void){
	return this->modeloLoop.obtenerObservadorEvento();
}

bool ModeloJuego::loop(void){
	return this->modeloLoop.loop();
}

