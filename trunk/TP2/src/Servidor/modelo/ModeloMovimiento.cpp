#include "ModeloEntidad.h"

using namespace std;

ModeloEntidad::ModeloMovimiento::ModeloMovimiento(const ModeloMovimiento &modeloMovimiento) {
}

ModeloEntidad::ModeloMovimiento& ModeloEntidad::ModeloMovimiento::operator=(const ModeloMovimiento &modeloMovimiento) {
	return *this;
}

ModeloEntidad::ModeloMovimiento::ModeloMovimiento(ModeloEntidad* modeloEntidad) {
	this->_modeloEntidad = modeloEntidad;
	this->_posicionDestino = this->_modeloEntidad->_posicionActual;
    this->_deltaX = 0;
    this->_deltaY = 0;
    this->_desplazamientoX = 0;
    this->_desplazamientoY = 0;
    this->_error = 0;
    this->_desplazamientoErrorX = 0;
    this->_desplazamientoErrorY = 0;
    this->_instanteUltimoCambioEstado = 0;
}

ModeloEntidad::ModeloMovimiento::~ModeloMovimiento() {
}

void ModeloEntidad::ModeloMovimiento::actualizar(Posicion posicionDestino) {
	this->_posicionDestino = posicionDestino;
	this->_deltaX = abs(this->_posicionDestino.x - this->_modeloEntidad->posicionActual().x);
	this->_deltaY = abs(this->_posicionDestino.y - this->_modeloEntidad->posicionActual().y);
	this->_desplazamientoX = (this->_modeloEntidad->posicionActual().x < this->_posicionDestino.x) ? 1 : -1;
	this->_desplazamientoY = (this->_modeloEntidad->posicionActual().y < this->_posicionDestino.y) ? 1 : -1;
	this->_error = (this->_deltaX >= this->_deltaY) ? this->_deltaX : this->_deltaY;
	this->_desplazamientoErrorX = 2 * this->_deltaX;
	this->_desplazamientoErrorY = 2 * this->_deltaY;
	this->_modeloEntidad->setPosicionSiguiente( this->_modeloEntidad->posicionActual() );
}

void ModeloEntidad::ModeloMovimiento::cambiarEstado() {
	if (this->_modeloEntidad->posicionActual() == this->_posicionDestino)
		return;
	
	if (this->_instanteUltimoCambioEstado == 0) {
		this->_instanteUltimoCambioEstado = GetTickCount();
		return;
	}

	if (this->_modeloEntidad->velocidad() > (GetTickCount() - this->_instanteUltimoCambioEstado))
		return;

	// Calculo nueva posición
	Posicion nuevaPos;
	nuevaPos.x = this->_modeloEntidad->posicionSiguiente().x + (this->_deltaX >= this->_deltaY) ? this->_desplazamientoX : 0;
	nuevaPos.y = this->_modeloEntidad->posicionSiguiente().y + (this->_deltaX >= this->_deltaY) ? 0 : this->_desplazamientoY;

	// La asigno
	this->_modeloEntidad->setPosicionSiguiente(nuevaPos);

	this->_error += (this->_deltaX >= this->_deltaY) ? this->_desplazamientoErrorY : this->_desplazamientoErrorX; 
	
	if (this->_deltaX >= this->_deltaY) {
		if (this->_error > this->_desplazamientoErrorX) {
			Posicion pos = this->_modeloEntidad->posicionSiguiente();
			pos.y = pos.y + this->_desplazamientoY;
			this->_modeloEntidad->setPosicionSiguiente(pos); 
			this->_error -= this->_desplazamientoErrorX; 
		}
	}
	else {
		if (this->_error > this->_desplazamientoErrorY) {
			Posicion pos = this->_modeloEntidad->posicionSiguiente();
			pos.x = pos.x + this->_desplazamientoX;
			this->_modeloEntidad->setPosicionSiguiente(pos); 
			this->_error -= this->_desplazamientoErrorY;
		}
	}

	this->notificarObservadores();
	this->_modeloEntidad->setPosicionActual( this->_modeloEntidad->posicionSiguiente() );

	this->_instanteUltimoCambioEstado = GetTickCount();
}
