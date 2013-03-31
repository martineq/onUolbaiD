#include "./VistaJuego.h"

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
	if( this->vistaFactory.crearVistaNivel(this->vistaNivel) == false ) return false;
	//if( this->vistaNivel.levantarPantalla() ) return false; // TODO: Ver donde se llama a este método
	return true;
}

bool VistaJuego::loop(){
	return this->vistaLoop.loop(this->vistaNivel);	// El return tiene que venir del this->vistaLoop.loop();
}