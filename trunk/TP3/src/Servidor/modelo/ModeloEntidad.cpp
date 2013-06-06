#include "ModeloEntidad.h"

using namespace std;

ModeloEntidad::ModeloEntidad(const ModeloEntidad &modeloEntidad) {
}

ModeloEntidad& ModeloEntidad::operator=(const ModeloEntidad &modeloEntidad) {
	return *this;
}

ModeloEntidad::ModeloEntidad(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad, int tipoEntidad) {
	this->_alto = alto;
	this->_ancho = ancho;
	this->_velocidad = velocidad;
	this->_posicion = posicion;
	this->_altoNivel = altoNivel;
	this->_anchoNivel = anchoNivel;
	this->_proxyEntidad = proxyEntidad;
	this->_id = id;
	this->_nombreEntidad = nombreEntidad;
	this->_direccion = SUR;
	this->_tipoEntidad = tipoEntidad;
	
	Posicion::convertirTileAPixel(altoNivel, this->_posicion.x, this->_posicion.y, this->_pixelSiguiente.x, this->_pixelSiguiente.y);
}

ModeloEntidad::~ModeloEntidad() {
	if (this->_proxyEntidad != NULL)
		delete this->_proxyEntidad;
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

void ModeloEntidad::nombreEntidad(std::string nombreEntidad) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_nombreEntidad = nombreEntidad;
	this->_mutex.unlock(__FILE__, __LINE__);
}

bool ModeloEntidad::notificar() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	bool notificar = this->_notificar;
	this->_mutex.unlock(__FILE__, __LINE__);
	return notificar;
}

void ModeloEntidad::notificar(bool notificar) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_notificar = notificar;
	this->_mutex.unlock(__FILE__, __LINE__);
}

Posicion ModeloEntidad::posicion() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	Posicion posicionActual = this->_posicion;
	this->_mutex.unlock(__FILE__, __LINE__);
	return posicionActual;
}

void ModeloEntidad::posicion(Posicion posicionActual) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_posicion = posicionActual;
	this->_mutex.unlock(__FILE__, __LINE__);
}

int ModeloEntidad::velocidad() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	int velocidad = this->_velocidad;
	this->_mutex.unlock(__FILE__, __LINE__);
	return velocidad;
}

void ModeloEntidad::velocidad(int velocidad) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_velocidad = velocidad;
	this->_mutex.unlock(__FILE__, __LINE__);
}

ProxyModeloEntidad::stEntidad ModeloEntidad::stEntidad() {
	ProxyModeloEntidad::stEntidad entidad;
	entidad.id = this->id();
	entidad.nombreEntidad = this->nombreEntidad();
	entidad.pixelX = this->pixel().x;
	entidad.pixelY = this->pixel().y;
	entidad.posicionX = this->posicion().x;
	entidad.posicionY = this->posicion().y;
	entidad.esUltimoMovimiento = this->esUltimoMovimiento();
	entidad.tipoEntidad = this->tipoEntidad();
	return entidad;
}

bool ModeloEntidad::enviarEstado(ProxyModeloEntidad::stEntidad estado) {
	this->_notificar = false;
	return this->_proxyEntidad->enviarEntidad(estado);
}

// NOTA: Sólo puede usarse si el cliente está setado en individual
void ModeloEntidad::notificarSoloAlJugador() {
	this->_proxyEntidad->enviarEntidadIndividual(this->stEntidad(),this->id());
	return void();
}

void ModeloEntidad::setMasivo(void){
	this->_proxyEntidad->setMasivoServidor(this->id());
	return void();
}

bool ModeloEntidad::ocupaPosicion(Posicion posicion) {
	return (posicion.x >= this->posicion().x) &&
		(posicion.x <= this->posicion().x + this->ancho() - 1) &&
		(posicion.y >= this->posicion().y) &&
		(posicion.y <= this->posicion().y + this->alto() - 1);
}

bool ModeloEntidad::operator==(const ModeloEntidad &modeloEntidad) const {
	return this == &modeloEntidad;
}

Posicion ModeloEntidad::pixel() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	Posicion pixelSiguiente = this->_pixelSiguiente;
	this->_mutex.unlock(__FILE__, __LINE__);
	return pixelSiguiente;
}

void ModeloEntidad::pixel(Posicion pixelSiguiente) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_pixelSiguiente = pixelSiguiente;
	this->_mutex.unlock(__FILE__, __LINE__);
}

int ModeloEntidad::tipoEntidad(void) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	int tipoEntidad = this->_tipoEntidad;
	this->_mutex.unlock(__FILE__, __LINE__);
	return tipoEntidad;
}
