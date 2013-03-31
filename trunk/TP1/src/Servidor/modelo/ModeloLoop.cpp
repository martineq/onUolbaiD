#include "ModeloLoop.h"

ModeloLoop::ModeloLoop() {
}

ModeloLoop::~ModeloLoop() {
}

Observador* ModeloLoop::obtenerObservadorEvento() {
	return &this->_modeloEvento;
}

void ModeloLoop::asignarModeloNivel(ModeloNivel* modeloNivel) {
	this->_modeloEvento.asignarModeloNivel(modeloNivel);
}

bool ModeloLoop::loop() {
	// Como por ahora el nivel no tiene ningun comportamiento y
	// ModeloEvento es el que se encarga de mover al personaje,
	// esto no hace nada y siempre devuelve true
	return true;
}
