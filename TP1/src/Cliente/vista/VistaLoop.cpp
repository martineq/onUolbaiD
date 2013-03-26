#include "VistaLoop.h"

VistaLoop::VistaLoop(void){
}

VistaLoop::~VistaLoop(void){
}

void VistaLoop::levantarPantalla(){
	this->pantalla.levantar();
}

void VistaLoop::loop() {
	this->pantalla.dibujar();
}
