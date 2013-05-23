#include "ControladorJuego.h"

ControladorJuego::ControladorJuego(void){
}

ControladorJuego::~ControladorJuego(void){
}

bool ControladorJuego::loop(VistaNivel* nivel) {
	//lo hace detectar y carga el vector de eventos
	this->controladorLoop.loop(nivel);	
	//se fija si preciono ESC o la X de la ventana
	if (this->controladorLoop.getQuit() == true) return false;
	else return true;
}

ControladorLoop* ControladorJuego::getControladorLoop(void){
	return (&(this->controladorLoop));
}

void ControladorJuego::asignarChat(VistaChat* vistaChat) {
	this->controladorLoop.asignarChat(vistaChat);
}
