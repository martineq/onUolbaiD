#include "ModeloEntidad.h"

using namespace std;

long ModeloEntidad::contador = 0; // Para el ID

ModeloEntidad::ModeloEntidad(unsigned int alto, unsigned int ancho, unsigned int velocidad, Posicion posicion) {
	this->_alto = alto;
	this->_ancho = ancho;
	this->_velocidad = velocidad;
	this->_posicionActual = posicion;
	this->_posicionSiguiente = posicion;
	this->_movimientoActual = NULL;
	this->_esJugador = false; // TODO: Agregegar parámetro para <_esJugador> al constructor de ModeloEntidad
	this->_id = InterlockedIncrement(&(this->contador));  // Genera un ID
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

int ModeloEntidad::obtenerId(void){	// Para el ID
    return ((int)this->_id);
}