#include "ModeloNivel.h"


ModeloNivel::ModeloNivel(){

}

ModeloNivel::~ModeloNivel(void){

}

std::list <ModeloEntidad*> ModeloNivel::getListaJugadores(void){
	return this->listaJugadores;
}

std::list <ModeloScroll*> ModeloNivel::getListaScroll(void){
	return this->listaScroll;
}

std::list <ModeloEntidad*> ModeloNivel::getListaEntidades(void){
	return this->listaEntidades;
}


void ModeloNivel::agregarObservadoresScroll(std::list<Observador*>){
	// TODO: Completar.
}

void ModeloNivel::agregarObservadoresEntidad(std::list<Observador*>){
	// TODO: Completar
}

void ModeloNivel::agregarJugador(ModeloEntidad* pJugador){
	this->listaJugadores.push_back(pJugador);
	return void();
}

void ModeloNivel::agregarEntidad(ModeloEntidad* pEntidad){
	this->listaEntidades.push_back(pEntidad);
	return void();
}

void ModeloNivel::agregarScroll(ModeloScroll* pScroll){
	this->listaScroll.push_back(pScroll);
	return void();
}
