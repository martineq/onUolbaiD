#include "ControladorEvento.h"

ControladorEvento::ControladorEvento(void){
	this->posicionMouseX = 0;
	this->posicionMouseY = 0;
	this->clicMouseBotonDerecho = 0;
	this->clicMouseBotonIzquierdo = 0;	
	this->mouseDentroDePantalla = true;
}

ControladorEvento::~ControladorEvento(void){

}

void ControladorEvento::setMouseDentroDePantalla(bool dentroDePantalla){
	this->mouseDentroDePantalla = dentroDePantalla;
	if ( this->mouseDentroDePantalla == false) this->cambiarEstado();
}

void ControladorEvento::setPosicionMouseX(int posicion){
	this->posicionMouseX = posicion;
	this->cambiarEstado();
}

void ControladorEvento::setPosicionMouseY(int posicion){
	this->posicionMouseY = posicion;
	this->cambiarEstado();
}

void ControladorEvento::setPosicionMouseXY(int posicionX,int posicionY){
	this->posicionMouseX = posicionX;
	this->posicionMouseY = posicionY;
	this->cambiarEstado();
}

void ControladorEvento::setClicMouseBotonIzquierdo(int clic){
	this->clicMouseBotonIzquierdo = clic;
	this->cambiarEstado();
}

void ControladorEvento::setClicMouseBotonDerecho(int clic){
	this->clicMouseBotonDerecho = clic;
	this->cambiarEstado();
}

int ControladorEvento::getPosicionMouseX(){
	return this->posicionMouseX;
}

int ControladorEvento::getPosicionMouseY(){
	return this->posicionMouseY;
}

int ControladorEvento::getClicMouseBotonIzquierdo(){
	return this->clicMouseBotonIzquierdo;	
}

int ControladorEvento::getClicMouseBotonDerecho(){
	return this->clicMouseBotonDerecho;	
}

bool ControladorEvento::getMouseDentroDePantalla(){
	return this->mouseDentroDePantalla;
}


void ControladorEvento::cambiarEstado(){
	// TODO: Acá debo usar el ProxyControladorEvento
}
