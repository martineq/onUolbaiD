#include "ControladorJuego.h"

ControladorJuego::ControladorJuego(void){
}

ControladorJuego::~ControladorJuego(void){
}

void ControladorJuego::loop(){
	this->detector.detectar();
}

bool ControladorJuego::getQuit(){
	return this->detector.getQuit();
}
