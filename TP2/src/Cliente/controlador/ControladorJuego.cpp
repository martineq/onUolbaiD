#include "ControladorJuego.h"

ControladorJuego::ControladorJuego(void){

}

ControladorJuego::~ControladorJuego(void){

}

bool ControladorJuego::loop(){
	//lo hace detectar y carga el vector de eventos
	this->controladorLoop.loop();	
	//se fija si preciono ESC o la X de la ventana
	if (this->controladorLoop.getQuit() == true) return false;
	else return true;
}

void ControladorJuego::agregarObservadorScroll(Observador* observadorScroll){
	this->controladorLoop.agregarObservadorScroll(observadorScroll);
	return void();
}