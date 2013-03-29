#include "VistaNivel.h"


VistaNivel::VistaNivel(){

}

VistaNivel::~VistaNivel(){

}

Observador* VistaNivel::obtenerObservadorScroll(void){
	return (Observador*)this->vistaScroll;
}

std::list<Observador*> VistaNivel::obtenerObservadoresEntidad(void){

	// TODO: Ver como paso la lista ¿se borra?
	std::list<Observador*> listaObservadoresEntidad;

	for (std::list<VistaEntidad*>::iterator it=this->listaVistaEntidad.begin() ; it != this->listaVistaEntidad.end(); it++ ){
		listaObservadoresEntidad.push_back( ((Observador*)*it) );
	}

	return listaObservadoresEntidad;

}

