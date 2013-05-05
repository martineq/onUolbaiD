#include "ModeloEntidad.h"

ModeloEntidad::ModeloEntidad(const ModeloEntidad &modeloEntidad){

}

ModeloEntidad& ModeloEntidad::operator=(const ModeloEntidad &modeloEntidad){
	return *this;
}

ModeloEntidad::ModeloEntidad(int alto, int ancho, int velocidad, Posicion posicion, bool esJugador, int altoMapa, int anchoMapa, int fps, ProxyModeloEntidad* pProxyEntidad,int id) {
	this->_id = id;
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
	ProxyModeloEntidad::stEntidad entidad;
	entidad.id = this->id();
	entidad.pixelSiguienteX = this->pixelSiguiente().x;
	entidad.pixelSiguienteY = this->pixelSiguiente().y;
	entidad.direccion = this->direccion();
	entidad.esUltimoMovimiento = this->esUltimoMovimiento();
	// TODO: agregar en el ProxyModeloEntidad::stEntidad y acá los nuevos atributos para el TP2
	// Agregar un: entidad.eliminarEntidad = this->eliminarEntidad();
	this->_pProxyEntidad->enviarEntidad(entidad);

	return void();
}
