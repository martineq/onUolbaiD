#include "ControladorEvento.h"

ControladorEvento::ControladorEvento(void){

}

ControladorEvento::~ControladorEvento(void){

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


void ControladorEvento::cambiarEstado(){
	this->notificarObservadores();
}
