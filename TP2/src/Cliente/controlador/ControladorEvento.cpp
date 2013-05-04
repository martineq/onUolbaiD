#include "ControladorEvento.h"

ControladorEvento::ControladorEvento(void){
	this->idJugador = -1;
	this->posicionMouseX = 0;
	this->posicionMouseY = 0;
	this->clicMouseBotonDerecho = 0;
	this->clicMouseBotonIzquierdo = 0;	
	this->mouseDentroDePantalla = true;
	this->controladorScroll = NULL;
	this->pProxyEvento = NULL;
}

ControladorEvento::~ControladorEvento(void){
	if( this->controladorScroll != NULL ) delete this->controladorScroll;
	if( this->pProxyEvento != NULL ) delete this->pProxyEvento;
}

void ControladorEvento::setIdJugador(int id){
	this->idJugador = id;
}

void ControladorEvento::setMouseDentroDePantalla(bool dentroDePantalla){
	this->mouseDentroDePantalla = dentroDePantalla;
	if ( this->mouseDentroDePantalla == false) this->notificarAlProxy();
}

void ControladorEvento::setPosicionMouseX(int posicion){
	this->posicionMouseX = posicion;
	this->notificarAlProxy();
}

void ControladorEvento::setPosicionMouseY(int posicion){
	this->posicionMouseY = posicion;
	this->notificarAlProxy();
}

void ControladorEvento::setPosicionMouseXY(int posicionX,int posicionY){
	this->posicionMouseX = posicionX;
	this->posicionMouseY = posicionY;
	this->notificarAlProxy();
}

void ControladorEvento::setClicMouseBotonIzquierdo(int clic){
	this->clicMouseBotonIzquierdo = clic;
	this->notificarAlProxy();
}

void ControladorEvento::setClicMouseBotonDerecho(int clic){
	this->clicMouseBotonDerecho = clic;
	this->notificarAlProxy();
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

void ControladorEvento::notificarAlProxy(){
	ProxyControladorEvento::stEvento evento;
	evento.id = this->idJugador;
	evento.mouseX = this->getPosicionMouseX();
	evento.mouseY = this->getPosicionMouseY();
	evento.mouseClickIzquierdo = (this->getClicMouseBotonIzquierdo() == 1 );
	evento.mouseDentroPantalla = this->getMouseDentroDePantalla();
	// TODO: Falta agregar:
	//evento.teclaA = this->getTeclaAApretada();
	//evento.teclaS = this->getTeclaSApretada();
	this->pProxyEvento->enviarEvento(evento);
}

void ControladorEvento::setControladorScroll(ControladorScroll* controladorScroll) {
	this->controladorScroll = controladorScroll;
}

ControladorScroll* ControladorEvento::getControladorScroll(void){
	return this->controladorScroll;
}

void ControladorEvento::setProxyEvento(ProxyControladorEvento* pProxyEvento){
	this->pProxyEvento;
}

ProxyControladorEvento* ControladorEvento::getProxyEvento(void){
	return this->pProxyEvento;
}