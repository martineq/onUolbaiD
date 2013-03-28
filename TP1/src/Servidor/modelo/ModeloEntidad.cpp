#include "ModeloEntidad.h"

using namespace std;

int ModeloEntidad::mover(void* objeto) {
	Movimiento* movimiento = (Movimiento*)objeto;
	ModeloEntidad* modeloEntidad = movimiento->modeloEntidad;
	Posicion posicionDestino = movimiento->posicionDestino;
	int deltaX = abs(posicionDestino.x - modeloEntidad->_posicionActual.x); 
	int deltaY = abs(posicionDestino.y - modeloEntidad->_posicionActual.y);
	int desplazamientoX = (modeloEntidad->_posicionActual.x < posicionDestino.x) ? 1 : -1;
	int desplazamientoY = (modeloEntidad->_posicionActual.y < posicionDestino.y) ? 1 : -1;
	int error = (deltaX >= deltaY) ? deltaX : deltaY;
	int desplazamientoErrorX = 2 * deltaX;
	int desplazamientoErrorY = 2 * deltaY;
		
	modeloEntidad->_posicionSiguiente = modeloEntidad->_posicionActual;

	movimiento->ejecutando = true;
	while (movimiento->ejecutando && (modeloEntidad->_posicionActual != posicionDestino)) {
		Uint32 tiempoInicio = SDL_GetTicks();

		modeloEntidad->_posicionSiguiente.x += (deltaX >= deltaY) ? desplazamientoX : 0;
		modeloEntidad->_posicionSiguiente.y += (deltaX >= deltaY) ? 0 : desplazamientoY;
		error += (deltaX >= deltaY) ? desplazamientoErrorY : desplazamientoErrorX; 
		
		if (deltaX >= deltaY) {
			if (error > desplazamientoErrorX) {
				modeloEntidad->_posicionSiguiente.y += desplazamientoY; 
				error -= desplazamientoErrorX; 
			}
		}
		else {
			if (error > desplazamientoErrorY) {
				modeloEntidad->_posicionSiguiente.x += desplazamientoX;
				error -= desplazamientoErrorY;
			}
		}

		modeloEntidad->notificarObservadores();
		modeloEntidad->_posicionActual = modeloEntidad->_posicionSiguiente;
		
		Sleep(modeloEntidad->_velocidad);
	}
	return 0;
}

ModeloEntidad::ModeloEntidad(unsigned int alto, unsigned int ancho, unsigned int velocidad, Posicion posicion) {
	this->_alto = alto;
	this->_ancho = ancho;
	this->_velocidad = velocidad;
	this->_posicionActual = posicion;
	this->_posicionSiguiente = posicion;

	this->_movimientoActual.modeloEntidad = this;
	this->_movimientoActual.posicionDestino = this->_posicionActual;
	this->_movimientoActual.ejecutando = false;
	this->_hiloMovimiento = NULL;
}

ModeloEntidad::~ModeloEntidad() {
	if (this->_hiloMovimiento != NULL) {
		this->_movimientoActual.ejecutando = false;
		SDL_WaitThread(this->_hiloMovimiento, NULL);
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
	if (this->_hiloMovimiento != NULL) {
		this->_movimientoActual.ejecutando = false;
		SDL_WaitThread(this->_hiloMovimiento, NULL);
	}
	this->_movimientoActual.modeloEntidad = this;
	this->_movimientoActual.posicionDestino = posicionDestino;
	this->_hiloMovimiento = SDL_CreateThread(ModeloEntidad::mover, &this->_movimientoActual);
}

bool ModeloEntidad::operator==(const ModeloEntidad &modeloEntidad) const {
	return this == &modeloEntidad;
}
