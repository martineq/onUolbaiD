#include "./VistaNivel.h"


VistaNivel::VistaNivel(){

}

VistaNivel::~VistaNivel(){
/*
	// Destruyo las entidades instanciadas (incluye al personaje)
	for (std::list<VistaEntidad*>::iterator entidad = this->listaEntidades.begin(); entidad != this->listaEntidades.end(); entidad++){
		delete (*entidad);
	}

	// Destruyo el scroll
	delete this->scroll;
*/
}

Observador* VistaNivel::obtenerObservadorJugador(void){
	Observador* pObservador;

	for (std::list<VistaEntidad*>::iterator it=this->listaEntidades.begin() ; it != this->listaEntidades.end(); it++ ){
		if( (*it)->getEsJugador() == false ){
			pObservador = ((Observador*)*it);
		}
	}
	return pObservador;
}

Observador* VistaNivel::obtenerObservadorScroll(void){
	return (Observador*)this->scroll;
}

std::list<Observador*> VistaNivel::obtenerObservadoresEntidad(void){

	std::list<Observador*> listaObservadoresEntidad;

	for (std::list<VistaEntidad*>::iterator it=this->listaEntidades.begin() ; it != this->listaEntidades.end(); it++ ){
		if( (*it)->getEsJugador() == false ){
			listaObservadoresEntidad.push_back( ((Observador*)*it) );
		}
	}

	return listaObservadoresEntidad;

}

VistaScroll* VistaNivel::getScroll(void){
	return this->scroll;
}

std::list<VistaEntidad*> VistaNivel::getListaEntidades(void){
	return this->listaEntidades;
}

void VistaNivel::agregarJugador(VistaEntidad* pJugador){
	this->listaEntidades.push_back(pJugador);
	return void();
}

void VistaNivel::agregarEntidad(VistaEntidad* pEntidad){
	this->listaEntidades.push_back(pEntidad);
	return void();
}

void VistaNivel::agregarScroll(VistaScroll* pScroll){
	this->scroll = pScroll;
	return void();
}

int VistaNivel::getAltoPantalla(void){
	return this->alto;
}

int VistaNivel::getAnchoPantalla(void){
	return this->ancho;
}

void VistaNivel::setAltoPantalla(int alto){
	this->alto = alto;
}

void VistaNivel::setAnchoPantalla(int ancho){
	this->ancho = ancho;
}

void VistaNivel::destruirListaEntidades(){
	// Destruyo las entidades instanciadas (incluye al personaje)
	for (std::list<VistaEntidad*>::iterator entidad = this->listaEntidades.begin(); entidad != this->listaEntidades.end(); entidad++){
		delete (*entidad);
	}
	return void();
}

void VistaNivel::destruirScroll(){
	// Destruyo el scroll
	delete this->scroll;
	return void();
}

void VistaNivel::destruirEntidadesYScroll(){
	this->destruirListaEntidades();
	this->destruirScroll();
	return void();
}