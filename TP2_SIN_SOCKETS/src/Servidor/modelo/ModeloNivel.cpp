#include "ModeloNivel.h"

ModeloEntidad* ModeloNivel::obtenerJugador(int id) {
	//TODO: Descomentar al implementar ids
	/*for (list<ModeloEntidad*>::iterator modeloEntidad = this->listaJugadores.begin(); modeloEntidad != this->listaJugadores.end(); modeloEntidad++)
	{
		if ((*modeloEntidad)->id() == id)
			return *modeloEntidad;
	}
	return NULL;*/
	return *this->listaJugadores.begin();
}

ModeloScroll* ModeloNivel::obtenerScroll(int id) {
	//TODO: Descomentar al implementar ids
	/*for (list<ModeloScroll*>::iterator modeloScroll = this->listaScroll.begin(); modeloScroll != this->listaScroll.end(); modeloScroll++)
	{
		if ((*modeloScroll)->id() == id)
			return *modeloScroll;
	}
	return NULL;*/
	return *this->listaScroll.begin();
}

ModeloEntidad* ModeloNivel::obtenerEntidad(int id) {
	//TODO: Descomentar al implementar ids
	/*for (list<ModeloEntidad*>::iterator modeloEntidad = this->listaEntidades.begin(); modeloEntidad != this->listaEntidades.end(); modeloEntidad++)
	{
		if ((*modeloEntidad)->id() == id)
			return *modeloEntidad;
	}
	return NULL;*/
	return *this->listaEntidades.begin();
}

ModeloNivel::ModeloNivel() {
	this->listaJugadores.clear();
	this->listaEntidades.clear();
	this->listaScroll.clear();
}

ModeloNivel::~ModeloNivel() {
	// Las listas de punteros ya son destruidos desde el Administrador
}

int ModeloNivel::getAnchoTiles() {
	return this->altoTiles;
}

int ModeloNivel::getAltoTiles() {
	return this->anchoTiles;
}

void ModeloNivel::agregarObservadoresJugador(std::list<Observador*> listaObservadoresJugador) {
	// Itero sobre los observadores
	for (std::list<Observador*>::iterator observador = listaObservadoresJugador.begin(); observador != listaObservadoresJugador.end(); observador++) {
		ModeloEntidad* jugador = this->obtenerJugador(dynamic_cast<Identificable*>(*observador)->id());
		if (jugador != NULL)
			jugador->agregarObservador(*observador);
	}
}

void ModeloNivel::agregarObservadoresEntidad(std::list<Observador*> listaObservadoresEntidad) {
	// Itero sobre los observadores
	for (std::list<Observador*>::iterator observador = listaObservadoresEntidad.begin(); observador != listaObservadoresEntidad.end(); observador++) {
		ModeloEntidad* entidad = this->obtenerEntidad(dynamic_cast<Identificable*>(*observador)->id());
		if (entidad != NULL)
			entidad->agregarObservador(*observador);
	}
}

void ModeloNivel::agregarObservadoresScroll(std::list<Observador*> listaObservadoresScroll){
	// Itero sobre los observadores
	for (std::list<Observador*>::iterator observador = listaObservadoresScroll.begin(); observador != listaObservadoresScroll.end(); observador++) {
		ModeloScroll* scroll = this->obtenerScroll(dynamic_cast<Identificable*>(*observador)->id());
		if (scroll != NULL)
			scroll->agregarObservador(*observador);
			scroll->notificarPosicionInicial();
	}
}

void ModeloNivel::agregarJugador(ModeloEntidad *jugador) {
	this->listaJugadores.push_back(jugador);
	jugador->asignarListaJugadores(&this->listaJugadores);
	jugador->asignarListaEntidades(&this->listaEntidades);
}

void ModeloNivel::agregarEntidad(ModeloEntidad *entidad) {
	this->listaEntidades.push_back(entidad);
}

void ModeloNivel::agregarScroll(ModeloScroll *scroll) {
	this->listaScroll.push_back(scroll);
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

void ModeloNivel::removerScroll(ModeloScroll *scroll) {
	this->listaScroll.remove(scroll);
}

void ModeloNivel::moverScroll(int mouseX, int mouseY, int id) {
	ModeloScroll* scroll = this->obtenerScroll(id);
	if (scroll != NULL)
		scroll->actualizar(mouseX, mouseY);
}

void ModeloNivel::detenerScroll(int id) {
	ModeloScroll* scroll = this->obtenerScroll(id);
	if (scroll != NULL)
		scroll->detener();
}

void ModeloNivel::moverJugador(int mouseX, int mouseY, int id) {
	ModeloEntidad* jugador = this->obtenerJugador(id);
	if (jugador == NULL)
		return;
	ModeloScroll* scroll = this->obtenerScroll(id);
	if (scroll != NULL) {
		mouseX += scroll->getX();
		mouseY += scroll->getY();
	}
	Posicion posicion;
	Posicion::convertirPixelATile(this->getAltoTiles(), mouseX, mouseY, posicion.x, posicion.y);
	jugador->mover(posicion);
}

bool ModeloNivel::actualizar(int id) {
	ModeloScroll* scroll = this->obtenerScroll(id);
	if (scroll != NULL)
		scroll->cambiarEstado();
	ModeloEntidad* jugador = this->obtenerJugador(id);
	if (jugador != NULL)
		jugador->cambiarEstado();
	return true;
}

void ModeloNivel::destruirListaJugadores(){
	// Destruyo los jugadores instanciados
	for (std::list<ModeloEntidad*>::iterator jugador = this->listaJugadores.begin(); jugador != this->listaJugadores.end(); jugador++)
		delete (*jugador);
}

void ModeloNivel::destruirListaEntidades(){
	// Destruyo las entidades instanciadas
	for (std::list<ModeloEntidad*>::iterator entidad = this->listaEntidades.begin(); entidad != this->listaEntidades.end(); entidad++)
		delete (*entidad);
}

void ModeloNivel::destruirListaScroll(){
	// Destruyo los scrolls instanciados
	for (std::list<ModeloScroll*>::iterator scroll = this->listaScroll.begin(); scroll != this->listaScroll.end(); scroll++)
		delete (*scroll);
}

void ModeloNivel::destruirListas(){	
	this->destruirListaJugadores();
	this->destruirListaEntidades();
	this->destruirListaScroll();
}

void ModeloNivel::jugadorAtacar() {
	ModeloEntidad* jugador = this->obtenerJugador(1);
	if (jugador != NULL)
		jugador->atacar();
}

void ModeloNivel::jugadorDefender() {
	ModeloEntidad* jugador = this->obtenerJugador(1);
	if (jugador != NULL)
		jugador->defender();
}
