#include "ModeloEntidad.h"

using namespace std;

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
	if (this->_estadoNivel != NULL)
		this->_estadoNivel->visitar(posicion.x,posicion.y);
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
	if (this->_proxyEntidad != NULL) delete this->_proxyEntidad;
}

Accion ModeloEntidad::accion() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	Accion accion = this->_accion;
	this->_mutex.unlock(__FILE__, __LINE__);
	return accion;
}

void ModeloEntidad::accion(Accion accion) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_accion = accion;
	this->_mutex.unlock(__FILE__, __LINE__);
}

int ModeloEntidad::alto() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	int alto = this->_alto;
	this->_mutex.unlock(__FILE__, __LINE__);
	return alto;
}

void ModeloEntidad::alto(int alto) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_alto = alto;
	this->_mutex.unlock(__FILE__, __LINE__);
}

int ModeloEntidad::ancho() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	int ancho = this->_ancho;
	this->_mutex.unlock(__FILE__, __LINE__);
	return ancho;
}

void ModeloEntidad::ancho(int ancho) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_ancho = ancho;
	this->_mutex.unlock(__FILE__, __LINE__);
}

Direccion ModeloEntidad::direccion() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	Direccion direccion = this->_direccion;
	this->_mutex.unlock(__FILE__, __LINE__);
	return direccion;
}

void ModeloEntidad::direccion(Direccion direccion) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_direccion = direccion;
	this->_mutex.unlock(__FILE__, __LINE__);
}

bool ModeloEntidad::esJugador() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	bool esJugador = this->_esJugador;
	this->_mutex.unlock(__FILE__, __LINE__);
	return esJugador;
}

void ModeloEntidad::esJugador(bool esJugador) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_esJugador = esJugador;
	this->_mutex.unlock(__FILE__, __LINE__);
}

bool ModeloEntidad::estaCongelado() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	bool estaCongelado = this->_estaCongelado;
	this->_mutex.unlock(__FILE__, __LINE__);
	return estaCongelado;
}

void ModeloEntidad::estaCongelado(bool estaCongelado) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_estaCongelado = estaCongelado;
	this->_mutex.unlock(__FILE__, __LINE__);
	this->notificar();
}

bool ModeloEntidad::esUltimoMovimiento() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	bool esUltimoMovimiento = this->_esUltimoMovimiento;
	this->_mutex.unlock(__FILE__, __LINE__);
	return esUltimoMovimiento;
}

void ModeloEntidad::esUltimoMovimiento(bool esUltimoMovimiento) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_esUltimoMovimiento = esUltimoMovimiento;
	this->_mutex.unlock(__FILE__, __LINE__);
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

void ModeloEntidad::nombreEntidad(std::string nombreEntidad){
	this->_nombreEntidad = nombreEntidad;
}

string ModeloEntidad::nombreJugador() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	string nombreJugador = this->_nombreJugador;
	this->_mutex.unlock(__FILE__, __LINE__);
	return nombreJugador;
}

void ModeloEntidad::nombreJugador(std::string nombreJugador){
	this->_nombreJugador = nombreJugador;
}

void ModeloEntidad::notificar() {
	this->_proxyEntidad->enviarEntidad(this->stEntidad());	
}

Posicion ModeloEntidad::posicionActual() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	Posicion posicionActual = this->_posicionActual;
	this->_mutex.unlock(__FILE__, __LINE__);
	return posicionActual;
}

void ModeloEntidad::posicionActual(Posicion posicionActual) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_posicionActual = posicionActual;
	if (this->_estadoNivel != NULL)
		this->_estadoNivel->visitar(this->_posicionActual.x, this->_posicionActual.y);
	this->_mutex.unlock(__FILE__, __LINE__);
}

Posicion ModeloEntidad::posicionSiguiente() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	Posicion posicionSiguiente = this->_posicionSiguiente;
	this->_mutex.unlock(__FILE__, __LINE__);
	return posicionSiguiente;
}

void ModeloEntidad::posicionSiguiente(Posicion posicionSiguiente) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_posicionSiguiente = posicionSiguiente;
	this->_mutex.unlock(__FILE__, __LINE__);
}

ProxyModeloEntidad::stEntidad ModeloEntidad::stEntidad() {
	ProxyModeloEntidad::stEntidad entidad;
	ProxyModeloEntidad::cargarStEntidad(entidad,this->id(),false,this->estaCongelado(),this->esJugador(),this->nombreEntidad(),
		this->pixelActual().x,this->pixelActual().y,this->posicionActual().x,this->posicionActual().y,this->pixelSiguiente().x,
		this->pixelSiguiente().y,this->posicionActual().x,this->posicionActual().y,this->direccion(),this->esUltimoMovimiento(),
		this->accion(),this->nombreJugador());	
	return entidad;
}

void ModeloEntidad::cargarMatriz(ProxyModeloEntidad::stEntidad& entidad){
	ProxyModeloEntidad::cargarMatriz(entidad,this->_estadoNivel->getMatriz());
}

int ModeloEntidad::velocidad() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	int velocidad = this->_velocidad;
	this->_mutex.unlock(__FILE__, __LINE__);
	return velocidad;
}

void ModeloEntidad::asignarEntidadesMoviles(Mutex* mutexEntidadesMoviles, list<ModeloEntidad*>* entidadesMoviles) {
	this->_modeloMovimiento->asignarEntidadesMoviles(mutexEntidadesMoviles, entidadesMoviles);
}

void ModeloEntidad::asignarEntidades(Mutex* mutexEntidades, multimap<std::pair<int, int>, ModeloEntidad*>* entidades) {
	this->_modeloMovimiento->asignarEntidades(mutexEntidades, entidades);
}

bool ModeloEntidad::chequearConexion() {
	ProxyModeloEntidad::stEntidad entidad = this->stEntidad();
	entidad.id = ID_FALSO;
	return this->_proxyEntidad->enviarEntidad(entidad);
}

void ModeloEntidad::detener() {
	this->_modeloMovimiento->detener();
}

bool ModeloEntidad::enMovimiento() {
	return !this->_vistaMovimiento->terminado();
}

void ModeloEntidad::enviarMensaje(ModeloEntidad* remitente, string mensaje) {
	ProxyModeloEntidad::stEntidad entidad = this->stEntidad();
	entidad.idRemitente = remitente->id();
	entidad.mensaje = mensaje;
	this->_proxyEntidad->enviarEntidad(entidad);
}

void ModeloEntidad::cambiarEstado() {
	this->_modeloMovimiento->cambiarEstado();
	this->_vistaMovimiento->cambiarEstado();
}

void ModeloEntidad::mover(Posicion posicionDestino) {
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

bool ModeloEntidad::operator==(const ModeloEntidad &modeloEntidad) const {
	return this == &modeloEntidad;
}

void ModeloEntidad::pixelActual(Posicion pixelActual) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_pixelActual = pixelActual;
	this->_mutex.unlock(__FILE__, __LINE__);
}

Posicion ModeloEntidad::pixelSiguiente() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	Posicion pixelSiguiente = this->_pixelSiguiente;
	this->_mutex.unlock(__FILE__, __LINE__);
	return pixelSiguiente;
}

void ModeloEntidad::pixelSiguiente(Posicion pixelSiguiente) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_pixelSiguiente = pixelSiguiente;
	this->_mutex.unlock(__FILE__, __LINE__);
}
