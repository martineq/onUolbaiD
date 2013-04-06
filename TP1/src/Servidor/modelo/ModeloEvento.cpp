#include "ModeloEvento.h"

ModeloEvento::ModeloEvento() {
	this->_modeloNivel = NULL;
}

ModeloEvento::~ModeloEvento() {
}

void ModeloEvento::actualizar(Observable* observable) {
	ControladorEvento* controladorEvento = (ControladorEvento*)observable;
	
	// Avisa al scroll que se movio el mouse
	//TODO: implementar
	//this->_modeloNivel->moverScroll(controladorEvento->getPosicionMouseX(), controladorEvento->getPosicionMouseY());

	// Si se hizo clic con el boton derecho del mouse avisa al personaje que se mueva
	if (controladorEvento->getClicMouseBotonDerecho()) {
		int x = 0, y = 0;
		Posicion::convertirPixelATile(this->_modeloNivel->getAltoTiles(), controladorEvento->getPosicionMouseX(), controladorEvento->getPosicionMouseY(), x, y);
		//TODO: implementar
		//this->_modeloNivel->moverPersonaje(x, y);
	}
}

void ModeloEvento::asignarModeloNivel(ModeloNivel* modeloNivel) {
	this->_modeloNivel = modeloNivel;
}