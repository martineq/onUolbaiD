#include "ControladorJuego.h"

ControladorJuego::ControladorJuego(void){

}

ControladorJuego::~ControladorJuego(void){

}


void ControladorJuego::agregarObservadorEventos(Observador*){
	// TODO: Implementar
}

bool ControladorJuego::iniciar(void){
	// TODO: Implementar. Ver si hace falta
	return false;
}

bool ControladorJuego::loop(void){
	return this->controladorLoop.loop();
}
