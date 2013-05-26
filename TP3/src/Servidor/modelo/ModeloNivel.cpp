#include "ModeloNivel.h"

using namespace std;

ModeloEntidad* ModeloNivel::obtenerEntidadMovil(int id) {
	std::list<ModeloEntidad*> listaEntidadesMovil = this->getListaEntidadesMoviles();
	for (std::list<ModeloEntidad*>::iterator itModeloEntidad = listaEntidadesMovil.begin(); itModeloEntidad != listaEntidadesMovil.end(); itModeloEntidad++){
		if ((*itModeloEntidad)->id() == id)
			return (*itModeloEntidad);
	}
	return NULL;
}

ModeloJugador* ModeloNivel::obtenerJugador(int id) {
	std::list<ModeloJugador*> listaJugadores = this->getListaJugadores();
	for (std::list<ModeloJugador*>::iterator itModeloEntidad = listaJugadores.begin(); itModeloEntidad != listaJugadores.end(); itModeloEntidad++){
		if ((*itModeloEntidad)->modeloEntidad()->id() == id)
			return (*itModeloEntidad);
	}
	return NULL;
}

ModeloNivel::ModeloNivel() {
	this->jugadoresConectados = 0;
}

ModeloNivel::~ModeloNivel() {
	// Las listas de punteros ya son destruidos desde el Administrador
}

std::list<ModeloJugador*> ModeloNivel::getListaJugadores() {
	this->mutexJugadores.lockLectura(__FILE__, __LINE__);
	std::list<ModeloJugador*> listaJugadores = this->jugadores;
	this->mutexJugadores.unlock(__FILE__, __LINE__);
	return listaJugadores;
}

std::list<ModeloEntidad*> ModeloNivel::getListaEntidadesMoviles() {
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
	jugador->modeloEntidad()->notificar();
	jugador->modeloEntidad()->asignarEntidades(&this->mutexEntidades, &this->entidades);
	jugador->modeloEntidad()->asignarJugadores(&this->mutexEntidadesMoviles, &this->entidadesMoviles);
}

void ModeloNivel::agregarEntidad(ModeloEntidad* entidad) {
	this->mutexEntidades.lockEscritura(__FILE__, __LINE__);
	// Agrego las posiciones ocupadas por la entidad
	for (int x = entidad->posicionActual().x; x < entidad->posicionActual().x + entidad->ancho(); x++)
		for (int y = entidad->posicionActual().y; y < entidad->posicionActual().y + entidad->alto(); y++)
			this->entidades.insert(make_pair(make_pair(x, y), entidad));
	this->mutexEntidades.unlock(__FILE__, __LINE__);
}

void ModeloNivel::setAltoTiles(int alto){
	this->altoTiles = alto;
}

void ModeloNivel::setAnchoTiles(int ancho){
	this->anchoTiles = ancho;
}

void ModeloNivel::removerJugador(ModeloJugador* jugador) {
	this->mutexJugadores.lockEscritura(__FILE__, __LINE__);
	this->jugadores.remove(jugador);
	this->mutexJugadores.unlock(__FILE__, __LINE__);
	this->mutexEntidadesMoviles.lockEscritura(__FILE__, __LINE__);
	this->entidadesMoviles.remove(jugador->modeloEntidad());	
	this->mutexEntidadesMoviles.unlock(__FILE__, __LINE__);
}

void ModeloNivel::removerEntidad(ModeloEntidad* entidad) {
	this->mutexEntidades.lockEscritura(__FILE__, __LINE__);
	this->entidades.erase(make_pair(entidad->posicionActual().x, entidad->posicionActual().y));
	this->mutexEntidades.unlock(__FILE__, __LINE__);
}

void ModeloNivel::jugadorMover(int mouseX, int mouseY, int id) {
	ModeloJugador* jugador = this->obtenerJugador(id);
	if (jugador == NULL)
		return;
	Posicion posicion;
	Posicion::convertirPixelATile(this->getAltoTiles(), mouseX, mouseY, posicion.x, posicion.y);
	jugador->modeloEntidad()->mover(posicion);
}

void ModeloNivel::jugadorAtacar(int id) {
	ModeloJugador* jugador = this->obtenerJugador(id);
	if (jugador == NULL)
		return;
	jugador->atacar();
}

void ModeloNivel::jugadorDefender(int id) {
	ModeloJugador* jugador = this->obtenerJugador(id);
	if (jugador == NULL)
		return;
	jugador->defender();
}

void ModeloNivel::congelarJugador(int id){
	ModeloJugador* jugador = this->obtenerJugador(id);
	if (jugador == NULL){
		return void();
	}else{
		jugador->modeloEntidad()->estaCongelado(true);
		this->decrementarJugadores();		// Se resta la cantidad de jugadores cuando alguno de ellos tiene error
	}
	return void();
}

bool ModeloNivel::actualizar() {
	std::list<ModeloEntidad*> listaJugadores = this->getListaEntidadesMoviles();
	for (std::list<ModeloEntidad*>::iterator entidad = listaJugadores.begin(); entidad != listaJugadores.end(); entidad++)
		(*entidad)->cambiarEstado();
	return true;
}

bool ModeloNivel::posicionOcupada(Posicion pos){
	std::list<ModeloEntidad*> listaJugadores = this->getListaEntidadesMoviles();

	for (std::list<ModeloEntidad*>::iterator jugador = listaJugadores.begin(); jugador != listaJugadores.end(); jugador++){
		Posicion posicionDelJugador = (*jugador)->posicionActual();
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

void ModeloNivel::destruirListaJugadores(){
	// Destruyo los jugadores instanciados
	for (std::list<ModeloJugador*>::iterator jugador = this->jugadores.begin(); jugador != this->jugadores.end(); jugador++){
		delete (*jugador);
	}
}

bool ModeloNivel::chequearConexion() {
	if (this->jugadores.empty())
		return false;
	return this->jugadores.front()->modeloEntidad()->chequearConexion();
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

void ModeloNivel::destruirListas(){	
	this->destruirListaJugadores();
	this->destruirListaEntidades();
}
