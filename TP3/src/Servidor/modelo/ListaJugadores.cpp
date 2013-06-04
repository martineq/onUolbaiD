#include "ModeloJugador.h"

using namespace std;

ListaJugadores::ListaJugadores() {
}

ListaJugadores::~ListaJugadores() {
}

void ListaJugadores::agregarJugador(ModeloJugador* jugador) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_jugadores.push_back(jugador);	
	this->_mutex.unlock(__FILE__, __LINE__);
	this->_listaEntidades->agregarEntidadMovil(jugador->modeloEntidad());
}

void ListaJugadores::asignarListaEntidades(ListaEntidades* listaEntidades) {
	this->_listaEntidades = listaEntidades;
}

void ListaJugadores::destruirJugadores() {
	for (list<ModeloJugador*>::iterator jugador = this->_jugadores.begin(); jugador != this->_jugadores.end(); jugador++)
		delete (*jugador);
}

ModeloJugador* ListaJugadores::obtenerJugador(int id) {
	list<ModeloJugador*> listaJugadores = this->obtenerJugadores();
	for (list<ModeloJugador*>::iterator jugador = listaJugadores.begin(); jugador != listaJugadores.end(); jugador++){
		if ((*jugador)->modeloEntidad()->id() == id)
			return (*jugador);
	}
	return NULL;
}

ModeloJugador* ListaJugadores::obtenerJugador(Posicion posicion) {
	list<ModeloJugador*> listaJugadores = this->obtenerJugadores();
	for (std::list<ModeloJugador*>::iterator jugador = listaJugadores.begin(); jugador != listaJugadores.end(); jugador++){
		if ((*jugador)->modeloEntidad()->posicion() == posicion)
			return (*jugador);
	}
	return NULL;
}

list<ModeloJugador*> ListaJugadores::obtenerJugadores() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	list<ModeloJugador*> listaJugadores = this->_jugadores;
	this->_mutex.unlock(__FILE__, __LINE__);
	return listaJugadores;
}

void ListaJugadores::removerJugador(ModeloJugador* jugador) {
	this->_listaEntidades->removerEntidadMovil(jugador->modeloEntidad());
}
