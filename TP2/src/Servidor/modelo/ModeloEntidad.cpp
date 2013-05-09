#include "ModeloEntidad.h"

ModeloEntidad::ModeloEntidad(const ModeloEntidad &modeloEntidad){

}

ModeloEntidad& ModeloEntidad::operator=(const ModeloEntidad &modeloEntidad){
	return *this;
}

ModeloEntidad::ModeloEntidad(int alto, int ancho, int velocidad, Posicion posicion, bool esJugador, int altoMapa, int anchoMapa, int fps, ProxyModeloEntidad* pProxyEntidad,int id,std::string nombreEntidad,std::string nombreJugador) {
	this->_id = id;
	this->_nombreEntidad = nombreEntidad;
	this->_nombreJugador = nombreJugador;
	this->_estaCongelado = false;
	this->_esJugador = esJugador;
	this->_alto = alto;
	this->_ancho = ancho;
	this->_velocidad = velocidad;
	this->_posicionActual = posicion;
	this->_posicionSiguiente = posicion;
	this->_modeloMovimiento = new ModeloMovimiento(this);
	this->_vistaMovimiento = new VistaMovimiento(this, altoMapa, anchoMapa, fps);
	this->_altoMapa = altoMapa;
	this->_anchoMapa = anchoMapa;
	this->_pProxyEntidad = pProxyEntidad;

	this->_direccion = SUR;
	Posicion::convertirTileAPixel(altoMapa, this->_posicionActual.x, this->_posicionActual.y, this->_pixelActual.x, this->_pixelActual.y);
	Posicion::convertirTileAPixel(altoMapa, this->_posicionSiguiente.x, this->_posicionSiguiente.y, this->_pixelSiguiente.x, this->_pixelSiguiente.y);

	this->_modeloMovimiento->agregarObservador(this->_vistaMovimiento);
}

ModeloEntidad::~ModeloEntidad() {
	delete this->_modeloMovimiento;
	delete this->_vistaMovimiento;
	delete this->_pProxyEntidad;
}

void ModeloEntidad::cambiarEstado() {
	this->_modeloMovimiento->cambiarEstado();
	this->_vistaMovimiento->cambiarEstado(); 
}

int ModeloEntidad::id() const {
    return this->_id;
}

std::string ModeloEntidad::getNombreEntidad() const {
    return this->_nombreEntidad;
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
}

bool ModeloEntidad::operator==(const ModeloEntidad &modeloEntidad) const {
	return this == &modeloEntidad;
}

void ModeloEntidad::notificarAlProxy(void){
	ProxyModeloEntidad::stEntidad entidad = this->getStEntidad();
	this->_pProxyEntidad->enviarEntidad(entidad);
	return void();
}

ProxyModeloEntidad::stEntidad ModeloEntidad::getStEntidad(){
	ProxyModeloEntidad::stEntidad entidad;
	ProxyModeloEntidad::cargarStEntidad(entidad,this->id(),false,this->getEstaCongelado(),this->getNombreEntidad(),this->pixelSiguiente().x,this->pixelSiguiente().y,this->direccion(),this->esUltimoMovimiento());
	
	// TODO: agregar en el ProxyModeloEntidad::stEntidad y acá los nuevos atributos para el TP2
	
	return entidad;
}

void ModeloEntidad::setNombreJugador(std::string nombre){
	this->_nombreJugador = nombre;
}

std::string ModeloEntidad::getNombreJugador() const {
	return this->_nombreJugador;
}

void ModeloEntidad::setEstaCongelado(bool estado){
	this->_estaCongelado = estado;
	this->notificarAlProxy(); // Con esto notifico a todos los clientes que se cambió esta condición
}

bool ModeloEntidad::getEstaCongelado() const {
	return this->_estaCongelado;
}