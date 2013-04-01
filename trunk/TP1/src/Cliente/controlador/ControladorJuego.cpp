#include "ControladorJuego.h"

ControladorJuego::ControladorJuego(void){

}

ControladorJuego::~ControladorJuego(void){

}

bool ControladorJuego::loop(){
	//lo hace detectar y carga el vector de eventos
	this->controladorLoop.loop();	
	//se fija si preciono ESC o la X de la ventana
	return this->controladorLoop.getQuit();	
}

void ControladorJuego::agregarObservadorEventos(Observador* observador){
	this->controladorLoop.agregarObservadorEventos(observador);
	return void();
}

bool ControladorJuego::iniciar(void){
	// TODO: Implementar. Ver si hace falta
	return false;
}
