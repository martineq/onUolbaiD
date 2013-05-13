#include "ModeloNivel.h"

ModeloEntidad* ModeloNivel::obtenerJugador(int id) {
	std::list<ModeloEntidad*> listaJugadores = this->getListaJugadores();
	for (std::list<ModeloEntidad*>::iterator itModeloEntidad = listaJugadores.begin(); itModeloEntidad != listaJugadores.end(); itModeloEntidad++){
		if ((*itModeloEntidad)->id() == id)
			return (*itModeloEntidad);
	}
	return NULL;
}

ModeloEntidad* ModeloNivel::obtenerEntidad(int id) {
	std::list<ModeloEntidad*> listaEntidades = this->getListaEntidades();
	for (std::list<ModeloEntidad*>::iterator itModeloEntidad = listaEntidades.begin(); itModeloEntidad != listaEntidades.end(); itModeloEntidad++){
		if ((*itModeloEntidad)->id() == id)
			return (*itModeloEntidad);
	}
	return NULL;
}

ModeloNivel::ModeloNivel() {
	this->jugadoresConectados = 0;
	this->listaJugadores.clear();
	this->listaEntidades.clear();
}

ModeloNivel::~ModeloNivel() {
	// Las listas de punteros ya son destruidos desde el Administrador
}

std::list<ModeloEntidad*> ModeloNivel::getListaJugadores() {
	this->mutexListaJugadores.lockLectura(__FILE__, __LINE__);
	std::list<ModeloEntidad*> listaJugadores = this->listaJugadores;
	this->mutexListaJugadores.unlock(__FILE__, __LINE__);
	return listaJugadores;
}

std::list<ModeloEntidad*> ModeloNivel::getListaEntidades() {
	this->mutexListaEntidades.lockLectura(__FILE__, __LINE__);
	std::list<ModeloEntidad*> listaEntidades = this->listaEntidades;
	this->mutexListaEntidades.unlock(__FILE__, __LINE__);
	return listaEntidades;
}

int ModeloNivel::getAnchoTiles() {
	return this->altoTiles;
}

int ModeloNivel::getAltoTiles() {
	return this->anchoTiles;
}

void ModeloNivel::agregarJugador(ModeloEntidad *jugador) {
	this->mutexListaJugadores.lockEscritura(__FILE__, __LINE__);
	this->listaJugadores.push_back(jugador);	
	jugador->notificar();
	this->mutexListaJugadores.unlock(__FILE__, __LINE__);
	jugador->asignarListaEntidades(&this->mutexListaEntidades, &this->listaEntidades);
	jugador->asignarListaJugadores(&this->mutexListaJugadores, &this->listaJugadores);
}

void ModeloNivel::agregarEntidad(ModeloEntidad *entidad) {
	this->mutexListaEntidades.lockEscritura(__FILE__, __LINE__);
	this->listaEntidades.push_back(entidad);	
	this->mutexListaEntidades.unlock(__FILE__, __LINE__);
}

void ModeloNivel::setAltoTiles(int alto){
	this->altoTiles = alto;
}

void ModeloNivel::setAnchoTiles(int ancho){
	this->anchoTiles = ancho;
}

void ModeloNivel::removerJugador(ModeloEntidad *jugador) {
	this->mutexListaJugadores.lockEscritura(__FILE__, __LINE__);
	this->listaJugadores.remove(jugador);
	this->mutexListaJugadores.unlock(__FILE__, __LINE__);
}

void ModeloNivel::removerEntidad(ModeloEntidad *entidad) {
	this->mutexListaEntidades.lockEscritura(__FILE__, __LINE__);
	this->listaEntidades.remove(entidad);
	this->mutexListaEntidades.unlock(__FILE__, __LINE__);
}

void ModeloNivel::jugadorMover(int mouseX, int mouseY, int id) {
	ModeloEntidad* jugador = this->obtenerJugador(id);
	if (jugador == NULL)
		return;
	Posicion posicion;
	Posicion::convertirPixelATile(this->getAltoTiles(), mouseX, mouseY, posicion.x, posicion.y);
	jugador->mover(posicion);
}

void ModeloNivel::jugadorAtacar(int id) {
	ModeloEntidad* jugador = this->obtenerJugador(id);
	if (jugador == NULL)
		return;
	jugador->atacar();
}

void ModeloNivel::jugadorDefender(int id) {
	ModeloEntidad* jugador = this->obtenerJugador(id);
	if (jugador == NULL)
		return;
	jugador->defender();
}

void ModeloNivel::congelarJugador(int idJugador){
	ModeloEntidad* jugador = this->obtenerJugador(idJugador);
	if (jugador == NULL){
		return void();
	}else{
		jugador->estaCongelado(true);
		this->decrementarJugadores();		// Se resta la cantidad de jugadores cuando alguno de ellos tiene error
	}
	return void();
}

bool ModeloNivel::actualizar() {
	std::list<ModeloEntidad*> listaJugadores = this->getListaJugadores();
	for (std::list<ModeloEntidad*>::iterator entidad = listaJugadores.begin(); entidad != listaJugadores.end(); entidad++)
		(*entidad)->cambiarEstado();
	return true;
}

void ModeloNivel::destruirListaJugadores(){
	// Destruyo los jugadores instanciados
	for (std::list<ModeloEntidad*>::iterator jugador = this->listaJugadores.begin(); jugador != this->listaJugadores.end(); jugador++){
		delete (*jugador);
	}
	return void();
}

void ModeloNivel::destruirListaEntidades(){
	// Destruyo las entidades instanciadas
	for (std::list<ModeloEntidad*>::iterator entidad = this->listaEntidades.begin(); entidad != this->listaEntidades.end(); entidad++){
		delete (*entidad);
	}
	return void();
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
	return void();
}

void ModeloNivel::decrementarJugadores(void){
	this->mutexJugadoresConectados.lockEscritura(__FILE__,__LINE__);
	this->jugadoresConectados = this->jugadoresConectados - 1;
	this->mutexJugadoresConectados.unlock(__FILE__,__LINE__);
	return void();
}

void ModeloNivel::destruirListas(){	
	this->destruirListaJugadores();
	this->destruirListaEntidades();
	return void();
}
