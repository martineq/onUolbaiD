#include "./Cliente.h"

Cliente::Cliente(void){

}

Cliente::~Cliente(void){

}

bool Cliente::iniciar(void){
	return this->vistaJuego.iniciar();
}

Observador* Cliente::obtenerObservadorScroll(void){
	return this->vistaJuego.obtenerObservadorScroll();
}

std::list<Observador*> Cliente::obtenerObservadoresEntidad(void){
	return this->vistaJuego.obtenerObservadoresEntidad();
}

void Cliente::agregarObservadorEventos(Observador*){

	return void();
}

bool Cliente::loop(void){
	// TODO: los dos loop tienen que ser evaluados por true o false
	bool quit = this->controladorJuego.loop();
	this->vistaJuego.loop(); // TODO: evaluar bool
	return quit;
	
	/*if( this->controladorJuego.loop() == true && this->vistaJuego.loop() == true){
		return true;
	}else{
		return false;
	}*/
}
