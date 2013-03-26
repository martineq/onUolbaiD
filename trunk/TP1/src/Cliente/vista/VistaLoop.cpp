#include "VistaLoop.h"

VistaLoop::VistaLoop(void){
}

VistaLoop::~VistaLoop(void){
}

void VistaLoop::levantarPantalla(){
	this->pantalla.levantar();
}

void VistaLoop::loop(std::vector<int> eventos) {
	this->pantalla.dibujar(eventos);
}
