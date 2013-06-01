#include "ModeloJugador.h"

#define DELAY_ATAQUE 1500

using namespace std;

void ModeloJugador::atacarEnemigo() {
	Posicion posicionEnemigo = this->_enemigo->modeloEntidad()->posicion();
	Posicion posicionJugador = this->_modeloEntidad->posicion();
	
	// Si el enemigo salio de la zona visible o esta muerto dejo de seguirlo y me detengo
	if (!this->estaEnRangoVision(this->_enemigo) || (this->_enemigo->vida() == 0)) {
		this->_modeloMovimiento->detener();
		this->_enemigo = NULL;
		this->_instanteUltimoCambioEstado = GetTickCount();
		return;
	}

	// Si el enemigo esta en una posicion adyacente y no me estoy moviendo lo ataco
	if (this->_vistaMovimiento->terminado() && (fabs((float)posicionJugador.x - posicionEnemigo.x) <= 1) && (fabs((float)posicionJugador.y - posicionEnemigo.y) <= 1)) {
		// Si el enemigo es autonomo chequeo el tiempo del ultimo cambio de estado para que no pegue muy seguido
		if (this->_autonomo) {
			if (this->_instanteUltimoCambioEstado == 0) {
				this->_instanteUltimoCambioEstado = GetTickCount();
				return;
			}

			if (DELAY_ATAQUE > (GetTickCount() - this->_instanteUltimoCambioEstado))
				return;
		}
		
		this->_modeloEntidad->direccion(Posicion::obtenerDireccion(posicionJugador, posicionEnemigo));
		this->_accion = ATACANDO;
		this->enviarEstado();
		this->_accion = CAMINANDO;
		this->_enemigo->consumirVida(rand() % (MAXIMO_DANIO + 1));
		this->_enemigo = NULL;
		this->_instanteUltimoCambioEstado = GetTickCount();
		return;
	}

	// Si el enemigo sigue en la zona visible lo sigo persiguiendo
	this->_modeloMovimiento->actualizar(this->_enemigo->modeloEntidad()->posicion());
	this->_accion = CAMINANDO;
	this->_instanteUltimoCambioEstado = GetTickCount();
}

void ModeloJugador::recogerItem() {
	Posicion posicionItem = this->_item->modeloEntidad()->posicion();
	Posicion posicionJugador = this->_modeloEntidad->posicion();
	
	// Si el item no esta en una posicion adyacente o me estoy moviendo salgo
	if (!this->_vistaMovimiento->terminado() || (fabs((float)posicionJugador.x - posicionItem.x) > 1) || (fabs((float)posicionJugador.y - posicionItem.y) > 1))
		return;
	
	// Si llegue al item y no fue recogido por nadie lo aplico
	if (this->_item->disponible()) {
		this->_item->disponible(false);
		this->_item->aplicar(this);
		this->enviarEstado();
	}
	this->_item = NULL;
}

ModeloJugador::ModeloJugador(const ModeloJugador &modeloJugador) {
}

ModeloJugador& ModeloJugador::operator=(const ModeloJugador &modeloJugador) {
	return *this;
}

ModeloJugador::ModeloJugador(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, string nombreEntidad, string nombreJugador) {
	this->_accion = CAMINANDO;
	this->_autonomo = false;
	this->_escudo = 0;
	this->_tieneMapa = false;
	this->_estaCongelado = false;
	this->_magia = MAXIMO_MAGIA;
	this->_nombreJugador = nombreJugador;
	this->_posicionInicial = posicion;
	this->_vida = MAXIMO_VIDA;
	this->_ingresoAlJuego = false;
	this->_instanteUltimoCambioEstado = 0;
	
	this->_enemigo = NULL;
	this->_item = NULL;
	this->_modeloEntidad = new ModeloEntidad(alto, ancho, velocidad, posicion, altoNivel, anchoNivel, fps, proxyEntidad, id, nombreEntidad);
	this->_estadoNivel = new EstadoNivel(altoNivel, anchoNivel, posicion.x, posicion.y, RANGO_VISION);
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

bool ModeloJugador::autonomo() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	bool autonomo = this->_autonomo;
	this->_mutex.unlock(__FILE__, __LINE__);
	return autonomo;
}

void ModeloJugador::autonomo(bool autonomo) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_autonomo = autonomo;
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
	this->_enemigo = NULL;
	this->_modeloMovimiento->detener();
	this->_mutex.unlock(__FILE__, __LINE__);
	this->enviarEstado();
}

bool ModeloJugador::tieneMapa() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	bool tieneMapa = this->_tieneMapa;
	this->_mutex.unlock(__FILE__, __LINE__);
	return tieneMapa;
}

void ModeloJugador::setTieneMapa(bool loTiene) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_tieneMapa = loTiene;
	this->_mutex.unlock(__FILE__, __LINE__);	
}

int ModeloJugador::magia() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	int magia = this->_magia;
	this->_mutex.unlock(__FILE__, __LINE__);
	return magia;
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
	estado.nombreJugador = this->_nombreJugador;
	estado.escudo = this->_escudo;
	estado.estaCongelado = this->_estaCongelado;
	estado.magia = this->_magia;
	estado.vida = this->_vida;
	estado.rangoVision = this->_estadoNivel->rangoVision();
	estado.tieneMapa = this->_tieneMapa;
	estado.accion = (this->_accion * 8) + this->_modeloEntidad->direccion();	
	return estado;
}

int ModeloJugador::vida() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	int vida = this->_vida;
	this->_mutex.unlock(__FILE__, __LINE__);
	return vida;
}

void ModeloJugador::asignarEntidadesMoviles(Mutex* mutexEntidadesMoviles, list<ModeloEntidad*>* entidadesMoviles) {
	this->_modeloMovimiento->asignarEntidadesMoviles(mutexEntidadesMoviles, entidadesMoviles);
}

void ModeloJugador::asignarEntidades(Mutex* mutexEntidades, multimap<std::pair<int, int>, ModeloEntidad*>* entidades) {
	this->_modeloMovimiento->asignarEntidades(mutexEntidades, entidades);
}

void ModeloJugador::atacar(ModeloJugador* enemigo) {
	if (this->_enemigo == enemigo)
		return;
	this->_item = NULL;
	this->_enemigo = enemigo;
	this->_modeloMovimiento->actualizar(this->_enemigo->modeloEntidad()->posicion());
	this->_accion = CAMINANDO;
}

void ModeloJugador::cambiarEstado() {
	// Marco el tile actual como visitado
	this->_estadoNivel->visitar(this->_modeloEntidad->posicion().x, this->_modeloEntidad->posicion().y);

	// Ejecuto la accion dependiendo de a que estoy persiguiendo
	if (this->_enemigo != NULL)
		this->atacarEnemigo();
	else if (this->_item != NULL)
		this->recogerItem();
	
	this->_modeloMovimiento->cambiarEstado();
	this->_vistaMovimiento->cambiarEstado();
	if (this->_modeloEntidad->notificar())
		this->enviarEstado();
}

void ModeloJugador::cargarMatriz(ProxyModeloEntidad::stEntidad& entidad){
	ProxyModeloEntidad::cargarMatriz(entidad, this->_estadoNivel->getMatriz());
}

bool ModeloJugador::chequearConexion() {
	ProxyModeloEntidad::stEntidad entidad;
	return this->_modeloEntidad->enviarEstado(entidad);
}

void ModeloJugador::consumirMagia(int magia) {
	this->_magia -= magia;
	if (this->_magia < 0)
		this->_magia = 0;
}

void ModeloJugador::consumirVida(int vida) {
	// Quito vida al escudo
	this->_escudo -= vida;

	// Si el escudo no pudo absorver todo el danio le quito el resto a la vida
	if (this->_escudo < 0) {
		this->_vida += this->_escudo;
		if (this->_vida < 0)
			this->_vida = 0;
		this->_escudo = 0;
	}

	//TODO: Falta chequear si la posicion esta ocupada
	//TODO: Falta hacer que dropee items
	// Si el personaje esta muerto y no es autonomo lo devuelvo a su posicion original
	if (this->_vida == 0) {
		this->_escudo = 0;
		this->_magia = MAXIMO_MAGIA;
		if (!this->_autonomo)
			this->_vida = MAXIMO_VIDA;
		this->_estaCongelado = false;
		this->_enemigo = NULL;
		this->_item = NULL;
		//this->_tieneMapa = false; no pierde el mapa una vez aplicado
		this->_estadoNivel->rangoVision(RANGO_VISION);
		this->_modeloEntidad->posicion(this->_posicionInicial);
		this->_modeloEntidad->pixel(this->_pixelInicial);
		this->_estadoNivel->rangoVision(RANGO_VISION);
		this->_modeloMovimiento->detener();
		this->enviarEstado();
	}
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

bool ModeloJugador::estaEnRangoVision(ModeloJugador* enemigo) {
	Posicion posicionEnemigo = enemigo->modeloEntidad()->posicion();
	Posicion posicionJugador = this->_modeloEntidad->posicion();

	return ((posicionEnemigo.x >= posicionJugador.x - this->_estadoNivel->rangoVision()) &&
		(posicionEnemigo.x <= posicionJugador.x + this->_estadoNivel->rangoVision()) &&
		(posicionEnemigo.y >= posicionJugador.y - this->_estadoNivel->rangoVision()) &&
		(posicionEnemigo.y <= posicionJugador.y + this->_estadoNivel->rangoVision()));
}

void ModeloJugador::mover(Posicion posicion) {
	this->_enemigo = NULL;
	this->_item = NULL;
	this->_modeloMovimiento->actualizar(posicion);
	this->_accion = CAMINANDO;
}

void ModeloJugador::recogerItem(ModeloItem* item) {
	this->_enemigo = NULL;
	this->_item = item;
	this->_modeloMovimiento->actualizar(this->_item->modeloEntidad()->posicion());
	this->_accion = CAMINANDO;
}

void ModeloJugador::recuperarEscudo(int escudo) {
	this->_escudo += escudo;
	if (this->_escudo > MAXIMO_ESCUDO)
		this->_escudo = MAXIMO_ESCUDO;
}

void ModeloJugador::recuperarMagia(int magia) {
	this->_magia += magia;
	if (this->_magia > MAXIMO_MAGIA)
		this->_magia = MAXIMO_MAGIA;
}

void ModeloJugador::recuperarVida(int vida) {
	this->_vida += vida;
	if (this->_vida > MAXIMO_VIDA)
		this->_vida = MAXIMO_VIDA;
}

bool ModeloJugador::ingresoAlJuego(void) {
	return this->_ingresoAlJuego;
}

void ModeloJugador::ingresarAlJuego(void) {
	this->_modeloEntidad->notificarSoloAlJugador();	// Mensaje para avisarle al cliente que deje de esperar y comienze con el juego
	this->_modeloEntidad->setMasivo();				// Al comenzar el juego seteo el jugador en masivo
	this->_ingresoAlJuego = true;					// Indico que este jugador ya entró al juego
	this->enviarEstado();							// Para actualizar a los jugadores que estaban desde antes en el juego
	return void();
}

EstadoNivel* ModeloJugador::getEstadoNivel(){
	return this->_estadoNivel;
}
