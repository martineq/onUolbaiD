#include "ModeloMision.h"

void ModeloMision::asignarGanador(ModeloJugador* ganador) {
	this->_ganador = ganador;
}

ModeloMision::ModeloMision() {
	this->_ganador = NULL;
}

ModeloMision::~ModeloMision() {
}

ModeloJugador* ModeloMision::ganador() {
	return this->_ganador;
}
