#include "./VistaJuego.h"

VistaJuego::VistaJuego(void){

}

VistaJuego::~VistaJuego(void){

}

Observador* VistaJuego::obtenerObservadorScroll(void){
	return this->vistaNivel.obtenerObservadorScroll();
}

bool VistaJuego::iniciar(void){
	// TODO: Por acá aparecerá todo el diálogo de sockets para obtener archivos del servidor y config final
	if( this->vistaFactory.crearVistaNivel(this->vistaNivel,this->vistaLoop) == false ) return false;
	return true;
}

bool VistaJuego::loop(){
	return this->vistaLoop.loop(this->vistaNivel);
}

void VistaJuego::destruirEntidades(){
	this->vistaNivel.destruirEntidadesYScroll();
}