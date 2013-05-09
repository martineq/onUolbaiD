#include "ModeloEntidad.h"

using namespace std;

long ModeloEntidad::_ultimoId = 0;

ModeloEntidad::ModeloEntidad(const ModeloEntidad &modeloEntidad) {
}

ModeloEntidad& ModeloEntidad::operator=(const ModeloEntidad &modeloEntidad) {
	return *this;
}

void ModeloEntidad::posicionActual(Posicion posicionActual) {
	this->_posicionActual = posicionActual;
}

void ModeloEntidad::posicionSiguiente(Posicion posicionSiguiente) {
	this->_posicionSiguiente = posicionSiguiente;
}

void ModeloEntidad::pixelActual(Posicion pixelActual) {
	this->_pixelActual = pixelActual;
}

void ModeloEntidad::pixelSiguiente(Posicion pixelSiguiente) {
	this->_pixelSiguiente = pixelSiguiente;
}

void ModeloEntidad::esUltimoMovimiento(bool esUltimoMovimiento) {
	this->_esUltimoMovimiento = esUltimoMovimiento;
}

void ModeloEntidad::direccion(Direccion direccion) {
	this->_direccion = direccion;
}

void ModeloEntidad::accion(Accion accion) {
	this->_accion = accion;
}

ModeloEntidad::ModeloEntidad(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps) {
	this->_id = (int)InterlockedIncrement(&this->_ultimoId);
	this->_alto = alto;
	this->_ancho = ancho;
	this->_velocidad = velocidad;
	this->_posicionActual = posicion;
	this->_posicionSiguiente = posicion;
	this->_modeloMovimiento = new ModeloMovimiento(altoNivel, anchoNivel, this);
	this->_vistaMovimiento = new VistaMovimiento(this, altoNivel, anchoNivel, fps);
	this->_altoMapa = altoNivel;
	this->_anchoMapa = anchoNivel;

	this->_direccion = SUR;
	this->_accion = CAMINANDO;
	Posicion::convertirTileAPixel(altoNivel, this->_posicionActual.x, this->_posicionActual.y, this->_pixelActual.x, this->_pixelActual.y);
	Posicion::convertirTileAPixel(altoNivel, this->_posicionSiguiente.x, this->_posicionSiguiente.y, this->_pixelSiguiente.x, this->_pixelSiguiente.y);

	this->_modeloMovimiento->agregarObservador(this->_vistaMovimiento);
}

ModeloEntidad::~ModeloEntidad() {
	delete this->_modeloMovimiento;
	delete this->_vistaMovimiento;
}

void ModeloEntidad::cambiarEstado() {
	//si es quieto no hace nada, puede estar caminando pero que la posicion actual sea igual a la de destino
	if (this->_accion == CAMINANDO)
		this->_modeloMovimiento->cambiarEstado();
	else if ((this->_accion == ATACANDO) || (this->_accion == DEFENDIENDO)) {
		this->notificarObservadores();
		this->_accion = CAMINANDO;
	}
	this->_vistaMovimiento->cambiarEstado();
}

int ModeloEntidad::id() const {
    return this->_id;
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

Accion ModeloEntidad::accion() const {
	return this->_accion;
}

bool ModeloEntidad::esUltimoMovimiento() const {
	return this->_esUltimoMovimiento;
}

void ModeloEntidad::mover(Posicion posicionDestino) {
	// Ajusta los movimientos para esten dentro del mapa
	if (posicionDestino.x < 0)
		posicionDestino.x = 0;
	else if (posicionDestino.x >= this->_anchoMapa)
		posicionDestino.x = this->_anchoMapa - 1;
	if (posicionDestino.y < 0)
		posicionDestino.y = 0;
	else if (posicionDestino.y >= this->_altoMapa)
		posicionDestino.y = this->_altoMapa - 1;

	this->_modeloMovimiento->actualizar(posicionDestino);
	this->_accion = CAMINANDO;
}

bool ModeloEntidad::ocupaPosicion(Posicion posicion) {
	return (posicion.x >= this->posicionActual().x) &&
		(posicion.x <= this->posicionActual().x + this->ancho() - 1) &&
		(posicion.y >= this->posicionActual().y) &&
		(posicion.y <= this->posicionActual().y + this->alto() - 1);
}

void ModeloEntidad::asignarListaJugadores(list<ModeloEntidad*>* listaJugadores) {
	this->_modeloMovimiento->asignarListaJugadores(listaJugadores);
}

void ModeloEntidad::asignarListaEntidades(list<ModeloEntidad*>* listaEntidades) {
	this->_modeloMovimiento->asignarListaEntidades(listaEntidades);
}

bool ModeloEntidad::operator==(const ModeloEntidad &modeloEntidad) const {
	return this == &modeloEntidad;
}

void ModeloEntidad::atacar() {
	std::cout << "Tecla A" << std::endl;
	this->_accion = ATACANDO;
//	this->_tickCounts = GetTickCount();
	this->_modeloMovimiento->actualizar(this->_posicionActual);
}

void ModeloEntidad::defender() {
	std::cout << "Tecla S" << std::endl;
	this->_accion = DEFENDIENDO;
//	this->_tickCounts = GetTickCount();
	this->_modeloMovimiento->actualizar(this->_posicionActual);
}

void ModeloEntidad::setTickCounts(int ticks) {
	this->_tickCounts = ticks;
}

int ModeloEntidad::getTickCounts() {
	return this->_tickCounts;
}

int ModeloEntidad::getAccion() {
	return this->_accion;
}

void ModeloEntidad::setAccion(int estado) {
	this->_accion = (Accion)estado;
}