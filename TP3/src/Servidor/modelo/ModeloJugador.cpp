#include "ModeloJugador.h"

using namespace std;

ModeloJugador::ModeloJugador(const ModeloJugador &modeloJugador) {
}

ModeloJugador& ModeloJugador::operator=(const ModeloJugador &modeloJugador) {
	return *this;
}

ModeloJugador::ModeloJugador(int alto, int ancho, int velocidad, Posicion posicion, bool esJugador, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, string nombreEntidad, string nombreJugador) {
	this->_modeloEntidad = new ModeloEntidad(alto, ancho, velocidad, posicion, esJugador, altoNivel, anchoNivel, fps, proxyEntidad, id, nombreEntidad, nombreJugador);
	this->_enemigo = NULL;
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

void ModeloJugador::atacar(ModeloJugador* enemigo) {
	this->_enemigo = enemigo;
	this->_modeloEntidad->mover(this->_enemigo->modeloEntidad()->posicionActual());
}

void ModeloJugador::cambiarEstado() {
	// Si no estoy persiguiendo a un enemigo ejecuto el cambio de estado normalmente y salgo
	if (this->_enemigo == NULL) {
		this->_modeloEntidad->cambiarEstado();
		return;
	}
	
	// Si estoy persiguiendo un enemigo
	Posicion posicionEnemigo = this->_enemigo->modeloEntidad()->posicionActual();
	Posicion posicionJugador = this->_modeloEntidad->posicionActual();
	
	// Si el enemigo salio de la zona visible dejo de seguirlo y me detengo
	if ((posicionEnemigo.x < posicionJugador.x - (ZONA_VISIBLE / 2)) || (posicionEnemigo.x > posicionJugador.x + (ZONA_VISIBLE / 2)) || (posicionEnemigo.y < posicionJugador.y - (ZONA_VISIBLE / 2)) || (posicionEnemigo.y > posicionJugador.y + (ZONA_VISIBLE / 2))) {
		this->_enemigo = NULL;
		this->_modeloEntidad->detener();
		this->_modeloEntidad->cambiarEstado();
		return;
	}

	// Si el enemigo esta en una posicion adyacente lo ataco
	if ((fabs((float)posicionJugador.x - posicionEnemigo.x) <= 1) && (fabs((float)posicionJugador.y - posicionEnemigo.y) <= 1)) {
		this->_enemigo = NULL;
		this->_modeloEntidad->direccion(Posicion::obtenerDireccion(posicionJugador, posicionEnemigo));
		this->_modeloEntidad->accion(ATACANDO);
		this->_modeloEntidad->cambiarEstado();
		return;
	}

	// Si el enemigo sigue en la zona visible lo sigo persiguiendo
	this->_modeloEntidad->mover(posicionEnemigo);
	this->_modeloEntidad->cambiarEstado();
}

void ModeloJugador::mover(Posicion posicion) {
	this->_enemigo = NULL;
	this->_modeloEntidad->mover(posicion);
}
