#include "ControladorJuego.h"

ControladorJuego::ControladorJuego(void){
}

ControladorJuego::~ControladorJuego(void){
}

bool ControladorJuego::loop(VistaChat* vistaChat, VistaNivel* nivel) {
	//lo hace detectar y carga el vector de eventos
	this->controladorLoop.loop(vistaChat, nivel);	
	//se fija si preciono ESC o la X de la ventana
	if (this->controladorLoop.getQuit() == true) return false;
	else return true;
}

ControladorLoop* ControladorJuego::getControladorLoop(void){
	return (&(this->controladorLoop));
}