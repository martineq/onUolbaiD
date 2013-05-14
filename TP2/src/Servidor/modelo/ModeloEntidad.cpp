#include "ModeloEntidad.h"

using namespace std;

void ModeloEntidad::accion(Accion accion) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_accion = accion;
	this->_mutex.unlock(__FILE__, __LINE__);
}

void ModeloEntidad::direccion(Direccion direccion) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_direccion = direccion;
	this->_mutex.unlock(__FILE__, __LINE__);
}

void ModeloEntidad::esUltimoMovimiento(bool esUltimoMovimiento) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_esUltimoMovimiento = esUltimoMovimiento;
	this->_mutex.unlock(__FILE__, __LINE__);
}

void ModeloEntidad::posicionActual(Posicion posicionActual) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_posicionActual = posicionActual;
	if (this->_estadoNivel != NULL)
		this->_estadoNivel->visitar(this->_posicionActual.x, this->_posicionActual.y);
	this->_mutex.unlock(__FILE__, __LINE__);
}

void ModeloEntidad::posicionSiguiente(Posicion posicionSiguiente) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_posicionSiguiente = posicionSiguiente;
	this->_mutex.unlock(__FILE__, __LINE__);
}

void ModeloEntidad::pixelActual(Posicion pixelActual) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_pixelActual = pixelActual;
	this->_mutex.unlock(__FILE__, __LINE__);
}

void ModeloEntidad::pixelSiguiente(Posicion pixelSiguiente) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_pixelSiguiente = pixelSiguiente;
	this->_mutex.unlock(__FILE__, __LINE__);
}

void ModeloEntidad::notificar() {
	this->_proxyEntidad->enviarEntidad(this->stEntidad());
}

void ModeloEntidad::setNombreJugador(std::string nombre){
	this->_nombreJugador = nombre;	
}
ModeloEntidad::ModeloEntidad(const ModeloEntidad &modeloEntidad) {
}

ModeloEntidad& ModeloEntidad::operator=(const ModeloEntidad &modeloEntidad) {
	return *this;
}

ModeloEntidad::ModeloEntidad(int alto, int ancho, int velocidad, Posicion posicion, bool esJugador, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad, std::string mote) {
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
	this->_nombreJugador = mote;
	this->_estaCongelado = false;
	
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

Accion ModeloEntidad::accion() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	Accion accion = this->_accion;
	this->_mutex.unlock(__FILE__, __LINE__);
	return accion;
}

int ModeloEntidad::alto() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	int alto = this->_alto;
	this->_mutex.unlock(__FILE__, __LINE__);
	return alto;
}

int ModeloEntidad::ancho() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	int ancho = this->_ancho;
	this->_mutex.unlock(__FILE__, __LINE__);
	return ancho;
}

Direccion ModeloEntidad::direccion() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	Direccion direccion = this->_direccion;
	this->_mutex.unlock(__FILE__, __LINE__);
	return direccion;
}

bool ModeloEntidad::esJugador() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	bool esJugador = this->_esJugador;
	this->_mutex.unlock(__FILE__, __LINE__);
	return esJugador;
}

bool ModeloEntidad::estaCongelado() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	bool estaCongelado = this->_estaCongelado;
	this->_mutex.unlock(__FILE__, __LINE__);
	return estaCongelado;
}

bool ModeloEntidad::esUltimoMovimiento() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	bool esUltimoMovimiento = this->_esUltimoMovimiento;
	this->_mutex.unlock(__FILE__, __LINE__);
	return esUltimoMovimiento;
}

int ModeloEntidad::id() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	int id = this->_id;
	this->_mutex.unlock(__FILE__, __LINE__);
    return id;
}

string ModeloEntidad::nombreEntidad() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	string nombreEntidad = this->_nombreEntidad;
	this->_mutex.unlock(__FILE__, __LINE__);
	return nombreEntidad;
}

string ModeloEntidad::nombreJugador() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	string nombreJugador = this->_nombreJugador;
	this->_mutex.unlock(__FILE__, __LINE__);
	return nombreJugador;
}

Posicion ModeloEntidad::posicionActual() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	Posicion posicionActual = this->_posicionActual;
	this->_mutex.unlock(__FILE__, __LINE__);
	return posicionActual;
}

Posicion ModeloEntidad::posicionSiguiente() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	Posicion posicionSiguiente = this->_posicionSiguiente;
	this->_mutex.unlock(__FILE__, __LINE__);
	return posicionSiguiente;
}

ProxyModeloEntidad::stEntidad ModeloEntidad::stEntidad() {
	ProxyModeloEntidad::stEntidad entidad;
	ProxyModeloEntidad::cargarStEntidad(entidad,this->id(),false,this->estaCongelado(),this->esJugador(),this->nombreEntidad(),
		this->pixelActual().x,this->pixelActual().y,this->posicionActual().x,this->posicionActual().y,
		this->pixelSiguiente().x,this->pixelSiguiente().y,this->posicionActual().x,this->posicionActual().y,
		this->direccion(),this->esUltimoMovimiento(),this->accion(),this->nombreJugador());
	return entidad;
}

int ModeloEntidad::velocidad() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	int velocidad = this->_velocidad;
	this->_mutex.unlock(__FILE__, __LINE__);
	return velocidad;
}

void ModeloEntidad::estaCongelado(bool estaCongelado) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_estaCongelado = estaCongelado;
	this->_mutex.unlock(__FILE__, __LINE__);
	this->notificar();
}

void ModeloEntidad::asignarListaJugadores(Mutex* mutexListaJugadores, list<ModeloEntidad*>* listaJugadores) {
	this->_modeloMovimiento->asignarListaJugadores(mutexListaJugadores, listaJugadores);
}

void ModeloEntidad::asignarListaEntidades(Mutex* mutexListaEntidades, list<ModeloEntidad*>* listaEntidades) {
	this->_modeloMovimiento->asignarListaEntidades(mutexListaEntidades, listaEntidades);
}

void ModeloEntidad::atacar() {
	this->_modeloMovimiento->detener();
	this->_accion = ATACANDO;
}

void ModeloEntidad::defender() {
	this->_modeloMovimiento->detener();
	this->_accion = DEFENDIENDO;
}

void ModeloEntidad::enviarMensaje(string remitente, string mensaje) {
	ProxyModeloEntidad::stEntidad entidad = this->stEntidad();
	entidad.nombreRemitente = remitente;
	entidad.mensaje = mensaje;
	this->_proxyEntidad->enviarEntidad(entidad);
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

Posicion ModeloEntidad::pixelActual() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	Posicion pixelActual = this->_pixelActual;
	this->_mutex.unlock(__FILE__, __LINE__);
	return pixelActual;
}

Posicion ModeloEntidad::pixelSiguiente() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	Posicion pixelSiguiente = this->_pixelSiguiente;
	this->_mutex.unlock(__FILE__, __LINE__);
	return pixelSiguiente;
}

bool ModeloEntidad::operator==(const ModeloEntidad &modeloEntidad) const {
	return this == &modeloEntidad;
}
