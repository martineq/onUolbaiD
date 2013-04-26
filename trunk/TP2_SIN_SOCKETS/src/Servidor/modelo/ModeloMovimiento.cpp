#include "ModeloEntidad.h"

using namespace std;

Direccion ModeloEntidad::ModeloMovimiento::obtenerDireccion(Posicion posicionOrigen, Posicion posicionDestino) {
	if (posicionOrigen.x > posicionDestino.x) {
		if (posicionOrigen.y > posicionDestino.y)
			return NORTE; //NOROESTE
		else if (posicionOrigen.y < posicionDestino.y)
			return OESTE; //SUDOESTE
		else
			return NOROESTE; //OESTE
	}
	else if (posicionOrigen.x < posicionDestino.x)
		if (posicionOrigen.y > posicionDestino.y)
			return ESTE; //NORESTE
		else if (posicionOrigen.y < posicionDestino.y)
			return SUR; //SUDESTE
		else
			return SUDESTE; //ESTE
	else {
		if (posicionOrigen.y > posicionDestino.y)
			return NORESTE; //NORTE
		else if (posicionOrigen.y < posicionDestino.y)
			return SUDOESTE; //SUR
		else
			return SUDOESTE; //SUR
	}
}

ModeloEntidad::ModeloMovimiento::ModeloMovimiento(const ModeloMovimiento &modeloMovimiento) {
}

ModeloEntidad::ModeloMovimiento& ModeloEntidad::ModeloMovimiento::operator=(const ModeloMovimiento &modeloMovimiento) {
	return *this;
}

ModeloEntidad::ModeloMovimiento::ModeloMovimiento(ModeloEntidad* modeloEntidad) {
	this->_modeloEntidad = modeloEntidad;
	this->_posicionDestino = this->_modeloEntidad->posicionActual();
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
	this->_modeloEntidad->posicionSiguiente(this->_modeloEntidad->posicionActual());
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

	Posicion posicionSiguiente = this->_modeloEntidad->posicionSiguiente();

	posicionSiguiente.x += (this->_deltaX >= this->_deltaY) ? this->_desplazamientoX : 0;
	posicionSiguiente.y += (this->_deltaX >= this->_deltaY) ? 0 : this->_desplazamientoY;
	this->_error += (this->_deltaX >= this->_deltaY) ? this->_desplazamientoErrorY : this->_desplazamientoErrorX; 
	
	if (this->_deltaX >= this->_deltaY) {
		if (this->_error > this->_desplazamientoErrorX) {
			posicionSiguiente.y += this->_desplazamientoY; 
			this->_error -= this->_desplazamientoErrorX; 
		}
	}
	else {
		if (this->_error > this->_desplazamientoErrorY) {
			posicionSiguiente.x += this->_desplazamientoX;
			this->_error -= this->_desplazamientoErrorY;
		}
	}

	list<ModeloEntidad*>::iterator iterador = this->_listaEntidades->begin();

	while (iterador != this->_listaEntidades->end()) {
		if (((*iterador) != this->_modeloEntidad) && 
			(posicionSiguiente.x >= (*iterador)->posicionActual().x) &&
			(posicionSiguiente.x <= (*iterador)->posicionActual().x + (*iterador)->ancho() - 1) &&
			(posicionSiguiente.y >= (*iterador)->posicionActual().y) &&
			(posicionSiguiente.y <= (*iterador)->posicionActual().y + (*iterador)->alto() - 1)) {
			this->_posicionDestino = this->_modeloEntidad->posicionActual();
			return;
		}
		iterador++;
	}

	this->_modeloEntidad->posicionSiguiente(posicionSiguiente);
	this->_modeloEntidad->direccion(this->obtenerDireccion(this->_modeloEntidad->posicionActual(), this->_modeloEntidad->posicionSiguiente()));
	this->notificarObservadores();
	this->_modeloEntidad->posicionActual(this->_modeloEntidad->posicionSiguiente());

	this->_instanteUltimoCambioEstado = GetTickCount();
}

void ModeloEntidad::ModeloMovimiento::asignarListaEntidades(std::list<ModeloEntidad*>* listaEntidades) {
	this->_listaEntidades = listaEntidades;
}
