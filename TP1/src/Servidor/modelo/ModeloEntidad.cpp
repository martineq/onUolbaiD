#include "ModeloEntidad.h"

using namespace std;

long ModeloEntidad::_ultimoId = 0;

ModeloEntidad::ModeloEntidad(const ModeloEntidad &modeloEntidad){

}

ModeloEntidad& ModeloEntidad::operator=(const ModeloEntidad &modeloEntidad) {
	return *this;
}

ModeloEntidad::ModeloEntidad(unsigned int alto, unsigned int ancho, unsigned int velocidad, Posicion posicion, bool esJugador) {
	this->_id = (int)InterlockedIncrement(&this->_ultimoId);
	this->_esJugador = esJugador;
	this->_alto = alto;
	this->_ancho = ancho;
	this->_velocidad = velocidad;
	this->_posicionActual = posicion;
	this->_posicionSiguiente = posicion;
	this->_modeloMovimientoActual = NULL;
}

ModeloEntidad::~ModeloEntidad() {
	if (this->_modeloMovimientoActual != NULL) {
		this->_modeloMovimientoActual->detener();
		this->_modeloMovimientoActual->join();
		delete this->_modeloMovimientoActual;
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
	if (this->_modeloMovimientoActual != NULL) {
		this->_modeloMovimientoActual->detener();
		this->_modeloMovimientoActual->join();
		delete this->_modeloMovimientoActual;
	}
	this->_modeloMovimientoActual = new ModeloMovimiento(this, posicionDestino);
	this->_modeloMovimientoActual->start(NULL);
}

bool ModeloEntidad::operator==(const ModeloEntidad &modeloEntidad) const {
	return this == &modeloEntidad;
}
