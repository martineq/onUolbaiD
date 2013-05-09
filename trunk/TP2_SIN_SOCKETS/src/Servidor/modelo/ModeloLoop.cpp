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
	if (this->_modeloEvento.getActualizado()) {
		int mousePosX = this->_modeloEvento.getMousePosX();
		int mousePosY = this->_modeloEvento.getMousePosY();

		/*if (((modeloNivel.getAccionJugador() == 1) || (modeloNivel.getAccionJugador() == 2)) && (GetTickCount() - modeloNivel.getTicksJugador() > DELAY_ACCIONES_PERSONAJE))
			modeloNivel.setAccionJugador(0);*/

		//TODO: Verificar la lista de ids (TP2)
		if (this->_modeloEvento.getMouseDentroPantalla())
			modeloNivel.moverScroll(mousePosX, mousePosY, 0);
		else
			modeloNivel.detenerScroll(0);

		if ((modeloNivel.getAccionJugador() != 1) && (modeloNivel.getAccionJugador() != 2)) {

			if (this->_modeloEvento.getMouseClickIzquierdo())
				modeloNivel.moverJugador(mousePosX, mousePosY, 0);

			if (this->_modeloEvento.getTeclaA()) {
				modeloNivel.jugadorAtacar();
			}

			if (this->_modeloEvento.getTeclaS()) {
				modeloNivel.jugadorDefender();
			}
		}
	}

	modeloNivel.actualizar(0);

	this->_modeloEvento.setActualizado(false);

	return true;
}
