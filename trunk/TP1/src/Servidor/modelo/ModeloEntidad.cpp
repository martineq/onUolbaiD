#include "ModeloEntidad.h"

using namespace std;

long ModeloEntidad::_ultimoId = 0;

ModeloEntidad::ModeloEntidad(const ModeloEntidad &modeloEntidad) {
}

ModeloEntidad& ModeloEntidad::operator=(const ModeloEntidad &modeloEntidad) {
	return *this;
}

ModeloEntidad::ModeloEntidad(int alto, int ancho, int velocidad, Posicion posicion, bool esJugador, int altoMapa, int anchoMapa, int fps) {
	this->_id = (int)InterlockedIncrement(&this->_ultimoId);
	this->_esJugador = esJugador;
	this->_alto = alto;
	this->_ancho = ancho;
	this->_velocidad = velocidad;
	this->_posicionActual = posicion;
	this->_posicionSiguiente = posicion;
	this->_vistaMovimiento = new VistaMovimiento(this, altoMapa, anchoMapa, fps);
	this->_modeloMovimientoActual = NULL;
	this->_altoMapa = altoMapa;
	this->_anchoMapa = anchoMapa;
}

ModeloEntidad::~ModeloEntidad() {
	// Detiene si hay algun movimiento ejecutandose lo detiene
	if (this->_modeloMovimientoActual != NULL) {
		this->_modeloMovimientoActual->detener();
		this->_modeloMovimientoActual->join();
		delete this->_modeloMovimientoActual;
	}
	delete this->_vistaMovimiento;
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

int ModeloEntidad::alto() const {
	return this->_alto;
}

int ModeloEntidad::ancho() const {
	return this->_ancho;
}
		
int ModeloEntidad::velocidad() const {
	return this->_velocidad;
}

Posicion ModeloEntidad::posicionActual() const {
	return this->_posicionActual;
}

Posicion ModeloEntidad::posicionSiguiente() const {
	return this->_posicionSiguiente;
}

Posicion ModeloEntidad::pixelActual() const {
	return this->_pixelActual;
}

Posicion ModeloEntidad::pixelSiguiente() const {
	return this->_pixelSiguiente;
}

Direccion ModeloEntidad::direccion() const {
	return this->_direccion;
}

void ModeloEntidad::mover(Posicion posicionDestino) {
	// Detiene si hay algun movimiento ejecutandose lo detiene
	if (this->_modeloMovimientoActual != NULL) {
		this->_modeloMovimientoActual->detener();
		this->_modeloMovimientoActual->join();
		delete this->_modeloMovimientoActual;
	}

	// Ajusta los movimientos para esten dentro del mapa
	if (posicionDestino.x < 0)
		posicionDestino.x = 0;
	else if (posicionDestino.x >= this->_anchoMapa)
		posicionDestino.x = this->_anchoMapa - 1;
	if (posicionDestino.y < 0)
		posicionDestino.y = 0;
	else if (posicionDestino.y >= this->_altoMapa)
		posicionDestino.y = this->_altoMapa - 1;

	// Inicia un nuevo movimiento
	this->_modeloMovimientoActual = new ModeloMovimiento(this, posicionDestino);
	this->_modeloMovimientoActual->agregarObservador(this->_vistaMovimiento);
	this->_modeloMovimientoActual->start(NULL);
}

bool ModeloEntidad::operator==(const ModeloEntidad &modeloEntidad) const {
	return this == &modeloEntidad;
}
