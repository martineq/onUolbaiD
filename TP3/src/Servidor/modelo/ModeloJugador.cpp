#include "ModeloJugador.h"

using namespace std;

ModeloJugador::ModeloJugador(const ModeloJugador &modeloJugador) {
}

ModeloJugador& ModeloJugador::operator=(const ModeloJugador &modeloJugador) {
	return *this;
}

ModeloJugador::ModeloJugador(int alto, int ancho, int velocidad, Posicion posicion, bool esJugador, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, string nombreEntidad, string nombreJugador) {
	this->_modeloEntidad = new ModeloEntidad(alto, ancho, velocidad, posicion, esJugador, altoNivel, anchoNivel, fps, proxyEntidad, id, nombreEntidad, nombreJugador);
}

ModeloJugador::~ModeloJugador() {
	delete this->_modeloEntidad;
}

ModeloEntidad* ModeloJugador::modeloEntidad() {
	return this->_modeloEntidad;
}

void ModeloJugador::asignarJugadores(Mutex* mutexJugadores, std::list<ModeloJugador*>* jugadores) {
	this->_mutexJugadores = mutexJugadores;
	this->_jugadores = jugadores;
}

void ModeloJugador::atacar() {
	this->_modeloEntidad->detener();
	this->_modeloEntidad->accion(ATACANDO);
}

void ModeloJugador::defender() {
	this->_modeloEntidad->detener();
	this->_modeloEntidad->accion(DEFENDIENDO);
}

void ModeloJugador::mover(Posicion posicion) {
	this->_modeloEntidad->mover(posicion);
}
