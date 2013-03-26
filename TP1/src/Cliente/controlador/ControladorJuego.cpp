#include "ControladorJuego.h"

ControladorJuego::ControladorJuego(void){
	this->eventos.push_back(0);
	this->eventos.push_back(0);
	this->eventos.push_back(0);
	this->eventos.push_back(0);
}

ControladorJuego::~ControladorJuego(void){

}

void ControladorJuego::loop(){
	this->eventos.pop_back();
	this->eventos.pop_back();
	this->eventos.pop_back();
	this->eventos.pop_back();
	this->detector.detectar();
	this->eventos.push_back(this->detector.posicionMouseX);
	this->eventos.push_back(this->detector.posicionMouseY);
	this->eventos.push_back(this->detector.clicMouseBotonIzquierdo);
	this->eventos.push_back(this->detector.clicMouseBotonDerecho);
}

std::vector <int> ControladorJuego::getEventos () {
	return this->eventos;
}

bool ControladorJuego::getQuit(){
	return this->detector.getQuit();
}

