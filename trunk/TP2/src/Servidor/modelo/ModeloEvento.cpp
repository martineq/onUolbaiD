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
	// TODO: Implementar estos métodos en ProxyControladorEvento
	// Y luego descomentar

	//ProxyControladorEvento* proxyControladorEvento = (ProxyControladorEvento*)observable;
	//this->setActualizado(true);
	//this->_mouseClickIzquierdo = proxyControladorEvento->getClicMouseBotonIzquierdo() == 1;
	//this->_mouseX = proxyControladorEvento->getPosicionMouseX();
	//this->_mouseY = proxyControladorEvento->getPosicionMouseY();
	//this->_mouseDentroPantalla = proxyControladorEvento->getMouseDentroDePantalla();
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
