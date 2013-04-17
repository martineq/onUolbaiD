#include "ModeloEvento.h"

using namespace std;

ModeloEvento::ModeloEvento() {
	this->_mouseClickIzquierdo = 0;
	this->_mouseX = 0;
	this->_mouseY = 0;
	this->_actualizado = false;
}

ModeloEvento::~ModeloEvento() {
}

bool ModeloEvento::getActualizado() {
	return this->_actualizado;
}

void ModeloEvento::setActualizado(bool actualizado) {
	this->_actualizado = actualizado;
}

void ModeloEvento::actualizar(Observable* observable) {
	ControladorEvento* controladorEvento = (ControladorEvento*)observable;
	this->setActualizado(true);
	this->_mouseClickIzquierdo = controladorEvento->getClicMouseBotonIzquierdo() == 1;
	this->_mouseX = controladorEvento->getPosicionMouseX();
	this->_mouseY = controladorEvento->getPosicionMouseY();
	this->_mouseDentroPantalla = controladorEvento->getMouseDentroDePantalla();
}

bool ModeloEvento::getMouseClickIzquierdo() {
	return this->_mouseClickIzquierdo;
}

bool ModeloEvento::getMouseDentroPantalla() {
	return this->_mouseDentroPantalla;
}

int ModeloEvento::getMousePosX() {
	return this->_mouseX;
}

int ModeloEvento::getMousePosY() {
	return this->_mouseY;
}
