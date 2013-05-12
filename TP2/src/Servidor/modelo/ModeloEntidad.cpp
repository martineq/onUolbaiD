#include "ModeloEntidad.h"

using namespace std;

void ModeloEntidad::accion(Accion accion) {
	this->_accion = accion;
}

void ModeloEntidad::direccion(Direccion direccion) {
	this->_direccion = direccion;
}

void ModeloEntidad::esUltimoMovimiento(bool esUltimoMovimiento) {
	this->_esUltimoMovimiento = esUltimoMovimiento;
}

void ModeloEntidad::notificar() {
	this->_proxyEntidad->enviarEntidad(this->stEntidad());
}

void ModeloEntidad::posicionActual(Posicion posicionActual) {
	this->_posicionActual = posicionActual;
	if (this->_estadoNivel != NULL)
		this->_estadoNivel->visitar(this->_posicionActual.x, this->_posicionActual.y);
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

ModeloEntidad::ModeloEntidad(const ModeloEntidad &modeloEntidad) {
}

ModeloEntidad& ModeloEntidad::operator=(const ModeloEntidad &modeloEntidad) {
	return *this;
}

ModeloEntidad::ModeloEntidad(int alto, int ancho, int velocidad, Posicion posicion, bool esJugador, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad, std::string nombreJugador) {
	this->_alto = alto;
	this->_ancho = ancho;
	this->_velocidad = velocidad;
	this->_posicionActual = posicion;
	this->_posicionSiguiente = posicion;
	this->_esJugador = esJugador;
	this->_altoNivel = altoNivel;
	this->_anchoNivel = anchoNivel;
	this->_proxyEntidad = proxyEntidad;
	this->_id = id;
	this->_nombreEntidad = nombreEntidad;
	this->_nombreJugador = nombreJugador;
	
	this->_accion = CAMINANDO;
	this->_direccion = SUR;
	this->_estadoNivel = (esJugador) ? new EstadoNivel(altoNivel, anchoNivel, this->_posicionActual.x, this->_posicionActual.y) : NULL;
	this->_modeloMovimiento = new ModeloMovimiento(altoNivel, anchoNivel, this);
	
	Posicion::convertirTileAPixel(altoNivel, this->_posicionActual.x, this->_posicionActual.y, this->_pixelActual.x, this->_pixelActual.y);
	Posicion::convertirTileAPixel(altoNivel, this->_posicionSiguiente.x, this->_posicionSiguiente.y, this->_pixelSiguiente.x, this->_pixelSiguiente.y);

	this->_vistaMovimiento = new VistaMovimiento(this, altoNivel, anchoNivel, fps);
	this->_modeloMovimiento->agregarObservador(this->_vistaMovimiento);
}

ModeloEntidad::~ModeloEntidad() {
	if (this->_estadoNivel != NULL)
		delete this->_estadoNivel;
	delete this->_modeloMovimiento;
	delete this->_vistaMovimiento;
}

Accion ModeloEntidad::accion() const {
	return this->_accion;
}

int ModeloEntidad::alto() const {
	return this->_alto;
}

int ModeloEntidad::ancho() const {
	return this->_ancho;
}

Direccion ModeloEntidad::direccion() const {
	return this->_direccion;
}

bool ModeloEntidad::esJugador() const {
	return this->_esJugador;
}

bool ModeloEntidad::estaCongelado() const {
	return this->_estaCongelado;
}

bool ModeloEntidad::esUltimoMovimiento() const {
	return this->_esUltimoMovimiento;
}

int ModeloEntidad::id() const {
    return this->_id;
}

string ModeloEntidad::nombreEntidad() const {
	return this->_nombreEntidad;
}

string ModeloEntidad::nombreJugador() const {
	return this->_nombreJugador;
}

Posicion ModeloEntidad::posicionActual() const {
	return this->_posicionActual;
}

Posicion ModeloEntidad::posicionSiguiente() const {
	return this->_posicionSiguiente;
}

ProxyModeloEntidad::stEntidad ModeloEntidad::stEntidad() const {
	ProxyModeloEntidad::stEntidad entidad;
/*	ProxyModeloEntidad::cargarStEntidad(entidad, this->id(), false, this->estaCongelado(), this->esJugador(),
		this->nombreEntidad(), this->pixelSiguiente().x, this->pixelSiguiente().y, this->direccion(),
		this->esUltimoMovimiento(), this->posicionActual().x, this->posicionActual().y, this->accion());*/
	ProxyModeloEntidad::cargarStEntidad(entidad,this->id(),false,false,this->esJugador(),this->nombreEntidad(),
		this->pixelActual().x,this->pixelActual().y,this->posicionActual().x,this->posicionActual().y,
		this->pixelSiguiente().x,this->pixelSiguiente().y,this->posicionActual().x,this->posicionActual().y,
		this->direccion(),this->esUltimoMovimiento(),this->accion());
	return entidad;
}

int ModeloEntidad::velocidad() const {
	return this->_velocidad;
}

void ModeloEntidad::estaCongelado(bool estaCongelado) {
	this->_estaCongelado = estaCongelado;
}

void ModeloEntidad::asignarListaJugadores(list<ModeloEntidad*>* listaJugadores) {
	this->_modeloMovimiento->asignarListaJugadores(listaJugadores);
}

void ModeloEntidad::asignarListaEntidades(list<ModeloEntidad*>* listaEntidades) {
	this->_modeloMovimiento->asignarListaEntidades(listaEntidades);
}

void ModeloEntidad::atacar() {
	this->_modeloMovimiento->detener();
	this->_accion = ATACANDO;
}

void ModeloEntidad::defender() {
	this->_modeloMovimiento->detener();
	this->_accion = DEFENDIENDO;
}

void ModeloEntidad::cambiarEstado() {
	if (((this->_accion == ATACANDO) || (this->_accion == DEFENDIENDO)) && this->_vistaMovimiento->terminado()) {
		this->notificar();
		this->_accion = QUIETO;
		return;
	}
	this->_modeloMovimiento->cambiarEstado();
	this->_vistaMovimiento->cambiarEstado();
}

void ModeloEntidad::mover(Posicion posicionDestino) {
	// Ajusta los movimientos para esten dentro del mapa
	if (posicionDestino.x < 0)
		posicionDestino.x = 0;
	else if (posicionDestino.x >= this->_anchoNivel)
		posicionDestino.x = this->_anchoNivel - 1;
	if (posicionDestino.y < 0)
		posicionDestino.y = 0;
	else if (posicionDestino.y >= this->_altoNivel)
		posicionDestino.y = this->_altoNivel - 1;

	this->_modeloMovimiento->actualizar(posicionDestino);
	this->_accion = CAMINANDO;
}

bool ModeloEntidad::ocupaPosicion(Posicion posicion) {
	return (posicion.x >= this->posicionActual().x) &&
		(posicion.x <= this->posicionActual().x + this->ancho() - 1) &&
		(posicion.y >= this->posicionActual().y) &&
		(posicion.y <= this->posicionActual().y + this->alto() - 1);
}

Posicion ModeloEntidad::pixelActual() const {
	return this->_pixelActual;
}

Posicion ModeloEntidad::pixelSiguiente() const {
	return this->_pixelSiguiente;
}

bool ModeloEntidad::operator==(const ModeloEntidad &modeloEntidad) const {
	return this == &modeloEntidad;
}
