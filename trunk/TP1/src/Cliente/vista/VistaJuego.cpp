#include "VistaJuego.h"

VistaJuego::VistaJuego(void){

}

bool VistaJuego::loop(){
	this->vistaLoop.loop();
	return true;
}

VistaJuego::~VistaJuego(void){

}

Observador* VistaJuego::obtenerObservadorScroll(void){
	return this->vistaNivel.obtenerObservadorScroll();
}

std::list<Observador*> VistaJuego::obtenerObservadoresEntidad(void){
	return this->vistaNivel.obtenerObservadoresEntidad();
}

bool VistaJuego::iniciar(void){
	return this->vistaFactory.crearVistaNivel(this->vistaNivel);
}

