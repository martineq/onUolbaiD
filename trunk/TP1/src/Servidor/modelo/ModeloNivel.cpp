#include "ModeloNivel.h"

using namespace std;

ModeloNivel::ModeloNivel(){
	this->listaJugadores.clear();
	this->listaEntidades.clear();
	this->listaScroll.clear();
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


void ModeloNivel::agregarJugador(ModeloEntidad *jugador) {
	this->listaJugadores.push_back(jugador);
}


void ModeloNivel::agregarEntidad(ModeloEntidad *entidad) {
	this->listaEntidades.push_back(entidad);
}

void ModeloNivel::agregarScroll(ModeloScroll *scroll) {
	this->listaScroll.push_back(scroll);
}

void ModeloNivel::removerJugador(ModeloEntidad *jugador) {
	this->listaJugadores.remove(jugador);
}

void ModeloNivel::removerEntidad(ModeloEntidad *entidad) {
	this->listaEntidades.remove(entidad);
}

void ModeloNivel::removerScroll(ModeloScroll *scroll) {
	this->listaScroll.remove(scroll);
}

/*
void ModeloNivel::agregarJugador(double x, double y, double alto, double ancho, double velocidad){
	ModeloEntidad* pJugador = NULL; // TODO: hacer el new() y llenar con los datos cuando reciban double
=======
void ModeloNivel::agregarJugador(ModeloEntidad* pJugador){
>>>>>>> .r64
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
*/
