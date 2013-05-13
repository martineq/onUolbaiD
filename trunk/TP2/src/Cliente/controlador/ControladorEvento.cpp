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
	this->finalizoElJuego = false;
	this->teclaAApretada = false;
	this->teclaSApretada = false;
}

ControladorEvento::~ControladorEvento(void){
	if( this->controladorScroll != NULL ) delete this->controladorScroll;
	if( this->pProxyEvento != NULL ) delete this->pProxyEvento;
}

void ControladorEvento::setIdJugador(int id){
	this->idJugador = id;
}

void ControladorEvento::setPosicionMouseXY(int posicionX,int posicionY){
	this->posicionMouseX = posicionX;
	this->posicionMouseY = posicionY;
}

void ControladorEvento::setClicMouseBotonIzquierdo(int clic){
	this->clicMouseBotonIzquierdo = clic;
	this->notificarAlProxy();
}

void ControladorEvento::setClicMouseBotonDerecho(int clic){
	this->clicMouseBotonDerecho = clic;
	this->notificarAlProxy();
}

void ControladorEvento::setTeclaAApretada(bool apretada){
	this->teclaAApretada = apretada;
	this->notificarAlProxy();
}

void ControladorEvento::setTeclaSApretada(bool apretada){
	this->teclaSApretada = apretada;
	this->notificarAlProxy();
}

int ControladorEvento::getPosicionMouseX(){
	return this->posicionMouseX + this->controladorScroll->getX();
}

int ControladorEvento::getPosicionMouseY(){
	return this->posicionMouseY + this->controladorScroll->getY();
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

bool ControladorEvento::getTeclaAApretada(){
	return this->teclaAApretada;
}

bool ControladorEvento::getTeclaSApretada(){
	return this->teclaSApretada;
}

void ControladorEvento::notificarAlProxy(){

	// TODO: Tomar estos datos desde el chat
	int idReceptorChat = 0;
	std::string mensajeChat("nada");

	ProxyControladorEvento::stEvento evento;
	ProxyControladorEvento::cargarStEvento(evento, this->idJugador, false, this->getPosicionMouseX(), this->getPosicionMouseY(),
		this->getTeclaAApretada(), this->getTeclaSApretada(), (this->getClicMouseBotonIzquierdo() == 1), this->getFinalizoElJuego(),idReceptorChat,mensajeChat);
	this->pProxyEvento->enviarEvento(evento);
}

void ControladorEvento::setControladorScroll(ControladorScroll* controladorScroll, double anchoNivelEnPixel, double altoNivelEnPixel) {
	this->controladorScroll = controladorScroll;
	this->altoNivelEnPixel = altoNivelEnPixel;
	this->anchoNivelEnPixel = anchoNivelEnPixel;
}

ControladorScroll* ControladorEvento::getControladorScroll(void){
	return this->controladorScroll;
}

void ControladorEvento::setProxyEvento(ProxyControladorEvento* pProxyEvento){
	this->pProxyEvento = pProxyEvento;
}

ProxyControladorEvento* ControladorEvento::getProxyEvento(void){
	return this->pProxyEvento;
}

void ControladorEvento::setFinalizoElJuego(bool valor){
	this->finalizoElJuego = valor;
	return void();
}

bool ControladorEvento::getFinalizoElJuego(void){
	return this->finalizoElJuego;
}

void ControladorEvento::limpiar() {
	this->clicMouseBotonDerecho = 0;
	this->clicMouseBotonIzquierdo = 0;	
	this->teclaAApretada = false;
	this->teclaSApretada = false;
}
