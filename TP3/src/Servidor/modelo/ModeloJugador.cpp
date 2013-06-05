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
		return;
	}

	// Si el enemigo esta en una posicion adyacente y no me estoy moviendo lo ataco
	if (this->_vistaMovimiento->terminado() && (fabs((float)posicionJugador.x - posicionEnemigo.x) <= 1) && (fabs((float)posicionJugador.y - posicionEnemigo.y) <= 1)) {
		// Si el enemigo es autonomo chequeo el tiempo del ultimo cambio de estado para que no pegue muy seguido
		if (this->_autonomo) {
			if (DELAY_ATAQUE > (GetTickCount() - this->_instanteUltimoCambioEstado))
				return;
		}

		this->_modeloEntidad->direccion(Posicion::obtenerDireccion(posicionJugador, posicionEnemigo));
		this->_accion = ATACANDO;
		this->enviarEstado();
		this->_accion = CAMINANDO;
		this->_enemigo->consumirVida(rand() % (this->danioAtaque() + 1));
		this->_enemigo = NULL;
		this->_instanteUltimoCambioEstado = GetTickCount();
		return;
	}

	// Si el enemigo sigue en la zona visible lo sigo persiguiendo
	this->_modeloMovimiento->actualizar(this->_enemigo->modeloEntidad()->posicion());
	this->_accion = CAMINANDO;
	this->_instanteUltimoCambioEstado = GetTickCount();
}

void ModeloJugador::matar() {
	this->_vida = 0;
	this->_estaCongelado = false;
	this->_enemigo = NULL;
	this->_item = NULL;
	this->_estadoNivel->rangoVision(RANGO_VISION);
	this->_modeloMovimiento->detener();
}

void ModeloJugador::recogerItem() {
	Posicion posicionItem = this->_item->modeloEntidad()->posicion();
	Posicion posicionJugador = this->_modeloEntidad->posicion();
	
	// Si el item no esta en una posicion adyacente o me estoy moviendo salgo
	if (!this->_vistaMovimiento->terminado() || (fabs((float)posicionJugador.x - posicionItem.x) > 1) || (fabs((float)posicionJugador.y - posicionItem.y) > 1))
		return;
	
	// Si llegue al item y no fue recogido por nadie recogo
	if (this->_item->disponible()) {
		this->_item->asignarJugador(this);
		this->_item->activar();
	}
	this->_item = NULL;
}

void ModeloJugador::revivir() {
	if (this->_vida > 0)
		return;
	this->_escudo = 0;
	this->_magia = this->_maximoMagia;
	this->_vida = this->_maximoVida;

	// Calculo la posicion donde puede revivir el personaje
	Posicion posicion = this->_posicionInicial;
	Posicion pixel;
	while (this->_listaEntidades->posicionOcupada(posicion)) {
		posicion.x = rand() % this->_anchoNivel;
		posicion.y = rand() % this->_altoNivel;
	}
	this->_modeloEntidad->posicion(posicion);
	Posicion::convertirTileAPixel(this->_altoNivel, posicion.x, posicion.y, pixel.x, pixel.y);
	this->_modeloEntidad->pixel(pixel);
}

ModeloJugador::ModeloJugador(const ModeloJugador &modeloJugador) {
}

ModeloJugador& ModeloJugador::operator=(const ModeloJugador &modeloJugador) {
	return *this;
}

ModeloJugador::ModeloJugador(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, string nombreEntidad, string nombreJugador, int maximoVida, int maximoMagia, int ataque, int idDuenio) {
	this->_altoNivel = altoNivel;
	this->_anchoNivel = anchoNivel;
	this->_accion = CAMINANDO;
	this->_autonomo = false;
	this->_escudo = 0;
	this->_tieneMapa = false;
	this->_estaCongelado = false;
	this->_estaDesconectado = false;
	this->_magia = maximoMagia;
	this->_maximoMagia = maximoMagia;
	this->_nombreJugador = nombreJugador;
	this->_posicionInicial = posicion;
	this->_vida = maximoVida;
	this->_maximoVida = maximoVida;
	this->_ingresoAlJuego = false;
	this->_instanteUltimoCambioEstado = 0;
	this->_danioAtaque = ataque;
	this->_idDuenio = idDuenio;

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
	this->_instanteCongelamiento = GetTickCount();
	this->_mutex.unlock(__FILE__, __LINE__);
	this->enviarEstado();
}

bool ModeloJugador::estaDesconectado() {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	bool estaDesconectado = this->_estaDesconectado;
	this->_mutex.unlock(__FILE__, __LINE__);
	return estaDesconectado;
}

void ModeloJugador::estaDesconectado(bool estaDesconectado) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_estaDesconectado = estaDesconectado;
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
	estado.nombreJugador = this->_nombreJugador;
	estado.escudo = this->_escudo;
	estado.estaCongelado = this->_estaDesconectado || this->_estaCongelado;
	estado.magia = this->_magia;
	estado.maximoVida = this->_maximoVida;
	estado.vida = this->_vida;
	estado.maximoVida = this->_maximoVida;
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

void ModeloJugador::asignarListaEnemigos(ListaJugadores* listaEnemigos) {
	this->_listaEnemigos = listaEnemigos;
}

void ModeloJugador::asignarListaEntidades(ListaEntidades* listaEntidades) {
	this->_listaEntidades = listaEntidades;
	this->_modeloMovimiento->asignarListaEntidades(listaEntidades);
}

void ModeloJugador::asignarListaItems(ListaItems* listaItems) {
	this->_listaItems = listaItems;
}

void ModeloJugador::asignarListaJugadores(ListaJugadores* listaJugadores) {
	this->_listaJugadores = listaJugadores;
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

	// Si el personaje esta congelado chequeo si se puede descongelar
	if (this->_estaCongelado) {
		if (TIEMPO_CONGELAMIENTO < GetTickCount() - this->_instanteCongelamiento)
			this->estaCongelado(false);
		return;
	}

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
	this->enviarEstado();

	//TODO: Falta hacer que dropee items
	// Si el personaje no tiene mas vida lo mato
	if (this->_vida == 0)
		this->matar();

	// Si la entidad no es autonoma la revivo
	if (!this->_autonomo) {
		this->revivir();
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
	if (this->_magia > this->_maximoMagia)
		this->_magia = this->_maximoMagia;
}

void ModeloJugador::recuperarVida(int vida) {
	this->_vida += vida;
	if (this->_vida > this->_maximoVida)
		this->_vida = this->_maximoVida;
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

void ModeloJugador::danioAtaque(int danio){
	this->_danioAtaque = danio;
	return void();
}

int ModeloJugador::danioAtaque(void){
	return this->_danioAtaque;
}

int ModeloJugador::idDuenio(void){
	return this->_idDuenio;
}

int ModeloJugador::maximoVida(void){
	return this->_maximoVida;
}

// Creo una posición libre cercana al jugador para crear el golem
Posicion ModeloJugador::posicionGolem() {

	Posicion posicion = this->modeloEntidad()->posicion();

	// Genero una posición al azar, pero dentro del rango de visión del jugador. Y verifico que la posición no se encentre ocupada.
	while (this->_listaEntidades->posicionOcupada(posicion)) {
		posicion.x = this->coordenadaAlAzar(this->modeloEntidad()->posicion().x,this->_estadoNivel->rangoVision(),0,this->_anchoNivel);
		posicion.y = this->coordenadaAlAzar(this->modeloEntidad()->posicion().y,this->_estadoNivel->rangoVision(),0,this->_altoNivel);
	}

	return posicion;
}

// Calcula una coordenada al azar. Devuelve un valor al azar <media>(+-)<desvio>
// El valor devuelto siempre se acota entre <cotaMinima> y <cotaMaxima> inclusive.
int ModeloJugador::coordenadaAlAzar(int media, int desvio, int cotaMinima , int cotaMaxima ){

	// Verifico consistencia
	if( cotaMinima > cotaMaxima ){
		int temp = cotaMinima;
		cotaMinima = cotaMaxima;
		cotaMaxima = temp;
	}

	// Seteo el mínimo y máximo
	int xMin = media - desvio;
	int xMax = media + desvio;

	// Me fijo que el mínimo y máximo no se salga de los bordes acotados
	if( xMin < cotaMinima ) xMin = cotaMinima;
	if( xMax > cotaMaxima ) xMin = cotaMaxima;

	// Obtengo la posicion al azar
	int xFactorMod = (xMax - xMin) + 1;
	int x = ( rand() % xFactorMod ) + xMin;

	return x;
}