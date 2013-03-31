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

void ModeloNivel::agregarJugador(double x, double y, double alto, double ancho, double velocidad){
	ModeloEntidad* pJugador = NULL; // TODO: hacer el new() y llenar con los datos cuando reciban double
	this->listaJugadores.push_back(pJugador);
	return void();
}

void ModeloNivel::agregarEntidad(double x, double y, double alto, double ancho, double velocidad){
	ModeloEntidad* pEntidad = NULL; // TODO: hacer el new() y llenar con los datos cuando reciban double
	this->listaEntidades.push_back(pEntidad);
	return void();
}

void ModeloNivel::agregarScroll(double x, double y, double alto, double ancho, double velocidad, double margen){
	ModeloScroll* pScroll = NULL; // TODO: hacer el new() y llenar con los datos cuando reciban double
	this->listaScroll.push_back(pScroll);
	return void();
}
