#include "ModeloEntidad.h"

using namespace std;

ModeloEntidad::ModeloMovimiento::ModeloMovimiento(const ModeloMovimiento &modeloMovimiento) {
}

ModeloEntidad::ModeloMovimiento& ModeloEntidad::ModeloMovimiento::operator=(const ModeloMovimiento &modeloMovimiento) {
	return *this;
}

ModeloEntidad::ModeloMovimiento::ModeloMovimiento(ModeloEntidad* modeloEntidad) {
	this->_modeloEntidad = modeloEntidad;
	this->_instanteUltimoCambioEstado = 0;
}

ModeloEntidad::ModeloMovimiento::~ModeloMovimiento() {
}

void ModeloEntidad::ModeloMovimiento::actualizar(Posicion posicionDestino) {
	this->_posicionDestino = posicionDestino;
	this->_deltaX = abs(this->_posicionDestino.x - this->_modeloEntidad->_posicionActual.x);
	this->_deltaY = abs(this->_posicionDestino.y - this->_modeloEntidad->_posicionActual.y);
	this->_desplazamientoX = (this->_modeloEntidad->_posicionActual.x < this->_posicionDestino.x) ? 1 : -1;
	this->_desplazamientoY = (this->_modeloEntidad->_posicionActual.y < this->_posicionDestino.y) ? 1 : -1;
	this->_error = (this->_deltaX >= this->_deltaY) ? this->_deltaX : this->_deltaY;
	this->_desplazamientoErrorX = 2 * this->_deltaX;
	this->_desplazamientoErrorY = 2 * this->_deltaY;
	this->_modeloEntidad->_posicionSiguiente = this->_modeloEntidad->_posicionActual;
}

void ModeloEntidad::ModeloMovimiento::cambiarEstado() {
	if (this->_modeloEntidad->_posicionActual == this->_posicionDestino)
		return;
	
	if (this->_instanteUltimoCambioEstado == 0) {
		this->_instanteUltimoCambioEstado = GetTickCount();
		return;
	}

	if (this->_modeloEntidad->velocidad() > (GetTickCount() - this->_instanteUltimoCambioEstado))
		return;

	this->_modeloEntidad->_posicionSiguiente.x += (this->_deltaX >= this->_deltaY) ? this->_desplazamientoX : 0;
	this->_modeloEntidad->_posicionSiguiente.y += (this->_deltaX >= this->_deltaY) ? 0 : this->_desplazamientoY;
	this->_error += (this->_deltaX >= this->_deltaY) ? this->_desplazamientoErrorY : this->_desplazamientoErrorX; 
	
	if (this->_deltaX >= this->_deltaY) {
		if (this->_error > this->_desplazamientoErrorX) {
			this->_modeloEntidad->_posicionSiguiente.y += this->_desplazamientoY; 
			this->_error -= this->_desplazamientoErrorX; 
		}
	}
	else {
		if (this->_error > this->_desplazamientoErrorY) {
			this->_modeloEntidad->_posicionSiguiente.x += this->_desplazamientoX;
			this->_error -= this->_desplazamientoErrorY;
		}
	}

	this->notificarObservadores();
	this->_modeloEntidad->_posicionActual = this->_modeloEntidad->_posicionSiguiente;

	this->_instanteUltimoCambioEstado = GetTickCount();
}
