#include "ModeloEntidad.h"

void* ModeloEntidad::Movimiento::run(void* parametro) {
	int deltaX = abs(this->_posicionDestino.x - this->_modeloEntidad->_posicionActual.x); 
	int deltaY = abs(this->_posicionDestino.y - this->_modeloEntidad->_posicionActual.y);
	int desplazamientoX = (this->_modeloEntidad->_posicionActual.x < this->_posicionDestino.x) ? 1 : -1;
	int desplazamientoY = (this->_modeloEntidad->_posicionActual.y < this->_posicionDestino.y) ? 1 : -1;
	int error = (deltaX >= deltaY) ? deltaX : deltaY;
	int desplazamientoErrorX = 2 * deltaX;
	int desplazamientoErrorY = 2 * deltaY;
	
	this->_modeloEntidad->_posicionSiguiente = this->_modeloEntidad->_posicionActual;

	this->_ejecutando = true;
	while (this->_ejecutando && (this->_modeloEntidad->_posicionActual != this->_posicionDestino)) {
		this->_modeloEntidad->_posicionSiguiente.x += (deltaX >= deltaY) ? desplazamientoX : 0;
		this->_modeloEntidad->_posicionSiguiente.y += (deltaX >= deltaY) ? 0 : desplazamientoY;
		error += (deltaX >= deltaY) ? desplazamientoErrorY : desplazamientoErrorX; 
		
		if (deltaX >= deltaY) {
			if (error > desplazamientoErrorX) {
				this->_modeloEntidad->_posicionSiguiente.y += desplazamientoY; 
				error -= desplazamientoErrorX; 
			}
		}
		else {
			if (error > desplazamientoErrorY) {
				this->_modeloEntidad->_posicionSiguiente.x += desplazamientoX;
				error -= desplazamientoErrorY;
			}
		}

		this->_modeloEntidad->notificarObservadores();
		this->_modeloEntidad->_posicionActual = this->_modeloEntidad->_posicionSiguiente;
		
		Sleep(this->_modeloEntidad->_velocidad);
	}
	return NULL;
}

ModeloEntidad::Movimiento::Movimiento(const Movimiento &movimiento) {
}

ModeloEntidad::Movimiento& ModeloEntidad::Movimiento::operator=(const Movimiento &movimiento) {
	return *this;
}

ModeloEntidad::Movimiento::Movimiento(ModeloEntidad* modeloEntidad, Posicion posicionDestino) {
	this->_modeloEntidad = modeloEntidad;
	this->_posicionDestino = posicionDestino;
	this->_ejecutando = false;
}

ModeloEntidad::Movimiento::~Movimiento() {
}

void ModeloEntidad::Movimiento::detener() {
	this->_ejecutando = false;
}
