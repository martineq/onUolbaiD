#include "ModeloNivel.h"

using namespace std;

ModeloJugador* ModeloNivel::obtenerJugador(int id) {
	return this->listaJugadores.obtenerJugador(id);
}

ModeloJugador* ModeloNivel::obtenerJugador(Posicion posicion) {
	return this->listaJugadores.obtenerJugador(posicion);
}

ModeloJugador* ModeloNivel::obtenerEnemigo(Posicion posicion) {
	std::list<ModeloJugador*> listaEnemigos = this->getEnemigos();
	for (std::list<ModeloJugador*>::iterator itModeloEntidad = listaEnemigos.begin(); itModeloEntidad != listaEnemigos.end(); itModeloEntidad++){
		if ((*itModeloEntidad)->modeloEntidad()->posicion() == posicion)
			return (*itModeloEntidad);
	}
	return NULL;
}

ModeloItem* ModeloNivel::obtenerItem(Posicion posicion) {
	return this->listaItems.obtenerItem(posicion);
}

ModeloNivel::ModeloNivel() {
	this->jugadoresConectados = 0;
	this->listaJugadores.asignarListaEntidades(&this->listaEntidades);
	this->listaEnemigos.asignarListaEntidades(&this->listaEntidades);
	this->listaItems.asignarListaEntidades(&this->listaEntidades);
}

ModeloNivel::~ModeloNivel() {
}

std::list<ModeloJugador*> ModeloNivel::getJugadores() {
	return this->listaJugadores.obtenerJugadores();
}

std::list<ModeloJugador*> ModeloNivel::getEnemigos() {
	return this->listaEnemigos.obtenerJugadores();
}

multimap<pair<int, int>, ModeloItem*> ModeloNivel::getItems() {
	return this->listaItems.obtenerItems();
}

int ModeloNivel::getAnchoTiles() {
	return this->altoTiles;
}

int ModeloNivel::getAltoTiles() {
	return this->anchoTiles;
}

void ModeloNivel::agregarJugador(ModeloJugador* jugador) {
	this->listaJugadores.agregarJugador(jugador);
	jugador->asignarListaEnemigos(&this->listaEnemigos);
	jugador->asignarListaEntidades(&this->listaEntidades);
	jugador->asignarListaItems(&this->listaItems);
	jugador->asignarListaJugadores(&this->listaJugadores);
	jugador->enviarEstado();
}

void ModeloNivel::agregarEnemigo(ModeloJugador* enemigo) {
	this->listaEnemigos.agregarJugador(enemigo);
	enemigo->asignarListaEnemigos(&this->listaEnemigos);
	enemigo->asignarListaEntidades(&this->listaEntidades);
	enemigo->asignarListaItems(&this->listaItems);
	enemigo->asignarListaJugadores(&this->listaJugadores);
}

void ModeloNivel::agregarItem(ModeloItem* item) {
	this->listaItems.agregarItem(item);
	item->enviarEstado();
}

void ModeloNivel::agregarEntidad(ModeloEntidad* entidad) {
	this->listaEntidades.agregarEntidad(entidad);
}

void ModeloNivel::setAltoTiles(int alto){
	this->altoTiles = alto;
}

void ModeloNivel::setAnchoTiles(int ancho){
	this->anchoTiles = ancho;
}

void ModeloNivel::ejecutarAccionJugador(int mouseX, int mouseY, int id) {
	ModeloJugador* jugador = this->obtenerJugador(id);
	
	// Si no encontre jugador o esta congelado salgo
	if ((jugador == NULL) || jugador->estaDesconectado() || jugador->estaCongelado())
		return;
	
	Posicion posicion;
	Posicion::convertirPixelATile(this->getAltoTiles(), mouseX, mouseY, posicion.x, posicion.y);
	
	// Si hice clic en un enemigo valido
	ModeloJugador* enemigo = this->obtenerJugador(posicion);
	if (enemigo == NULL)
		enemigo = this->obtenerEnemigo(posicion);
	if ((enemigo != NULL) && (enemigo != jugador)) {
		// Si el enemigo esta vivo lo ataco y salgo
		if (enemigo->vida() > 0) {
			jugador->atacar(enemigo);
			return;
		}
		
		//Si no esta vivo y es autonomo lo quito de la lista de entidades moviles para que no se colisione mas con el
		if (enemigo->autonomo())
			this->listaEntidades.removerEntidadMovil(enemigo->modeloEntidad());
	}
	
	// Si hice clic en un item valido
	ModeloItem* item = this->obtenerItem(posicion);
	if (item != NULL) {
		// Si el item esta disponible lo recogo
		if (item->disponible()) {
			jugador->recogerItem(item);
			return;
		}
		
		// Si el item no esta disponible lo quito de la lista de entidades para que no se colisione mas con el
		this->listaEntidades.removerEntidad(item->modeloEntidad());
	}
	jugador->mover(posicion);
}

void ModeloNivel::desconectarJugador(int id){
	ModeloJugador* jugador = this->obtenerJugador(id);
	if (jugador == NULL){
		return void();
	}else{
		if( jugador->estaDesconectado() == false ){
			jugador->estaDesconectado(true);
			this->decrementarJugadores();		// Se resta la cantidad de jugadores cuando alguno de ellos tiene error
		}
	}
	return void();
}

bool ModeloNivel::actualizar() {
	std::list<ModeloJugador*> listaJugadores = this->getJugadores();
	std::list<ModeloJugador*> listaEnemigos = this->getEnemigos();
	
	// Ejecuto el cambio de estado de todos los jugadores
	for (std::list<ModeloJugador*>::iterator jugador = listaJugadores.begin(); jugador != listaJugadores.end(); jugador++)
		(*jugador)->cambiarEstado();

	// Ejecuto el cambio de estado de todos los enenmigos vivos y que no esten congelados
	for (std::list<ModeloJugador*>::iterator enemigo = listaEnemigos.begin(); enemigo != listaEnemigos.end(); enemigo++) {
		if ((*enemigo)->vida() == 0)
			continue;
		
		// Busco algun jugador que este en el rango de vision para atacarlo
		for (std::list<ModeloJugador*>::iterator jugador = listaJugadores.begin(); jugador != listaJugadores.end(); jugador++) {
			if ((*enemigo)->estaEnRangoVision(*jugador))
				(*enemigo)->atacar(*jugador);
		}
		
		(*enemigo)->cambiarEstado();
	}
	return true;
}

bool ModeloNivel::posicionOcupada(Posicion posicion){
	return this->listaEntidades.posicionOcupada(posicion);
}

bool ModeloNivel::chequearConexion() {
	if (this->listaJugadores.obtenerJugadores().empty())
		return false;
	return this->listaJugadores.obtenerJugadores().front()->chequearConexion();
}

int ModeloNivel::cantidadJugadores(void){
	int cantidad;
	this->mutexJugadoresConectados.lockLectura(__FILE__,__LINE__);
	cantidad = this->jugadoresConectados;
	this->mutexJugadoresConectados.unlock(__FILE__,__LINE__);
	return cantidad;
}

void ModeloNivel::incrementarJugadores(void){
	this->mutexJugadoresConectados.lockEscritura(__FILE__,__LINE__);
	this->jugadoresConectados = this->jugadoresConectados + 1;
	this->mutexJugadoresConectados.unlock(__FILE__,__LINE__);
}

void ModeloNivel::decrementarJugadores(void){
	this->mutexJugadoresConectados.lockEscritura(__FILE__,__LINE__);
	this->jugadoresConectados = this->jugadoresConectados - 1;
	this->mutexJugadoresConectados.unlock(__FILE__,__LINE__);
}

void ModeloNivel::iniciarNuevosJugadores(void){
	
	std::list<ModeloJugador*> listaJugadores = this->getJugadores();
	for (std::list<ModeloJugador*>::iterator itModeloEntidad = listaJugadores.begin(); itModeloEntidad != listaJugadores.end(); itModeloEntidad++){
		if( (*itModeloEntidad)->ingresoAlJuego() == false ) (*itModeloEntidad)->ingresarAlJuego();
	}

	return void();
}

void ModeloNivel::destruirListas(){
	this->listaJugadores.destruirJugadores();
	this->listaEnemigos.destruirJugadores();
	this->listaItems.destruirItems();
	this->listaEntidades.destruirEntidades();
}
