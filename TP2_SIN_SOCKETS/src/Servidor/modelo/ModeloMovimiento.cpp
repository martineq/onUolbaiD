#include "ModeloEntidad.h"

using namespace std;

Direccion ModeloEntidad::ModeloMovimiento::obtenerDireccion(Posicion posicionOrigen, Posicion posicionDestino) {
	if (posicionOrigen.x > posicionDestino.x) {
		if (posicionOrigen.y > posicionDestino.y)
			return NOROESTE;
		else if (posicionOrigen.y < posicionDestino.y)
			return SUDOESTE;
		else
			return OESTE;
	}
	else if (posicionOrigen.x < posicionDestino.x)
		if (posicionOrigen.y > posicionDestino.y)
			return NORESTE;
		else if (posicionOrigen.y < posicionDestino.y)
			return SUDESTE;
		else
			return ESTE;
	else {
		if (posicionOrigen.y > posicionDestino.y)
			return NORTE;
		else if (posicionOrigen.y < posicionDestino.y)
			return SUR;
		else
			return SUR;
	}
}

Posicion ModeloEntidad::ModeloMovimiento::obtenerPosicionSiguiente() {
	Posicion posicionSiguiente = this->_modeloEntidad->posicionActual();

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

	return posicionSiguiente;
}

ModeloEntidad* ModeloEntidad::ModeloMovimiento::detectarColision(Posicion posicion) {
	list<ModeloEntidad*>::iterator iterador = this->_listaEntidades->begin();

	while (iterador != this->_listaEntidades->end()) {
		if (((*iterador) != this->_modeloEntidad) && 
			(posicion.x >= (*iterador)->posicionActual().x) &&
			(posicion.x <= (*iterador)->posicionActual().x + (*iterador)->ancho() - 1) &&
			(posicion.y >= (*iterador)->posicionActual().y) &&
			(posicion.y <= (*iterador)->posicionActual().y + (*iterador)->alto() - 1)) {
			return *iterador;
		}
		iterador++;
	}
	return NULL;
}

bool ModeloEntidad::ModeloMovimiento::calcularDesvio(ModeloEntidad* modeloEntidad) {
	if (this->resolviendoDesvio())
		return false;
	
	Posicion posicionDestino = this->_modeloEntidad->posicionActual();
	Direccion direccion = this->obtenerDireccion(this->_modeloEntidad->posicionActual(), this->_posicionDestino);
	int desvioNorte = this->_modeloEntidad->posicionActual().y - modeloEntidad->posicionActual().y + 1;
	int desvioSur = modeloEntidad->posicionActual().y + modeloEntidad->alto() - this->_modeloEntidad->posicionActual().y;
	int desvioOeste = this->_modeloEntidad->posicionActual().x - modeloEntidad->posicionActual().x + 1;
	int desvioEste = modeloEntidad->posicionActual().x + modeloEntidad->ancho() - this->_modeloEntidad->posicionActual().x;

	// Choco con cara norte
	if (this->_modeloEntidad->posicionActual().x < modeloEntidad->posicionActual().x) {
		// Si el obstaculo esta en el inicio del nivel
		if (modeloEntidad->posicionActual().y == 0)
			posicionDestino.y += desvioSur;
		// Si el obstaculo llega hasta el fin del nivel
		else if (modeloEntidad->posicionActual().y + modeloEntidad->alto() == this->_altoNivel)
			posicionDestino.y -= desvioNorte;
		else if (direccion == ESTE) {
			if (desvioNorte < desvioSur)
				posicionDestino.y -= desvioNorte;
			else if (desvioNorte > desvioSur)
				posicionDestino.y += desvioSur;
			else 
				posicionDestino.y -= desvioNorte;
		}
		else if (direccion == NORESTE)
			posicionDestino.y -= desvioNorte;
		else if (direccion == SUDESTE)
			posicionDestino.y += desvioSur;
		else
			return false;
	}
	// Choco con cara sur
	else if (this->_modeloEntidad->posicionActual().x >= modeloEntidad->posicionActual().x + modeloEntidad->ancho()) {
		if (modeloEntidad->posicionActual().y == 0)
			posicionDestino.y += desvioSur;
		else if (modeloEntidad->posicionActual().y + modeloEntidad->alto() == this->_altoNivel)
			posicionDestino.y -= desvioNorte;
		else if (direccion == OESTE) {
			if (desvioNorte < desvioSur)
				posicionDestino.y -= desvioNorte;
			else if (desvioNorte > desvioSur)
				posicionDestino.y += desvioSur;
			else
				posicionDestino.y += desvioSur;
		}
		else if (direccion == NOROESTE)
			posicionDestino.y -= desvioNorte;
		else if (direccion == SUDOESTE)
			posicionDestino.y += desvioSur;
		else
			return false;
	}
	// Choco con cara este
	else if (this->_modeloEntidad->posicionActual().y >= modeloEntidad->posicionActual().y + modeloEntidad->alto()) {
		if (modeloEntidad->posicionActual().x == 0)
			posicionDestino.x += desvioEste;
		else if (modeloEntidad->posicionActual().x + modeloEntidad->ancho() == this->_anchoNivel)
			posicionDestino.x -= desvioOeste;
		else if (direccion == NORTE) {
			if (desvioOeste < desvioEste)
				posicionDestino.x -= desvioOeste;
			else if (desvioOeste > desvioEste)
				posicionDestino.x += desvioEste;
			else
				posicionDestino.x -= desvioOeste;
		}
		else if (direccion == NORESTE)
			posicionDestino.x += desvioEste;
		else if (direccion == NOROESTE)
			posicionDestino.x -= desvioOeste;
		else
			false;
	}
	// Choco con cara oeste
	else if (this->_modeloEntidad->posicionActual().y < modeloEntidad->posicionActual().y) {
		if (modeloEntidad->posicionActual().x == 0)
			posicionDestino.x += desvioEste;
		else if (modeloEntidad->posicionActual().x + modeloEntidad->ancho() == this->_anchoNivel)
			posicionDestino.x -= desvioOeste;
		else if (direccion == SUR) {
			if (desvioOeste < desvioEste)
				posicionDestino.x -= desvioOeste;
			else if (desvioOeste > desvioEste)
				posicionDestino.x += desvioEste;
			else
				posicionDestino.x += desvioEste;
		}
		else if (direccion == SUDESTE)
			posicionDestino.x += desvioEste;
		else if (direccion == SUDOESTE)
			posicionDestino.x -= desvioOeste;
		else
			false;
	}
	else
		false;
	
	this->_posicionDestinoDesvio = posicionDestino;
	this->_deltaX = abs(this->_posicionDestinoDesvio.x - this->_modeloEntidad->posicionActual().x);
	this->_deltaY = abs(this->_posicionDestinoDesvio.y - this->_modeloEntidad->posicionActual().y);
	this->_desplazamientoX = (this->_modeloEntidad->posicionActual().x < this->_posicionDestinoDesvio.x) ? 1 : -1;
	this->_desplazamientoY = (this->_modeloEntidad->posicionActual().y < this->_posicionDestinoDesvio.y) ? 1 : -1;
	this->_error = (this->_deltaX >= this->_deltaY) ? this->_deltaX : this->_deltaY;
	this->_desplazamientoErrorX = 2 * this->_deltaX;
	this->_desplazamientoErrorY = 2 * this->_deltaY;
	this->_modeloEntidad->posicionSiguiente(this->_modeloEntidad->posicionActual());

	return true;
}

bool ModeloEntidad::ModeloMovimiento::resolviendoDesvio() const {
	return (this->_posicionDestino != this->_posicionDestinoDesvio);
}

ModeloEntidad::ModeloMovimiento::ModeloMovimiento(const ModeloMovimiento &modeloMovimiento) {
}

ModeloEntidad::ModeloMovimiento& ModeloEntidad::ModeloMovimiento::operator=(const ModeloMovimiento &modeloMovimiento) {
	return *this;
}

ModeloEntidad::ModeloMovimiento::ModeloMovimiento(int altoNivel, int anchoNivel, ModeloEntidad* modeloEntidad) {
	this->_altoNivel = altoNivel;
	this->_anchoNivel = anchoNivel;
	this->_modeloEntidad = modeloEntidad;
	this->_posicionDestino = this->_modeloEntidad->posicionActual();
    this->_posicionDestinoDesvio = this->_posicionDestino;
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
	this->_posicionDestinoDesvio = this->_posicionDestino;
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

	if (this->resolviendoDesvio() && (this->_modeloEntidad->posicionActual() == this->_posicionDestinoDesvio)) {
		this->_posicionDestino = this->_modeloEntidad->posicionActual();
		this->_posicionDestinoDesvio = this->_posicionDestino;
		return;
	}

	Posicion posicionSiguiente = this->obtenerPosicionSiguiente();
	this->_modeloEntidad->direccion(this->obtenerDireccion(this->_modeloEntidad->posicionActual(), posicionSiguiente));
	
	ModeloEntidad* entidadColisionada = this->detectarColision(posicionSiguiente);
	if (entidadColisionada != NULL) {
		if (!this->calcularDesvio(entidadColisionada)) {
			this->_posicionDestino = this->_modeloEntidad->posicionActual();
			this->_posicionDestinoDesvio = this->_posicionDestino;
			return;
		}
		posicionSiguiente = this->obtenerPosicionSiguiente();
		this->_modeloEntidad->direccion(this->obtenerDireccion(this->_modeloEntidad->posicionActual(), posicionSiguiente));
	}

	this->_modeloEntidad->posicionSiguiente(posicionSiguiente);
	this->notificarObservadores();
	this->_modeloEntidad->posicionActual(this->_modeloEntidad->posicionSiguiente());

	this->_instanteUltimoCambioEstado = GetTickCount();
}

void ModeloEntidad::ModeloMovimiento::asignarListaEntidades(std::list<ModeloEntidad*>* listaEntidades) {
	this->_listaEntidades = listaEntidades;
}
