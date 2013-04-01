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

int ModeloNivel::getAnchoTiles(void){
	return this->altoTiles;
}

int ModeloNivel::getAltoTiles(void){
	return this->anchoTiles;
}


void ModeloNivel::agregarObservadoresScroll(std::list<Observador*> listaObservadoresScroll){
	
	// Itero sobre los observadores
	for(std::list<Observador*>::iterator it=listaObservadoresScroll.begin() ; it != listaObservadoresScroll.end(); it++ ){
		Observador* pObservador = (*it);
		
		// Busco al que quiero observar
		for(std::list<ModeloScroll*>::iterator it2=this->listaScroll.begin() ; it2 != this->listaScroll.end(); it2++ ){
			ModeloScroll* pObservado = (*it2);

			if( pObservado->obtenerId() == ((VistaScroll*)pObservador)->getId() ){ // Cuando lo encuentro, lo agrego
				pObservado->agregarObservador(pObservador);
			}

		}
	}
	return void();
}

void ModeloNivel::agregarObservadoresEntidad(std::list<Observador*> listaObservadoresEntidad){

	// Itero sobre los observadores
	for(std::list<Observador*>::iterator it=listaObservadoresEntidad.begin() ; it != listaObservadoresEntidad.end(); it++ ){
		Observador* pObservador = (*it);
		
		if( ((VistaEntidad*)pObservador)->getEsJugador() == true ){

			// Busco al que quiero observar
			for(std::list<ModeloEntidad*>::iterator it2=this->listaJugadores.begin() ; it2 != this->listaJugadores.end(); it2++ ){
				ModeloEntidad* pObservado = (*it2);

				if( pObservado->obtenerId() == ((VistaEntidad*)pObservador)->getId() ){ // Cuando lo encuentro, lo agrego
					pObservado->agregarObservador(pObservador);
				}

			}

		}else{

			// Busco al que quiero observar
			for(std::list<ModeloEntidad*>::iterator it2=this->listaEntidades.begin() ; it2 != this->listaEntidades.end(); it2++ ){
				ModeloEntidad* pObservado = (*it2);

				if( pObservado->obtenerId() == ((VistaEntidad*)pObservador)->getId() ){ // Cuando lo encuentro, lo agrego
					pObservado->agregarObservador(pObservador);
				}

		}

		}

		
	}
	return void();
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

void ModeloNivel::setAltoTiles(int alto){
	this->altoTiles = alto;
}

void ModeloNivel::setAnchoTiles(int ancho){
	this->anchoTiles = ancho;
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


void ModeloNivel::moverScroll (int mouseX, int mouseY, int id) {
	for (std::list<ModeloScroll *>::iterator it=this->listaScroll.begin() ; it != this->listaScroll.end(); it++ ){
			if ((*it)->obtenerId() == id) {
				(*it)->actualizar(mouseX, mouseY);
			}
		}
}