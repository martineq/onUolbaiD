#include "VistaJuego.h"

VistaJuego::VistaJuego(void){

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

bool VistaJuego::loop(void){
	return this->vistaLoop.loop();
}
