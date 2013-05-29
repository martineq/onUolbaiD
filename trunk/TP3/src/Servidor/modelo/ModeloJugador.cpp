#include "ModeloJugador.h"

using namespace std;

#define DANIO_MAXIMO 20

ModeloJugador::ModeloJugador(const ModeloJugador &modeloJugador) {
}

ModeloJugador& ModeloJugador::operator=(const ModeloJugador &modeloJugador) {
	return *this;
}

ModeloJugador::ModeloJugador(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, string nombreEntidad, string nombreJugador) {
	this->_posicionInicial = posicion;
	this->_nombreJugador = nombreJugador;
	this->_estaCongelado = false;
	this->_accion = CAMINANDO;
	this->_enemigo = NULL;
	
	this->_modeloEntidad = new ModeloEntidad(alto, ancho, velocidad, posicion, altoNivel, anchoNivel, fps, proxyEntidad, id, nombreEntidad);
	this->_estadoNivel = new EstadoNivel(altoNivel, anchoNivel, posicion.x, posicion.y);
	this->_modeloMovimiento = new ModeloMovimiento(altoNivel, anchoNivel, this->_modeloEntidad);
	this->_vistaMovimiento = new VistaMovimiento(this->_modeloEntidad, altoNivel, anchoNivel, fps);
	
	Posicion::convertirTileAPixel(altoNivel, this->_posicionInicial.x, this->_posicionInicial.y, this->_pixelInicial.x, this->_pixelInicial.y);
	this->_estadoNivel->visitar(posicion.x,posicion.y);
	this->_modeloMovimiento->agregarObservador(this->_vistaMovimiento);
}

ModeloJugador::~ModeloJugador() {
	delete this->_modeloEntidad;
	delete this->_estadoNivel;
	delete this->_modeloMovimiento;
	delete this->_vistaMovimiento;
}

Accion ModeloJugador::accion() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	Accion accion = this->_accion;
	this->_mutex.unlock(__FILE__, __LINE__);
	return accion;
}

void ModeloJugador::accion(Accion accion) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_accion = accion;
	this->_mutex.unlock(__FILE__, __LINE__);
}

bool ModeloJugador::estaCongelado() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	bool estaCongelado = this->_estaCongelado;
	this->_mutex.unlock(__FILE__, __LINE__);
	return estaCongelado;
}

void ModeloJugador::estaCongelado(bool estaCongelado) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_estaCongelado = estaCongelado;
	this->_mutex.unlock(__FILE__, __LINE__);
	this->enviarEstado();
}

string ModeloJugador::nombreJugador() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	string nombreJugador = this->_nombreJugador;
	this->_mutex.unlock(__FILE__, __LINE__);
	return nombreJugador;
}

void ModeloJugador::nombreJugador(std::string nombreJugador) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_nombreJugador = nombreJugador;
	this->_mutex.unlock(__FILE__, __LINE__);
}

ModeloEntidad* ModeloJugador::modeloEntidad() {
	return this->_modeloEntidad;
}

ProxyModeloEntidad::stEntidad ModeloJugador::stEntidad() {
	ProxyModeloEntidad::stEntidad estado = this->_modeloEntidad->stEntidad();
	estado.esJugador = true;
	estado.nombreJugador = this->nombreJugador();
	estado.entidadCongelada = this->_estaCongelado;
	estado.accion = (this->_accion * 8) + this->_modeloEntidad->direccion();
	return estado;
}

void ModeloJugador::asignarEntidadesMoviles(Mutex* mutexEntidadesMoviles, list<ModeloEntidad*>* entidadesMoviles) {
	this->_modeloMovimiento->asignarEntidadesMoviles(mutexEntidadesMoviles, entidadesMoviles);
}

void ModeloJugador::asignarEntidades(Mutex* mutexEntidades, multimap<std::pair<int, int>, ModeloEntidad*>* entidades) {
	this->_modeloMovimiento->asignarEntidades(mutexEntidades, entidades);
}

void ModeloJugador::atacar(ModeloJugador* enemigo) {
	this->_enemigo = enemigo;
	this->_modeloMovimiento->actualizar(this->_enemigo->modeloEntidad()->posicion());
	this->_accion = CAMINANDO;
}

void ModeloJugador::cambiarEstado() {
	// Marco el tile actual como visitado
	this->_estadoNivel->visitar(this->_modeloEntidad->posicion().x, this->_modeloEntidad->posicion().y);

	// Si no estoy persiguiendo a un enemigo ejecuto el cambio de estado normalmente y salgo
	if (this->_enemigo == NULL) {
		this->_modeloMovimiento->cambiarEstado();
		this->_vistaMovimiento->cambiarEstado();
		if (this->_modeloEntidad->notificar())
			this->enviarEstado();
		return;
	}
	
	// Si estoy persiguiendo un enemigo
	Posicion posicionEnemigo = this->_enemigo->modeloEntidad()->posicion();
	Posicion posicionJugador = this->_modeloEntidad->posicion();
	
	// Si el enemigo salio de la zona visible dejo de seguirlo y me detengo
	if ((posicionEnemigo.x < posicionJugador.x - (ZONA_VISIBLE / 2)) || (posicionEnemigo.x > posicionJugador.x + (ZONA_VISIBLE / 2)) || (posicionEnemigo.y < posicionJugador.y - (ZONA_VISIBLE / 2)) || (posicionEnemigo.y > posicionJugador.y + (ZONA_VISIBLE / 2))) {
		this->_modeloMovimiento->detener();
		this->_enemigo = NULL;
		return;
	}

	// Si el enemigo esta en una posicion adyacente y no me estoy moviendo lo ataco
	if (this->_vistaMovimiento->terminado() && (fabs((float)posicionJugador.x - posicionEnemigo.x) <= 1) && (fabs((float)posicionJugador.y - posicionEnemigo.y) <= 1)) {
		this->_modeloEntidad->direccion(Posicion::obtenerDireccion(posicionJugador, posicionEnemigo));
		this->_accion = ATACANDO;
		this->enviarEstado();
		this->_accion = CAMINANDO;
		this->_enemigo->lastimar(rand() % DANIO_MAXIMO);
		this->_enemigo = NULL;
		return;
	}

	// Si el enemigo sigue en la zona visible lo sigo persiguiendo
	this->_modeloMovimiento->actualizar(this->_enemigo->modeloEntidad()->posicion());
	this->_accion = CAMINANDO;
	this->_modeloMovimiento->cambiarEstado();
	this->_vistaMovimiento->cambiarEstado();
	if (this->_modeloEntidad->notificar())
		this->enviarEstado();
}

void ModeloJugador::cargarMatriz(ProxyModeloEntidad::stEntidad& entidad){
	ProxyModeloEntidad::cargarMatriz(entidad, this->_estadoNivel->getMatriz());
}

bool ModeloJugador::chequearConexion() {
	ProxyModeloEntidad::stEntidad entidad = this->stEntidad();
	entidad.id = ID_FALSO;
	return this->_modeloEntidad->enviarEstado(entidad);
}

void ModeloJugador::enviarEstado() {
	this->_modeloEntidad->enviarEstado(this->stEntidad());
}

void ModeloJugador::enviarMensaje(ModeloJugador* remitente, string mensaje) {
	ProxyModeloEntidad::stEntidad entidad = this->stEntidad();
	entidad.idRemitente = remitente->_modeloEntidad->id();
	entidad.mensaje = mensaje;
	this->_modeloEntidad->enviarEstado(entidad);
}

void ModeloJugador::lastimar(int danio) {
	this->_modeloEntidad->posicion(this->_posicionInicial);
	this->_modeloEntidad->pixel(this->_pixelInicial);
	this->enviarEstado();
}

void ModeloJugador::mover(Posicion posicion) {
	this->_enemigo = NULL;
	this->_modeloMovimiento->actualizar(posicion);
	this->_accion = CAMINANDO;
}
