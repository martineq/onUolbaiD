#include "ModeloNivel.h"

using namespace std;

ModeloNivel::ModeloNivel() {
	this->listaJugadores.clear();
	this->listaEntidades.clear();
	this->listaScroll.clear();
}

ModeloNivel::~ModeloNivel() {
}

std::list<ModeloEntidad*> ModeloNivel::getListaJugadores() {
	return this->listaJugadores;
}

std::list<ModeloScroll*> ModeloNivel::getListaScroll() {
	return this->listaScroll;
}

std::list<ModeloEntidad*> ModeloNivel::getListaEntidades() {
	return this->listaEntidades;
}

int ModeloNivel::getAnchoTiles() {
	return this->altoTiles;
}

int ModeloNivel::getAltoTiles() {
	return this->anchoTiles;
}

void ModeloNivel::agregarObservadoresJugador(std::list<Observador*> listaObservadoresJugador) {
	// Itero sobre los observadores
	for (std::list<Observador*>::iterator it = listaObservadoresJugador.begin(); it != listaObservadoresJugador.end(); it++) {
		Observador* pObservador = *it;
		
		// Busco al que quiero observar
		for (std::list<ModeloEntidad*>::iterator it2 = this->listaJugadores.begin(); it2 != this->listaJugadores.end(); it2++) {
			ModeloEntidad* pObservado = *it2;

			// Cuando lo encuentro, lo agrego
			if (pObservado->obtenerId() == ((VistaScroll*)pObservador)->getId()) 
				pObservado->agregarObservador(pObservador);
		}
	}
}

void ModeloNivel::agregarObservadoresEntidad(std::list<Observador*> listaObservadoresEntidad) {
	// Itero sobre los observadores
	for (std::list<Observador*>::iterator it = listaObservadoresEntidad.begin(); it != listaObservadoresEntidad.end(); it++) {
		Observador* pObservador = *it;
		
		// Busco al que quiero observar
		for (std::list<ModeloEntidad*>::iterator it2 = this->listaEntidades.begin(); it2 != this->listaEntidades.end(); it2++) {
			ModeloEntidad* pObservado = *it2;

			// Cuando lo encuentro, lo agrego
			if (pObservado->obtenerId() == ((VistaScroll*)pObservador)->getId()) 
				pObservado->agregarObservador(pObservador);
		}
	}
}

void ModeloNivel::agregarObservadoresScroll(std::list<Observador*> listaObservadoresScroll){
	// Itero sobre los observadores
	for (std::list<Observador*>::iterator it = listaObservadoresScroll.begin(); it != listaObservadoresScroll.end(); it++) {
		Observador* pObservador = *it;
		
		// Busco al que quiero observar
		for (std::list<ModeloScroll*>::iterator it2 = this->listaScroll.begin(); it2 != this->listaScroll.end(); it2++) {
			ModeloScroll* pObservado = *it2;

			// Cuando lo encuentro, lo agrego
			if ( pObservado->obtenerId() == ((VistaScroll*)pObservador)->getId()) 
				pObservado->agregarObservador(pObservador);
		}
	}
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

void ModeloNivel::moverScroll(int mouseX, int mouseY, int id) {
	for (std::list<ModeloScroll*>::iterator it = this->listaScroll.begin(); it != this->listaScroll.end(); it++) {
		if ((*it)->obtenerId() == id) {
			(*it)->actualizar(mouseX, mouseY);
		}
	}
}

void ModeloNivel::moverJugador(int mouseX, int mouseY, int id) {
	if (this->listaJugadores.size() == 0)
		return;
	ModeloEntidad* personaje = *this->listaJugadores.begin();
	Posicion posicion;
	Posicion::convertirPixelATile(this->altoTiles, mouseX, mouseY, posicion.x, posicion.y);
	personaje->mover(posicion);
}
