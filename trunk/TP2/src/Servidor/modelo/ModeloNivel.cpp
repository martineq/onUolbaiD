#include "ModeloNivel.h"

ModeloEntidad* ModeloNivel::obtenerJugador(int id){
	for (std::list<ModeloEntidad*>::iterator itModeloEntidad = this->listaJugadores.begin(); itModeloEntidad != this->listaJugadores.end(); itModeloEntidad++){
		if ((*itModeloEntidad)->id() == id)
			return (*itModeloEntidad);
	}
	return NULL;
}

ModeloEntidad* ModeloNivel::obtenerEntidad(int id){
	for (std::list<ModeloEntidad*>::iterator itModeloEntidad = this->listaEntidades.begin(); itModeloEntidad != this->listaEntidades.end(); itModeloEntidad++){
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
	return this->listaJugadores;
}

std::list<ModeloEntidad*> ModeloNivel::getListaEntidades() {
	return this->listaEntidades;
}

int ModeloNivel::getAnchoTiles() {
	return this->altoTiles;
}

int ModeloNivel::getAltoTiles() {
	return this->anchoTiles;
}

void ModeloNivel::agregarJugador(ModeloEntidad *jugador) {
	this->listaJugadores.push_back(jugador);
}

void ModeloNivel::agregarEntidad(ModeloEntidad *entidad) {
	this->listaEntidades.push_back(entidad);
}

void ModeloNivel::setAltoTiles(int alto){
	this->altoTiles = alto;
}

void ModeloNivel::setAnchoTiles(int ancho){
	this->anchoTiles = ancho;
}

void ModeloNivel::removerJugador(ModeloEntidad *jugador) {
	this->listaJugadores.remove(jugador);
}

void ModeloNivel::removerEntidad(ModeloEntidad *entidad) {
	this->listaEntidades.remove(entidad);
}

void ModeloNivel::moverJugador(int mouseX, int mouseY, int id) {
	ModeloEntidad* jugador = this->obtenerJugador(id);
	if (jugador == NULL)
		return;
	Posicion posicion;
	Posicion::convertirPixelATile(this->getAltoTiles(), mouseX, mouseY, posicion.x, posicion.y);
	jugador->mover(posicion);
}

bool ModeloNivel::actualizar(int id) {
	ModeloEntidad* jugador = this->obtenerJugador(id);
	if (jugador != NULL)
		jugador->cambiarEstado();
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
