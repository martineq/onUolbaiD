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

bool ModeloLoop::loop(ModeloNivel& modeloNivel){
	// TODO: Implementar
	return true;
}
