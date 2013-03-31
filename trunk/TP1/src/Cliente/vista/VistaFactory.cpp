#include "VistaFactory.h"

VistaFactory::VistaFactory(void){
}

VistaFactory::~VistaFactory(void){
}

bool VistaFactory::crearVistaNivel(VistaNivel& vistaNivel){
/*	
	ParserYaml::stJuego juego;
	juego = ParserYaml::getInstance().cargarConfiguracionDeJuego();

	if( juego.juegoValido == false ) return false;
	
	this->crearJugadorConScroll(juego,modeloNivel);
	this->crearEntidades(juego,modeloNivel);
*/
	return true;
}

void VistaFactory::crearJugadorConScroll(ParserYaml::stJuego juego, VistaNivel& vistaNivel){

	return void();
}

void VistaFactory::crearEntidades(ParserYaml::stJuego juego, VistaNivel& vistaNivel){

	return void();
}
