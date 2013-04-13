#include "./VistaJuego.h"

VistaJuego::VistaJuego(void){

}

VistaJuego::~VistaJuego(void){

}

Observador* VistaJuego::obtenerObservadorJugador(void){
	return this->vistaNivel.obtenerObservadorJugador();
}

Observador* VistaJuego::obtenerObservadorScroll(void){
	return this->vistaNivel.obtenerObservadorScroll();
}

std::list<Observador*> VistaJuego::obtenerObservadoresEntidad(void){
	return this->vistaNivel.obtenerObservadoresEntidad();
}

bool VistaJuego::iniciar(void){
	if( this->vistaFactory.crearVistaNivel(this->vistaNivel,this->vistaLoop) == false ) return false;
	if( this->vistaLoop.levantarFondo(this->vistaNivel.getAltoPantalla(),this->vistaNivel.getAnchoPantalla()) == false ) return false;
	return true;
}

bool VistaJuego::loop(){
	return this->vistaLoop.loop(this->vistaNivel);	// El return tiene que venir del this->vistaLoop.loop();
}

void VistaJuego::destruirEntidades(){
	this->vistaNivel.destruirEntidadesYScroll();
}