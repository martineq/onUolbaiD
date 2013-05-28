#include "ModeloJugador.h"

using namespace std;

#define DANIO_MAXIMO 20

ModeloJugador::ModeloJugador(const ModeloJugador &modeloJugador) {
}

ModeloJugador& ModeloJugador::operator=(const ModeloJugador &modeloJugador) {
	return *this;
}

ModeloJugador::ModeloJugador(int alto, int ancho, int velocidad, Posicion posicion, bool esJugador, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, string nombreEntidad, string nombreJugador) {
	this->_posicionInicial = posicion;
	this->_modeloEntidad = new ModeloEntidad(alto, ancho, velocidad, posicion, esJugador, altoNivel, anchoNivel, fps, proxyEntidad, id, nombreEntidad, nombreJugador);
	this->_enemigo = NULL;
}

ModeloJugador::~ModeloJugador() {
	delete this->_modeloEntidad;
}

bool ModeloJugador::estaCongelado() {
	return this->_modeloEntidad->estaCongelado();
}

void ModeloJugador::estaCongelado(bool estaCongelado) {
	this->_modeloEntidad->estaCongelado(estaCongelado);
	this->_enemigo = NULL;
}

ModeloEntidad* ModeloJugador::modeloEntidad() {
	return this->_modeloEntidad;
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
		this->_modeloEntidad->detener();
		this->_enemigo = NULL;
		return;
	}

	// Si el enemigo esta en una posicion adyacente y no me estoy moviendo lo ataco
	if (!this->_modeloEntidad->enMovimiento() && (fabs((float)posicionJugador.x - posicionEnemigo.x) <= 1) && (fabs((float)posicionJugador.y - posicionEnemigo.y) <= 1)) {
		this->_modeloEntidad->direccion(Posicion::obtenerDireccion(posicionJugador, posicionEnemigo));
		this->_modeloEntidad->accion(ATACANDO);
		this->_modeloEntidad->notificar();
		this->_modeloEntidad->accion(CAMINANDO);
		this->_enemigo->lastimar(rand() % DANIO_MAXIMO);
		this->_enemigo = NULL;
		return;
	}

	// Si el enemigo sigue en la zona visible lo sigo persiguiendo
	this->_modeloEntidad->mover(posicionEnemigo);
	this->_modeloEntidad->cambiarEstado();
}

void ModeloJugador::lastimar(int danio) {
	this->_modeloEntidad->posicionActual(this->_posicionInicial);
	this->_modeloEntidad->posicionSiguiente(this->_posicionInicial);
	this->_modeloEntidad->notificar();
}

void ModeloJugador::mover(Posicion posicion) {
	this->_enemigo = NULL;
	this->_modeloEntidad->mover(posicion);
}
