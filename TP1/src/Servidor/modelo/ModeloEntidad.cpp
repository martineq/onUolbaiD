#include "ModeloEntidad.h"

using namespace std;

ModeloEntidad::ModeloEntidad(unsigned int alto, unsigned int ancho, unsigned int velocidad, Posicion posicion) {
	this->_alto = alto;
	this->_ancho = ancho;
	this->_velocidad = velocidad;
	this->_posicionActual = posicion;
	this->_posicionSiguiente = posicion;
}

ModeloEntidad::~ModeloEntidad() {
}

void ModeloEntidad::actualizar(Observable* s) {
	//TODO: Implementar cuando este el controlador
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
	int deltaX = abs(posicionDestino.x - this->_posicionActual.x); 
	int deltaY = abs(posicionDestino.y - this->_posicionActual.y);
	int desplazamientoX = (this->_posicionActual.x < posicionDestino.x) ? 1 : -1;
	int desplazamientoY = (this->_posicionActual.y < posicionDestino.y) ? 1 : -1;
	int error = (deltaX >= deltaY) ? deltaX : deltaY;
	int desplazamientoErrorX = 2 * deltaX;
	int desplazamientoErrorY = 2 * deltaY;
		
	this->_posicionSiguiente = this->_posicionActual;
	
	while ((this->_posicionActual.x != posicionDestino.x) || (this->_posicionActual.y != posicionDestino.y)) {
		this->_posicionSiguiente.x += (deltaX >= deltaY) ? desplazamientoX : 0;
		this->_posicionSiguiente.y += (deltaX >= deltaY) ? 0 : desplazamientoY;
		error += (deltaX >= deltaY) ? desplazamientoErrorY : desplazamientoErrorX; 
		
		if (deltaX >= deltaY) {
			if (error > desplazamientoErrorX) {
				this->_posicionSiguiente.y += desplazamientoY; 
				error -= desplazamientoErrorX; 
			}
		}
		else {
			if (error > desplazamientoErrorY) {
				this->_posicionSiguiente.x += desplazamientoX;
				error -= desplazamientoErrorY;
			}
		}

		this->notificarObservadores();
		this->_posicionActual = this->_posicionSiguiente;
		
		Sleep(this->_velocidad);
	}
}

void ModeloEntidad::cambiarEstado() {
	//TODO: No se para que es este metodo
}

bool ModeloEntidad::operator==(const ModeloEntidad &modeloEntidad) const {
	return this == &modeloEntidad;
}
