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

bool ModeloLoop::loop(ModeloNivel& modeloNivel) {
	if (this->_modeloEvento.getActualizado() == true) {
		int mousePosX = this->_modeloEvento.getMousePosX();
		int mousePosY = this->_modeloEvento.getMousePosY();

		std::list<ModeloScroll*> listaScroll = modeloNivel.getListaScroll();
		
		for (std::list<ModeloScroll*>::iterator it = listaScroll.begin(); it != listaScroll.end(); it++) {
			ModeloScroll* scroll = *it;

			//TODO: Verificar la lista de ids (TP2)
			if (scroll->enMargen(mousePosX, mousePosY) == true)
				scroll->actualizar(mousePosX, mousePosY);
		}

		// Si se hizo clic con el boton derecho del mouse avisa al personaje que se mueva
		if (this->_modeloEvento.getMouseClickDerecho()) {
			int x = 0, y = 0;
			Posicion::convertirPixelATile(modeloNivel.getAltoTiles(),mousePosX,mousePosY, x, y);
			modeloNivel.moverJugador(x, y, 0);
		}
	}

	this->_modeloEvento.setActualizado(false);

	return true;
}
