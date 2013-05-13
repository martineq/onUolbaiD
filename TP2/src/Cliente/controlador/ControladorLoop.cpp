#include "ControladorLoop.h"

ControladorLoop::ControladorLoop() {
}

void ControladorLoop::loop() {
	this->detector.detectar();
	this->evento.limpiar();

	// Capturo eventos para el scroll
	if (!this->detector.getDentroDePantalla())
		this->evento.getControladorScroll()->detener();
	else
		this->evento.getControladorScroll()->actualizar(detector.getPosicionMouseX(), detector.getPosicionMouseY());
	this->evento.getControladorScroll()->cambiarEstado();

	// Caputro eventos para el servidor
	this->evento.setPosicionMouseXY(this->detector.getPosicionMouseX(), this->detector.getPosicionMouseY());
	if (this->detector.getClicMouseBotonIzquierdo() == 1)
		this->evento.setClicMouseBotonIzquierdo(this->detector.getClicMouseBotonIzquierdo());
	else if (this->detector.getTeclaAApretada())
		this->evento.setTeclaAApretada(this->detector.getTeclaAApretada());
	else if (this->detector.getTeclaSApretada())
		this->evento.setTeclaSApretada(this->detector.getTeclaSApretada());
}

bool ControladorLoop::getQuit() {
	return this->detector.getQuit();
}

ControladorEvento* ControladorLoop::getControladorEvento() {
	return &this->evento;
}

ControladorLoop::~ControladorLoop() {
}
