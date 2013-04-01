#include "ModeloEntidad.h"

using namespace std;

long ModeloEntidad::_ultimoId = 0;

ModeloEntidad::ModeloEntidad(const ModeloEntidad &modeloEntidad){

}

ModeloEntidad& ModeloEntidad::operator=(const ModeloEntidad &modeloEntidad) {
	return *this;
}

ModeloEntidad::ModeloEntidad(unsigned int alto, unsigned int ancho, unsigned int velocidad, Posicion posicion, bool esJugador) {
	this->_alto = alto;
	this->_ancho = ancho;
	this->_velocidad = velocidad;
	this->_posicionActual = posicion;
	this->_posicionSiguiente = posicion;
	this->_movimientoActual = NULL;
	this->_esJugador = esJugador;
	this->_id = (int)InterlockedIncrement(&this->_ultimoId);  // Genera un ID
}

ModeloEntidad::~ModeloEntidad() {
	if (this->_movimientoActual != NULL) {
		this->_movimientoActual->detener();
		this->_movimientoActual->join();
		delete this->_movimientoActual;
	}
}

void ModeloEntidad::cambiarEstado() {
	this->notificarObservadores();
}

int ModeloEntidad::obtenerId() const {
    return this->_id;
}

bool ModeloEntidad::esJugador() const {
	return this->_esJugador;
}

unsigned int ModeloEntidad::alto() const {
	return this->_alto;
}

unsigned int ModeloEntidad::ancho() const {
	return this->_ancho;
}
		
unsigned int ModeloEntidad::velocidad() const {
	return this->_velocidad;
}

Posicion ModeloEntidad::posicionActual() const {
	return this->_posicionActual;
}

Posicion ModeloEntidad::posicionSiguiente() const {
	return this->_posicionSiguiente;
}

void ModeloEntidad::mover(Posicion posicionDestino) {
	if (this->_movimientoActual != NULL) {
		this->_movimientoActual->detener();
		this->_movimientoActual->join();
		delete this->_movimientoActual;
	}
	this->_movimientoActual = new Movimiento(this, posicionDestino);
	this->_movimientoActual->start(NULL);
}

bool ModeloEntidad::operator==(const ModeloEntidad &modeloEntidad) const {
	return this == &modeloEntidad;
}
