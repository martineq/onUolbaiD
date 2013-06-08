#include "ModeloNivel.h"

using namespace std;

void ModeloNivel::actualizarJugadores(std::list<ModeloJugador*>* listaJugadores, std::list<ModeloJugador*>* listaEnemigos, std::list<ModeloJugador*>* listaGolems) {
	for (std::list<ModeloJugador*>::iterator jugador = listaJugadores->begin(); jugador != listaJugadores->end(); jugador++)
		(*jugador)->cambiarEstado();
}

void ModeloNivel::actualizarEnemigos(std::list<ModeloJugador*>* listaJugadores, std::list<ModeloJugador*>* listaEnemigos, std::list<ModeloJugador*>* listaGolems) {
	if (listaEnemigos->empty())
		return;
	
	std::list<ModeloJugador*>::iterator enemigo = listaEnemigos->begin();
	std::advance(enemigo, indiceEnemigo);

	if ((*enemigo)->vida() == 0) {
		indiceEnemigo++;
		if (indiceEnemigo >= listaEnemigos->size())
			indiceEnemigo = 0;
		return;
	}

	for (std::list<ModeloJugador*>::iterator jugador = listaJugadores->begin(); jugador != listaJugadores->end(); jugador++) {
		if ((*enemigo)->estaEnRangoVision(*jugador)) {
			(*enemigo)->atacar(*jugador);
			break;
		}
	}
	(*enemigo)->cambiarEstado();
	
	indiceEnemigo++;
	if (indiceEnemigo >= listaEnemigos->size())
		indiceEnemigo = 0;
}

void ModeloNivel::actualizarGolems(std::list<ModeloJugador*>* listaJugadores, std::list<ModeloJugador*>* listaEnemigos, std::list<ModeloJugador*>* listaGolems) {
	// Actualizo el golem que le toca en esta iteracion
	if (listaGolems->empty())
		return;
	std::list<ModeloJugador*>::iterator golem = listaGolems->begin();
	std::advance(golem, indiceGolem);

	if ((*golem)->vida() == 0) {
		indiceGolem++;
		if (indiceGolem >= listaGolems->size())
			indiceGolem = 0;
		return;
	}

	(*golem)->mover(this->obtenerJugador((*golem)->idDuenio())->modeloEntidad()->posicion());

	// Busco algun jugador que este en el rango de vision para atacarlo y que sea disitinto al dueño
	for (std::list<ModeloJugador*>::iterator jugador = listaJugadores->begin(); jugador != listaJugadores->end(); jugador++) {
		if ((*golem)->estaEnRangoVision(*jugador) && ((*golem)->idDuenio() != (*jugador)->modeloEntidad()->id())) {
			(*golem)->atacar(*jugador);
			break;
		}
	}
			
	// Busco algun enemigo que este en el rango de vision para atacarlo
	for (std::list<ModeloJugador*>::iterator enemigo = listaEnemigos->begin(); enemigo != listaEnemigos->end(); enemigo++) {
		if ((*golem)->estaEnRangoVision(*enemigo) && ((*enemigo)->vida() > 0)) {
			(*golem)->atacar(*enemigo);
			break;
		}
	}
	(*golem)->cambiarEstado();

	indiceGolem++;
	if (indiceGolem >= listaGolems->size())
		indiceGolem = 0;
}

void ModeloNivel::actualizarItems() {
	std::multimap<std::pair<int, int>, ModeloItem*> listaItems = this->getItems();
	for (std::multimap<std::pair<int, int>, ModeloItem*>::iterator item = listaItems.begin(); item != listaItems.end(); item++)
		(*item).second->cambiarEstado();
}

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
	this->indiceEnemigo = 0;
	this->indiceGolem = 0;
	this->jugadoresConectados = 0;
	this->listaJugadores.asignarListaEntidades(&this->listaEntidades);
	this->listaEnemigos.asignarListaEntidades(&this->listaEntidades);
	this->listaItems.asignarListaEntidades(&this->listaEntidades);
	this->listaGolems.asignarListaEntidades(&this->listaEntidades);
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
	jugador->asignarListaItems(&this->listaItems);
	jugador->asignarListaJugadores(&this->listaJugadores);
	jugador->enviarEstado();
}

void ModeloNivel::agregarEnemigo(ModeloJugador* enemigo) {
	this->listaEnemigos.agregarJugador(enemigo);
	enemigo->asignarListaEnemigos(&this->listaEnemigos);
	enemigo->asignarListaItems(&this->listaItems);
	enemigo->asignarListaJugadores(&this->listaJugadores);
}

void ModeloNivel::agregarItem(ModeloItem* item) {
	this->listaItems.agregarItem(item);
	item->asignarListaJugadores(&this->listaJugadores);
	item->asignarListaEnemigos(&this->listaEnemigos);
	item->asignarListaGolems(&this->listaGolems);
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

void ModeloNivel::activarBomba(int id) {
	ModeloJugador* jugador = this->obtenerJugador(id);
	if (jugador != NULL)
		jugador->activarBomba();
}

void ModeloNivel::activarHechizoHielo(int id) {
	ModeloJugador* jugador = this->obtenerJugador(id);
	if (jugador != NULL)
		jugador->activarHechizoHielo();
}

void ModeloNivel::activarGolem(int id) {
	ModeloJugador* jugador = this->obtenerJugador(id);
	if (jugador != NULL)
		jugador->activarGolem();
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
		if ((enemigo->vida() > 0) && !enemigo->estaDesconectado()) {
			jugador->atacar(enemigo);
			return;
		}
	}
	
	// Si hice clic en un item valido
	ModeloItem* item = this->obtenerItem(posicion);
	if (item != NULL) {
		// Si el item esta disponible lo recogo
		if (item->disponible()) {
			jugador->recogerItem(item);
			return;
		}
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
	std::list<ModeloJugador*> listaGolems = this->listaGolems.obtenerJugadores();
	
	this->actualizarJugadores(&listaJugadores, &listaEnemigos, &listaGolems);
	this->actualizarEnemigos(&listaJugadores, &listaEnemigos, &listaGolems);
	this->actualizarGolems(&listaJugadores, &listaEnemigos, &listaGolems);
	this->actualizarItems();
	
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
