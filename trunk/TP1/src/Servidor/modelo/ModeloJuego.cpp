#include "ModeloJuego.h"

ModeloJuego::ModeloJuego() {
	this->_modeloLoop.asignarModeloNivel(&this->_modeloNivel);
}

ModeloJuego::~ModeloJuego() {
}

bool ModeloJuego::iniciar() {
	return this->_modeloFactory.crearModeloNivel(this->_modeloNivel);
}

void ModeloJuego::agregarObservadoresScroll(std::list<Observador*> listaObservadoresScroll){
	this->_modeloNivel.agregarObservadoresScroll(listaObservadoresScroll);
}

void ModeloJuego::agregarObservadoresEntidad(std::list<Observador*> listaObservadoresEntidad){
	this->_modeloNivel.agregarObservadoresEntidad(listaObservadoresEntidad);
}

Observador* ModeloJuego::obtenerObservadorEvento() {
	return this->_modeloLoop.obtenerObservadorEvento();
}

bool ModeloJuego::loop() {
	return this->_modeloLoop.loop();
}
