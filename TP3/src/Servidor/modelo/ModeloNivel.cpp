#include "ModeloNivel.h"

using namespace std;

ModeloJugador* ModeloNivel::obtenerJugador(int id) {
	std::list<ModeloJugador*> listaJugadores = this->getJugadores();
	for (std::list<ModeloJugador*>::iterator itModeloEntidad = listaJugadores.begin(); itModeloEntidad != listaJugadores.end(); itModeloEntidad++){
		if ((*itModeloEntidad)->modeloEntidad()->id() == id)
			return (*itModeloEntidad);
	}
	return NULL;
}

ModeloJugador* ModeloNivel::obtenerJugador(Posicion posicion) {
	std::list<ModeloJugador*> listaJugadores = this->getJugadores();
	for (std::list<ModeloJugador*>::iterator itModeloEntidad = listaJugadores.begin(); itModeloEntidad != listaJugadores.end(); itModeloEntidad++){
		if ((*itModeloEntidad)->modeloEntidad()->posicion() == posicion)
			return (*itModeloEntidad);
	}
	return NULL;
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
	this->mutexItems.lockLectura(__FILE__, __LINE__);
	multimap<std::pair<int, int>, ModeloItem*>::iterator item = this->items.find(make_pair(posicion.x, posicion.y));
	multimap<std::pair<int, int>, ModeloItem*>::iterator fin = this->items.end();
	this->mutexItems.unlock(__FILE__, __LINE__);
	return (item == fin) ? NULL : (*item).second;
}

ModeloNivel::ModeloNivel() {
	this->jugadoresConectados = 0;
}

ModeloNivel::~ModeloNivel() {
	// Las listas de punteros ya son destruidos desde el Administrador
}

std::list<ModeloJugador*> ModeloNivel::getJugadores() {
	this->mutexJugadores.lockLectura(__FILE__, __LINE__);
	std::list<ModeloJugador*> listaJugadores = this->jugadores;
	this->mutexJugadores.unlock(__FILE__, __LINE__);
	return listaJugadores;
}

std::list<ModeloJugador*> ModeloNivel::getEnemigos() {
	this->mutexEnemigos.lockLectura(__FILE__, __LINE__);
	std::list<ModeloJugador*> listaEnemigos = this->enemigos;
	this->mutexEnemigos.unlock(__FILE__, __LINE__);
	return listaEnemigos;
}

std::list<ModeloEntidad*> ModeloNivel::getEntidadesMoviles() {
	this->mutexEntidadesMoviles.lockLectura(__FILE__, __LINE__);
	std::list<ModeloEntidad*> listaEntidadesMoviles = this->entidadesMoviles;
	this->mutexEntidadesMoviles.unlock(__FILE__, __LINE__);
	return listaEntidadesMoviles;
}

int ModeloNivel::getAnchoTiles() {
	return this->altoTiles;
}

int ModeloNivel::getAltoTiles() {
	return this->anchoTiles;
}

void ModeloNivel::agregarJugador(ModeloJugador* jugador) {
	this->mutexJugadores.lockEscritura(__FILE__, __LINE__);
	this->jugadores.push_back(jugador);	
	this->mutexJugadores.unlock(__FILE__, __LINE__);
	this->mutexEntidadesMoviles.lockEscritura(__FILE__, __LINE__);
	this->entidadesMoviles.push_back(jugador->modeloEntidad());	
	this->mutexEntidadesMoviles.unlock(__FILE__, __LINE__);
	jugador->enviarEstado();
	jugador->asignarEntidades(&this->mutexEntidades, &this->entidades);
	jugador->asignarEntidadesMoviles(&this->mutexEntidadesMoviles, &this->entidadesMoviles);
}

void ModeloNivel::agregarEnemigo(ModeloJugador* enemigo) {
	this->mutexEnemigos.lockEscritura(__FILE__, __LINE__);
	this->enemigos.push_back(enemigo);	
	this->mutexEnemigos.unlock(__FILE__, __LINE__);
	this->mutexEntidadesMoviles.lockEscritura(__FILE__, __LINE__);
	this->entidadesMoviles.push_back(enemigo->modeloEntidad());	
	this->mutexEntidadesMoviles.unlock(__FILE__, __LINE__);
	enemigo->asignarEntidades(&this->mutexEntidades, &this->entidades);
	enemigo->asignarEntidadesMoviles(&this->mutexEntidadesMoviles, &this->entidadesMoviles);
}

void ModeloNivel::agregarItem(ModeloItem* item) {
	this->mutexItems.lockEscritura(__FILE__, __LINE__);
	this->items.insert(make_pair(make_pair(item->modeloEntidad()->posicion().x, item->modeloEntidad()->posicion().y), item));
	this->mutexItems.unlock(__FILE__, __LINE__);
	this->agregarEntidad(item->modeloEntidad());
}

void ModeloNivel::agregarEntidad(ModeloEntidad* entidad) {
	this->mutexEntidades.lockEscritura(__FILE__, __LINE__);
	// Agrego las posiciones ocupadas por la entidad
	for (int x = entidad->posicion().x; x < entidad->posicion().x + entidad->ancho(); x++)
		for (int y = entidad->posicion().y; y < entidad->posicion().y + entidad->alto(); y++)
			this->entidades.insert(make_pair(make_pair(x, y), entidad));
	this->mutexEntidades.unlock(__FILE__, __LINE__);
}

void ModeloNivel::setAltoTiles(int alto){
	this->altoTiles = alto;
}

void ModeloNivel::setAnchoTiles(int ancho){
	this->anchoTiles = ancho;
}

void ModeloNivel::removerEntidad(ModeloEntidad* entidad) {
	this->mutexEntidades.lockEscritura(__FILE__, __LINE__);
	this->entidades.erase(make_pair(entidad->posicion().x, entidad->posicion().y));
	this->mutexEntidades.unlock(__FILE__, __LINE__);
}

void ModeloNivel::removerEntidadMovil(ModeloEntidad* entidad) {
	this->mutexEntidadesMoviles.lockEscritura(__FILE__, __LINE__);
	this->entidadesMoviles.remove(entidad);	
	this->mutexEntidadesMoviles.unlock(__FILE__, __LINE__);
}

void ModeloNivel::ejecutarAccionJugador(int mouseX, int mouseY, int id) {
	ModeloJugador* jugador = this->obtenerJugador(id);
	
	// Si no encontre jugador o esta congelado salgo
	if ((jugador == NULL) || (jugador->estaCongelado()))
		return;
	
	Posicion posicion;
	Posicion::convertirPixelATile(this->getAltoTiles(), mouseX, mouseY, posicion.x, posicion.y);
	
	ModeloJugador* enemigo = this->obtenerJugador(posicion);
	if (enemigo == NULL)
		enemigo = this->obtenerEnemigo(posicion);
	ModeloItem* item = this->obtenerItem(posicion);
	
	// Si hice clic en un enemigo valido
	if ((enemigo != NULL) && (enemigo != jugador)) {
		// Si el enemigo esta vivo lo ataco; sino, si es autonomo, lo quito de la lista de entidades moviles para que no se colisione mas con el
		if (enemigo->vida() > 0)
			jugador->atacar(enemigo);
		else if (enemigo->autonomo()) {
			this->removerEntidadMovil(enemigo->modeloEntidad());
			jugador->mover(posicion);
		}
	}
	// Si hice click en un item
	else if (item != NULL) {
		// Si el item esta disponible lo recogo, sino lo quito de la lista de entidades para que no se colisione mas con el
		if (item->disponible())
			jugador->recogerItem(item);
		else {
			this->removerEntidad(item->modeloEntidad());
			jugador->mover(posicion);
		}
	}
	else 
		jugador->mover(posicion);
}

void ModeloNivel::congelarJugador(int id){
	ModeloJugador* jugador = this->obtenerJugador(id);
	if (jugador == NULL){
		return void();
	}else{
		if( jugador->estaCongelado() == false ){
			jugador->estaCongelado(true);
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
		if ((*enemigo)->estaCongelado() || ((*enemigo)->vida() == 0))
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

bool ModeloNivel::posicionOcupada(Posicion pos){
	std::list<ModeloEntidad*> listaJugadores = this->getEntidadesMoviles();

	for (std::list<ModeloEntidad*>::iterator jugador = listaJugadores.begin(); jugador != listaJugadores.end(); jugador++){
		Posicion posicionDelJugador = (*jugador)->posicion();
		int x1 = posicionDelJugador.x;
		int x2 = posicionDelJugador.x + (*jugador)->ancho() - 1;
		int y1 = posicionDelJugador.y;
		int y2 = posicionDelJugador.y + (*jugador)->alto() - 1;

		if ( (pos.x >= x1) && (pos.x <= x2) && (pos.y >= y1) && (pos.y <= y2) ) 
			return true;		
	}

	multimap<std::pair<int, int>, ModeloEntidad*>::iterator entidad = this->entidades.find(make_pair(pos.x, pos.y));
	return entidad != this->entidades.end();
}

bool ModeloNivel::chequearConexion() {
	if (this->jugadores.empty())
		return false;
	return this->jugadores.front()->chequearConexion();
}

void ModeloNivel::destruirListaJugadores(){
	// Destruyo los jugadores instanciados
	for (std::list<ModeloJugador*>::iterator jugador = this->jugadores.begin(); jugador != this->jugadores.end(); jugador++) {
		this->removerEntidadMovil((*jugador)->modeloEntidad());
		delete (*jugador);
	}
}

void ModeloNivel::destruirListaEnemigos(){
	// Destruyo los enemigos instanciados
	for (std::list<ModeloJugador*>::iterator enemigo = this->enemigos.begin(); enemigo != this->enemigos.end(); enemigo++) {
		this->removerEntidadMovil((*enemigo)->modeloEntidad());
		delete (*enemigo);
	}
}

void ModeloNivel::destruirListaItems() {	
	// Destruyo todos los items instaciados
	for (multimap<std::pair<int, int>, ModeloItem*>::iterator item = this->items.begin(); item != this->items.end(); item++) {
		this->removerEntidad((*item).second->modeloEntidad());
		delete (*item).second;
	}
}

void ModeloNivel::destruirListaEntidades() {
	vector<ModeloEntidad*> entidadesEliminadas;
	
	// Elimino todas las entidades distintas
	for (multimap<std::pair<int, int>, ModeloEntidad*>::iterator entidad = this->entidades.begin(); entidad != this->entidades.end(); entidad++) {
		std::vector<ModeloEntidad*>::iterator entidadEliminada = find(entidadesEliminadas.begin(), entidadesEliminadas.end(), (*entidad).second);
		if (entidadEliminada == entidadesEliminadas.end()) {
			entidadesEliminadas.push_back((*entidad).second);
			delete (*entidad).second;
		}
	}
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
	this->destruirListaJugadores();
	this->destruirListaEnemigos();
	this->destruirListaItems();
	this->destruirListaEntidades();
}