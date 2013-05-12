#include "ModeloEntidad.h"

ModeloEntidad::ModeloEntidad(const ModeloEntidad &modeloEntidad){

}

ModeloEntidad& ModeloEntidad::operator=(const ModeloEntidad &modeloEntidad){
	return *this;
}

ModeloEntidad::ModeloEntidad(int alto, int ancho, int velocidad, Posicion posicion, bool esJugador, int altoMapa, int anchoMapa, int fps, ProxyModeloEntidad* pProxyEntidad,int id,std::string nombreEntidad,std::string nombreJugador) {
	
	this->mutexEntidad.lockEscritura(__FILE__,__LINE__);

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

	this->mutexEntidad.unlock(__FILE__,__LINE__);

}

ModeloEntidad::~ModeloEntidad() {
	this->mutexEntidad.lockEscritura(__FILE__,__LINE__);
		delete this->_modeloMovimiento;
		delete this->_vistaMovimiento;
		delete this->_pProxyEntidad;
	this->mutexEntidad.unlock(__FILE__,__LINE__);
}

void ModeloEntidad::cambiarEstado() {
	// ¿ Va el mutex?
	this->_modeloMovimiento->cambiarEstado();
	this->_vistaMovimiento->cambiarEstado(); 
}

int ModeloEntidad::id() {
	int id = this->getId();
	return id;
}

int ModeloEntidad::getId(){
	int id;
	this->mutexEntidad.lockLectura(__FILE__,__LINE__);
		id = this->_id;
	this->mutexEntidad.unlock(__FILE__,__LINE__);
	return id;
}

std::string ModeloEntidad::getNombreEntidad(){
	std::string nombre;
	this->mutexEntidad.lockLectura(__FILE__,__LINE__);
		nombre = this->_nombreEntidad;
	this->mutexEntidad.unlock(__FILE__,__LINE__);
	return nombre;
}

bool ModeloEntidad::esJugador(){
	bool valor;
	this->mutexEntidad.lockLectura(__FILE__,__LINE__);
		valor =  this->_esJugador;
	this->mutexEntidad.unlock(__FILE__,__LINE__);
	return valor;
}

int ModeloEntidad::alto() {
	int alto;
	this->mutexEntidad.lockLectura(__FILE__,__LINE__);
		alto = this->_alto;
	this->mutexEntidad.unlock(__FILE__,__LINE__);
	return alto;
}

int ModeloEntidad::ancho() {
	int ancho;
	this->mutexEntidad.lockLectura(__FILE__,__LINE__);
		ancho = this->_ancho;
	this->mutexEntidad.unlock(__FILE__,__LINE__);
	return ancho;
}

int ModeloEntidad::velocidad() {
	int velocidad;
	this->mutexEntidad.lockLectura(__FILE__,__LINE__);
		velocidad = this->_velocidad;
	this->mutexEntidad.unlock(__FILE__,__LINE__);
	return velocidad;
}
		
Posicion ModeloEntidad::posicionActual() {
	Posicion posAct;
	this->mutexEntidad.lockLectura(__FILE__,__LINE__);
		posAct = this->_posicionActual;
	this->mutexEntidad.unlock(__FILE__,__LINE__);
	return posAct;
}

Posicion ModeloEntidad::posicionSiguiente() {
	Posicion posSig;
	this->mutexEntidad.lockLectura(__FILE__,__LINE__);
		posSig = this->_posicionSiguiente;
	this->mutexEntidad.unlock(__FILE__,__LINE__);
	return posSig;
}
	
Posicion ModeloEntidad::pixelActual() {
	Posicion pixAct;
	this->mutexEntidad.lockLectura(__FILE__,__LINE__);
		pixAct = this->_pixelActual;
	this->mutexEntidad.unlock(__FILE__,__LINE__);
	return pixAct;
}

Posicion ModeloEntidad::pixelSiguiente() {
	Posicion pixSig;
	this->mutexEntidad.lockLectura(__FILE__,__LINE__);
		pixSig = this->_pixelSiguiente;
	this->mutexEntidad.unlock(__FILE__,__LINE__);
	return pixSig;
}

Direccion ModeloEntidad::direccion() {
	Direccion dir;
	this->mutexEntidad.lockLectura(__FILE__,__LINE__);
		dir = this->_direccion;
	this->mutexEntidad.unlock(__FILE__,__LINE__);
	return dir;
}

bool ModeloEntidad::esUltimoMovimiento() {
	bool valor;
	this->mutexEntidad.lockLectura(__FILE__,__LINE__);
		valor = this->_esUltimoMovimiento;
	this->mutexEntidad.unlock(__FILE__,__LINE__);
	return valor;
}

int ModeloEntidad::altoMapa() {
	int alto;
	this->mutexEntidad.lockLectura(__FILE__,__LINE__);
		alto = this->_altoMapa;
	this->mutexEntidad.unlock(__FILE__,__LINE__);
	return alto;
}

int ModeloEntidad::anchoMapa() {
	int ancho;
	this->mutexEntidad.lockLectura(__FILE__,__LINE__);
		ancho = this->_anchoMapa;
	this->mutexEntidad.unlock(__FILE__,__LINE__);
	return ancho;
}

std::string ModeloEntidad::getNombreJugador() {
	std::string nombre;
	this->mutexEntidad.lockLectura(__FILE__,__LINE__);
		nombre = this->_nombreJugador;
	this->mutexEntidad.unlock(__FILE__,__LINE__);
	return nombre;
}

void ModeloEntidad::setEstaCongelado(bool estado){
	this->mutexEntidad.lockEscritura(__FILE__,__LINE__);
		this->_estaCongelado = estado;
	this->mutexEntidad.unlock(__FILE__,__LINE__);
	
	this->notificarAlProxy();		// Con esto notifico a todos los clientes que se cambió esta condición
}

bool ModeloEntidad::getEstaCongelado() {
	bool valor;
	this->mutexEntidad.lockLectura(__FILE__,__LINE__);
		valor = this->_estaCongelado;
	this->mutexEntidad.unlock(__FILE__,__LINE__);
	return valor;
}

void ModeloEntidad::setPixelActual(Posicion valor){
	this->mutexEntidad.lockEscritura(__FILE__,__LINE__);
		this->_pixelActual = valor;
	this->mutexEntidad.unlock(__FILE__,__LINE__);
}

void ModeloEntidad::setPixelSiguiente(Posicion valor){
	this->mutexEntidad.lockEscritura(__FILE__,__LINE__);
		this->_pixelSiguiente = valor;
	this->mutexEntidad.unlock(__FILE__,__LINE__);
}

void ModeloEntidad::setPosicionActual(Posicion valor){
	this->mutexEntidad.lockEscritura(__FILE__,__LINE__);
		this->_posicionActual = valor;
	this->mutexEntidad.unlock(__FILE__,__LINE__);
}

void ModeloEntidad::setPosicionSiguiente(Posicion valor){
	this->mutexEntidad.lockEscritura(__FILE__,__LINE__);
		this->_posicionSiguiente = valor;
	this->mutexEntidad.unlock(__FILE__,__LINE__);
}

void ModeloEntidad::setDireccion(Direccion valor){
	this->mutexEntidad.lockEscritura(__FILE__,__LINE__);
		this->_direccion = valor;
	this->mutexEntidad.unlock(__FILE__,__LINE__);
}


void ModeloEntidad::setEsUltimoMovimiento(bool valor){
	this->mutexEntidad.lockEscritura(__FILE__,__LINE__);
		this->_esUltimoMovimiento = valor;
	this->mutexEntidad.unlock(__FILE__,__LINE__);
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
	int accion = 0;
	ProxyModeloEntidad::stEntidad entidad;
	ProxyModeloEntidad::cargarStEntidad(entidad,this->id(),false,this->getEstaCongelado(),this->esJugador(),this->getNombreEntidad(),this->pixelSiguiente().x,this->pixelSiguiente().y,this->direccion(),this->esUltimoMovimiento(),this->posicionActual().x,this->posicionActual().y,accion);
	return entidad;
}
