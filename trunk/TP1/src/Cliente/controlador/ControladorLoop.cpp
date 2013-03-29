#include "ControladorLoop.h"

ControladorLoop::ControladorLoop(void){

}

ControladorLoop::~ControladorLoop(void){

}

void ControladorLoop::agregarObservadorEventos(Observador* observador){
	this->evento.agregarObservador(observador);
}

bool ControladorLoop::loop(void){

	// TODO: implementar
	return false;
}