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
	for (std::list<Observador*>::iterator observador = listaObservadoresJugador.begin(); observador != listaObservadoresJugador.end(); observador++) {
		// Busco al que quiero observar
		for (std::list<ModeloEntidad*>::iterator jugador = this->listaJugadores.begin(); jugador != this->listaJugadores.end(); jugador++) {
			// Cuando lo encuentro, lo agrego
			if ((*jugador)->id() == dynamic_cast<Identificable*>(*observador)->id()) 
				(*jugador)->agregarObservador(*observador);
		}
	}
}

void ModeloNivel::agregarObservadoresEntidad(std::list<Observador*> listaObservadoresEntidad) {
	// Itero sobre los observadores
	for (std::list<Observador*>::iterator observador = listaObservadoresEntidad.begin(); observador != listaObservadoresEntidad.end(); observador++) {
		// Busco al que quiero observar
		for (std::list<ModeloEntidad*>::iterator entidad = this->listaEntidades.begin(); entidad != this->listaEntidades.end(); entidad++) {
			// Cuando lo encuentro, lo agrego
			if ((*entidad)->id() == dynamic_cast<Identificable*>(*observador)->id()) 
				(*entidad)->agregarObservador(*observador);
		}
	}
}

void ModeloNivel::agregarObservadoresScroll(std::list<Observador*> listaObservadoresScroll){
	// Itero sobre los observadores
	for (std::list<Observador*>::iterator observador = listaObservadoresScroll.begin(); observador != listaObservadoresScroll.end(); observador++) {
		// Busco al que quiero observar
		for (std::list<ModeloScroll*>::iterator scroll = this->listaScroll.begin(); scroll != this->listaScroll.end(); scroll++) {
			// Cuando lo encuentro, lo agrego
			if ((*scroll)->id() == dynamic_cast<Identificable*>(*observador)->id()) 
				(*scroll)->agregarObservador(*observador);
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
	for (std::list<ModeloScroll*>::iterator scroll = this->listaScroll.begin(); scroll != this->listaScroll.end(); scroll++) {
		if ((*scroll)->id() == id) {
			(*scroll)->actualizar(mouseX, mouseY);
			return;
		}
	}
}

void ModeloNivel::moverJugador(int tileX, int tileY, int id) {
	if (this->listaJugadores.size() == 0)
		return;
	ModeloEntidad* personaje = *this->listaJugadores.begin();
	Posicion posicion;
	posicion.x = tileX;
	posicion.y = tileY;
	personaje->mover(posicion);
}
