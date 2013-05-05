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
	// Detecto colision con jugadores
	if (this->_listaJugadores != NULL) {
		list<ModeloEntidad*>::iterator iterador = this->_listaJugadores->begin();

		while (iterador != this->_listaJugadores->end()) {
			if (((*iterador) != this->_modeloEntidad) && (*iterador)->ocupaPosicion(posicion))
				return *iterador;
			iterador++;
		}
	}

	// Detecto colision con entidades
	if (this->_listaEntidades != NULL) {
		list<ModeloEntidad*>::iterator iterador = this->_listaEntidades->begin();

		while (iterador != this->_listaEntidades->end()) {
			if (((*iterador) != this->_modeloEntidad) && (*iterador)->ocupaPosicion(posicion))
				return *iterador;
			iterador++;
		}
	}
	return NULL;
}

int ModeloEntidad::ModeloMovimiento::obtenerX(ModeloEntidad* modeloEntidad) {
	int x = 0;
	while (modeloEntidad != NULL) {
		Posicion posicion = modeloEntidad->posicionActual();
		x = posicion.x--;
		modeloEntidad = this->detectarColision(posicion);
	}
	return x;
}

int ModeloEntidad::ModeloMovimiento::obtenerY(ModeloEntidad* modeloEntidad) {
	int y = 0;
	while (modeloEntidad != NULL) {
		Posicion posicion = modeloEntidad->posicionActual();
		y = posicion.y--;
		modeloEntidad = this->detectarColision(posicion);
	}
	return y;
}

int ModeloEntidad::ModeloMovimiento::obtenerAlto(int y, ModeloEntidad* modeloEntidad) {
	int alto = modeloEntidad->posicionActual().y - y;
	while (modeloEntidad != NULL) {
		alto += modeloEntidad->alto();
		Posicion posicion = modeloEntidad->posicionActual();
		posicion.y += modeloEntidad->alto();
		modeloEntidad = this->detectarColision(posicion);
	}
	return alto;
}

int ModeloEntidad::ModeloMovimiento::obtenerAncho(int x, ModeloEntidad* modeloEntidad) {
	int ancho = modeloEntidad->posicionActual().x - x;
	while (modeloEntidad != NULL) {
		ancho += modeloEntidad->alto();
		Posicion posicion = modeloEntidad->posicionActual();
		posicion.x += modeloEntidad->ancho();
		modeloEntidad = this->detectarColision(posicion);
	}
	return ancho;
}

bool ModeloEntidad::ModeloMovimiento::calcularDesvio(ModeloEntidad* modeloEntidad) {
	// Si ya estoy en el medio de un desvio no lo puedo resolver
	if (this->resolviendoDesvio())
		return false;
	
	Posicion posicionDestino = this->_modeloEntidad->posicionActual();
	int x = this->obtenerX(modeloEntidad);
	int y = this->obtenerY(modeloEntidad);
	int alto = this->obtenerAlto(y, modeloEntidad);
	int ancho = this->obtenerAncho(x, modeloEntidad);
	int desvioNorte = this->_modeloEntidad->posicionActual().y - y + 1;
	int desvioSur = y + alto - this->_modeloEntidad->posicionActual().y;
	int desvioOeste = this->_modeloEntidad->posicionActual().x - x + 1;
	int desvioEste = x + ancho - this->_modeloEntidad->posicionActual().x;

	// Choco con esquina superior izquierda
	if ((this->_modeloEntidad->posicionActual().x < x) && (this->_modeloEntidad->posicionActual().y < y)) {
		// Voy a cara este
		if (this->_posicionDestino.x >= x + ancho)
			posicionDestino.x += desvioEste;
		// Voy a cara sur
		else if (this->_posicionDestino.y >= y + alto)
			posicionDestino.y += desvioSur;
	}
	// Choco con esquina superior derecha
	else if ((this->_modeloEntidad->posicionActual().x >= x + ancho) && (this->_modeloEntidad->posicionActual().y < y)) {
		// Voy a cara oeste
		if (this->_posicionDestino.x < x)
			posicionDestino.x -= desvioOeste;
		// Voy a cara sur
		else if (this->_posicionDestino.y >= y + alto)
			posicionDestino.y += desvioSur;
	}
	// Choco con esquina inferior izquierda
	else if ((this->_modeloEntidad->posicionActual().x < x) && (this->_modeloEntidad->posicionActual().y >= y + alto)) {
		// Voy a cara este
		if (this->_posicionDestino.x >= x + ancho)
			posicionDestino.x += desvioEste;
		// Voy a cara norte
		else if (this->_posicionDestino.y < y)
			posicionDestino.y -= desvioNorte;
	}
	// Choco con esquina inferior derecha
	else if ((this->_modeloEntidad->posicionActual().x >= x + ancho) && (this->_modeloEntidad->posicionActual().y  >= y + alto)) {
		// Voy a cara oeste
		if (this->_posicionDestino.x < x)
			posicionDestino.x -= desvioOeste;
		// Voy a cara norte
		else if (this->_posicionDestino.y < y)
			posicionDestino.y -= desvioNorte;
	}
	// Choco con cara norte
	else if (this->_modeloEntidad->posicionActual().y < y) {
		// Voy a cara este
		if (this->_posicionDestino.x >= x + ancho)
			posicionDestino.x += desvioEste;
		// Voy a cara oeste
		else if (this->_posicionDestino.x < x)
			posicionDestino.x -= desvioOeste;
		// Voy a cara sur
		else if (this->_posicionDestino.y >= y + alto) {
			if (x == 0)
				posicionDestino.x += desvioEste;
			else if (x + ancho == this->_anchoNivel)
				posicionDestino.x -= desvioOeste;
			else if (desvioEste < desvioOeste)
				posicionDestino.x += desvioEste;
			else if (desvioOeste < desvioEste)
				posicionDestino.x -= desvioOeste;
			else
				posicionDestino.x += desvioEste;
		}
	}
	// Choco con cara sur
	else if (this->_modeloEntidad->posicionActual().y >= y + alto) {
		// Voy a cara este
		if (this->_posicionDestino.x >= x + ancho)
			posicionDestino.x += desvioEste;
		// Voy a cara oeste
		else if (this->_posicionDestino.x < x)
			posicionDestino.x -= desvioOeste;
		// Voy a cara norte
		else if (this->_posicionDestino.y < y) {
			if (x == 0)
				posicionDestino.x += desvioEste;
			else if (x + ancho == this->_anchoNivel)
				posicionDestino.x -= desvioOeste;
			else if (desvioEste < desvioOeste)
				posicionDestino.x += desvioEste;
			else if (desvioOeste < desvioEste)
				posicionDestino.x -= desvioOeste;
			else
				posicionDestino.x -= desvioOeste;
		}
	}
	// Choco con cara este
	else if (this->_modeloEntidad->posicionActual().x >= x + ancho) {
		// Voy a cara norte
		if (this->_posicionDestino.y < y)
			posicionDestino.y -= desvioNorte;
		// Voy a cara sur
		else if (this->_posicionDestino.y >= y + alto)
			posicionDestino.y += desvioSur;
		// Voy a cara oeste
		else if (this->_posicionDestino.x < x) {
			if (y == 0)
				posicionDestino.y += desvioSur;
			else if (y + alto == this->_altoNivel)
				posicionDestino.y -= desvioNorte;
			else if (desvioNorte < desvioSur)
				posicionDestino.y -= desvioNorte;
			else if (desvioSur < desvioNorte)
				posicionDestino.y += desvioSur;
			else
				posicionDestino.y -= desvioNorte;
		}
	}
	// Choco con cara oeste
	else if (this->_modeloEntidad->posicionActual().x < x) {
		// Voy a cara norte
		if (this->_posicionDestino.y < y)
			posicionDestino.y -= desvioNorte;
		// Voy a cara sur
		else if (this->_posicionDestino.y >= y + alto)
			posicionDestino.y += desvioSur;
		// Voy a cara este
		else if (this->_posicionDestino.x >= x + ancho) {
			if (y == 0)
				posicionDestino.y += desvioSur;
			else if (y + alto == this->_altoNivel)
				posicionDestino.y -= desvioNorte;
			else if (desvioNorte < desvioSur)
				posicionDestino.y -= desvioNorte;
			else if (desvioSur < desvioNorte)
				posicionDestino.y += desvioSur;
			else
				posicionDestino.y += desvioSur;
		}
	}
	
	// Si el desvio es igual a la posicion actual no lo pude resolver
	if (posicionDestino == this->_modeloEntidad->posicionActual())
		return false;

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
	this->_listaJugadores = NULL;
	this->_listaEntidades = NULL;
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

	// Si ya resolvi el desvio vuelvo a asignar la posicion destino
	if (this->resolviendoDesvio() && (this->_modeloEntidad->posicionActual() == this->_posicionDestinoDesvio))
		this->actualizar(this->_posicionDestino);

	// Obtengo la siguente posicion del movimiento actual
	Posicion posicionSiguiente = this->obtenerPosicionSiguiente();
	this->_modeloEntidad->direccion(this->obtenerDireccion(this->_modeloEntidad->posicionActual(), posicionSiguiente));
	
	// Detecto si hubo colision
	ModeloEntidad* entidadColisionada = this->detectarColision(posicionSiguiente);
	if (entidadColisionada != NULL) {
		// Si la posicion destino esta dentro de la entidad colisionada o si no pudo calcular el desvio me detengo
		if (entidadColisionada->ocupaPosicion(this->_posicionDestino) || !this->calcularDesvio(entidadColisionada)) {
			this->_posicionDestino = this->_modeloEntidad->posicionActual();
			this->_posicionDestinoDesvio = this->_posicionDestino;
			return;
		}

		// Obtengo al nueva posicion con el desvio
		posicionSiguiente = this->obtenerPosicionSiguiente();
		this->_modeloEntidad->direccion(this->obtenerDireccion(this->_modeloEntidad->posicionActual(), posicionSiguiente));
	}

	// Si el movimiento sale del nivel me detengo
	if ((posicionSiguiente.x < 0) || (posicionSiguiente.x >= this->_anchoNivel) || (posicionSiguiente.y < 0) || (posicionSiguiente.y >= this->_altoNivel)) {
		this->_posicionDestino = this->_modeloEntidad->posicionActual();
		this->_posicionDestinoDesvio = this->_posicionDestino;
		return;
	}

	// Si despues de calcular el desvio la siguiente posicion siguie colisionando me detengo
	if (this->detectarColision(posicionSiguiente) != NULL) {
		this->_posicionDestino = this->_modeloEntidad->posicionActual();
		this->_posicionDestinoDesvio = this->_posicionDestino;
		return;
	}

	// Notifico a VistaMovimiento
	this->_modeloEntidad->posicionSiguiente(posicionSiguiente);
	this->notificarObservadores();
	this->_modeloEntidad->posicionActual(this->_modeloEntidad->posicionSiguiente());

	// Si llegue a destino cambio el estado a quieto
	if (this->_modeloEntidad->posicionActual() == this->_posicionDestino)
		this->_modeloEntidad->accion(QUIETO);

	this->_instanteUltimoCambioEstado = GetTickCount();
}

void ModeloEntidad::ModeloMovimiento::asignarListaJugadores(std::list<ModeloEntidad*>* listaJugadores) {
	this->_listaJugadores = listaJugadores;
}

void ModeloEntidad::ModeloMovimiento::asignarListaEntidades(std::list<ModeloEntidad*>* listaEntidades) {
	this->_listaEntidades = listaEntidades;
}
