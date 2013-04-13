#include "ModeloLoop.h"

using namespace std;

ModeloLoop::ModeloLoop() {
}

ModeloLoop::~ModeloLoop() {
}

Observador* ModeloLoop::obtenerObservadorEvento() {
	return &this->_modeloEvento;
}

bool ModeloLoop::loop(ModeloNivel& modeloNivel) {
	if (!this->_modeloEvento.getActualizado()) {
		int mousePosX = this->_modeloEvento.getMousePosX();
		int mousePosY = this->_modeloEvento.getMousePosY();

		//TODO: Verificar la lista de ids (TP2)
		modeloNivel.moverScroll(mousePosX, mousePosY, 0);

		if (this->_modeloEvento.getMouseClickDerecho() == 1)
			modeloNivel.moverJugador(mousePosX, mousePosY, 0);
	}

	modeloNivel.actualizar(0);

	this->_modeloEvento.setActualizado(false);

	return true;
}
