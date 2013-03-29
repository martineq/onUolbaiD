#include "ControladorLoop.h"

ControladorLoop::ControladorLoop(void){	
	this->posicionMouseXAnterior = 0;
	this->posicionMouseYAnterior = 0;
	this->clicMouseBotonDerechoAnterior = 0;
	this->clicMouseBotonIzquierdoAnterior = 0;
}

void ControladorLoop::loop(){	
	this->detector.detectar();

	if ((this->detector.getPosicionMouseX()!=this->posicionMouseXAnterior) && 
		(this->detector.getPosicionMouseY()!=this->posicionMouseYAnterior)){
			this->evento.setPosicionMouseXY(this->detector.getPosicionMouseX(),this->detector.getPosicionMouseY());
			this->posicionMouseXAnterior = detector.getPosicionMouseX();
			this->posicionMouseYAnterior = detector.getPosicionMouseY();
	}
	else if (this->detector.getPosicionMouseX()!=this->posicionMouseXAnterior) {
		this->evento.setPosicionMouseX(this->detector.getPosicionMouseX());
		this->posicionMouseXAnterior = detector.getPosicionMouseX();
	}
	else if (this->detector.getPosicionMouseY()!=this->posicionMouseYAnterior) {
		this->evento.setPosicionMouseY(this->detector.getPosicionMouseY());
		this->posicionMouseYAnterior = detector.getPosicionMouseY();
	}
	if (this->detector.getClicMouseBotonIzquierdo()!=this->clicMouseBotonIzquierdoAnterior) {
		this->evento.setClicMouseBotonIzquierdo(this->detector.getClicMouseBotonIzquierdo());
		this->clicMouseBotonIzquierdoAnterior = detector.getClicMouseBotonIzquierdo();
	}
	if (this->detector.getClicMouseBotonDerecho()!=this->clicMouseBotonDerechoAnterior) {
		this->evento.setClicMouseBotonDerecho(this->detector.getClicMouseBotonDerecho());
		this->clicMouseBotonDerechoAnterior = detector.getClicMouseBotonDerecho();
	}
}

bool ControladorLoop::getQuit(){
	return this->detector.getQuit();
}



ControladorLoop::~ControladorLoop(void){

}

void ControladorLoop::agregarObservadorEventos(Observador* observador){
	this->evento.agregarObservador(observador);
}

