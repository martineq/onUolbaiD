#include "ModeloEvento.h"

ModeloEvento::ModeloEvento() {
	this->_modeloNivel = NULL;
	this->actualizado = false;
}

ModeloEvento::~ModeloEvento() {
}

bool ModeloEvento::getActualizado(void){
	return this->actualizado;
}

void ModeloEvento::setActualizado(bool actualizado){
	this->actualizado = actualizado;
}


void ModeloEvento::actualizar(Observable* observable) {
	ControladorEvento* controladorEvento = (ControladorEvento*)observable;
	this->setActualizado(true);

	// Avisa al scroll que se movio el mouse
	//TODO: implementar
	//this->_modeloNivel->moverScroll(controladorEvento->getPosicionMouseX(), controladorEvento->getPosicionMouseY());

	// Si se hizo clic con el boton derecho del mouse avisa al personaje que se mueva
	//if (controladorEvento->getClicMouseBotonDerecho()) {
		//int x = 0, y = 0;
		//Posicion::convertirPixelATile(this->_modeloNivel->getAltoTiles(), controladorEvento->getPosicionMouseX(), controladorEvento->getPosicionMouseY(), x, y);
		//TODO: implementar
		//this->_modeloNivel->moverPersonaje(x, y);
	//}

	this->mouseClickDerecho = controladorEvento->getClicMouseBotonDerecho();
	Posicion::convertirPixelATile(this->_modeloNivel->getAltoTiles(), controladorEvento->getPosicionMouseX(), controladorEvento->getPosicionMouseY(), this->mousePosX, this->mousePosY);

}

void ModeloEvento::asignarModeloNivel(ModeloNivel* modeloNivel) {
	this->_modeloNivel = modeloNivel;
}

int ModeloEvento::getMouseClickDerecho() {
	return this->mouseClickDerecho;
}

int ModeloEvento::getMousePosX() {
	return this->mousePosX;
}


int ModeloEvento::getMousePosY() {
	return this->mousePosX;
}
