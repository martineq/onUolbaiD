#include "ControladorLoop.h"

ControladorLoop::ControladorLoop(void){	
	loopInicial = true;
	this->posicionMouseXAnterior = 0;
	this->posicionMouseYAnterior = 0;
	this->clicMouseBotonDerechoAnterior = 0;
	this->clicMouseBotonIzquierdoAnterior = 0;
	this->dentroDePantalla = true;
	this->teclaAApretada = false;
	this->teclaSApretada = false;
}

void ControladorLoop::loop(){	

	if( this->loopInicial == true ){
		this->evento.setPosicionMouseXY(this->detector.getPosicionMouseX(),this->detector.getPosicionMouseY());
		this->loopInicial = false;
		return void();
	}

	this->detector.detectar();

	if ( this->detector.getDentroDePantalla() == false ) {
		this->evento.setMouseDentroDePantalla(false);
		return void();
	}
	else this->evento.setMouseDentroDePantalla(true);

	if ((this->detector.getPosicionMouseX()!=this->posicionMouseXAnterior) && 
		(this->detector.getPosicionMouseY()!=this->posicionMouseYAnterior)){
			this->evento.setPosicionMouseXY(this->detector.getPosicionMouseX(),this->detector.getPosicionMouseY());
			this->evento.setClicMouseBotonIzquierdo(0); // Con esto aclaro que no estoy mandando un evento de click
			this->evento.setClicMouseBotonDerecho(0);   // Con esto aclaro que no estoy mandando un evento de click
			this->posicionMouseXAnterior = detector.getPosicionMouseX();
			this->posicionMouseYAnterior = detector.getPosicionMouseY();
	}

	else if (this->detector.getPosicionMouseX()!=this->posicionMouseXAnterior) {
		this->evento.setPosicionMouseX(this->detector.getPosicionMouseX());
		this->evento.setClicMouseBotonIzquierdo(0);  // Con esto aclaro que no estoy mandando un evento de click
		this->evento.setClicMouseBotonDerecho(0);    // Con esto aclaro que no estoy mandando un evento de click
		this->posicionMouseXAnterior = detector.getPosicionMouseX();
	}

	else if (this->detector.getPosicionMouseY()!=this->posicionMouseYAnterior) {
		this->evento.setPosicionMouseY(this->detector.getPosicionMouseY());
		this->evento.setClicMouseBotonIzquierdo(0); // Con esto aclaro que no estoy mandando un evento de click
		this->evento.setClicMouseBotonDerecho(0);   // Con esto aclaro que no estoy mandando un evento de click
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

	if (this->detector.getTeclaAApretada()!=this->teclaAApretada){
		this->evento.setTeclaAApretada(this->detector.getTeclaAApretada());
		this->teclaAApretada = this->detector.getTeclaAApretada();
	}

	if (this->detector.getTeclaSApretada()!=this->teclaSApretada){
		this->evento.setTeclaSApretada(this->detector.getTeclaSApretada());
		this->teclaSApretada = this->detector.getTeclaSApretada();
	}
}

bool ControladorLoop::getQuit(){
	return this->detector.getQuit();
}

ControladorEvento* ControladorLoop::getControladorEvento(void){
	return (&(this->evento));
}

ControladorLoop::~ControladorLoop(void){

}
