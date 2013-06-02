#include "ModeloEntidad.h"

using namespace std;

ListaEntidades::ListaEntidades() {
}

ListaEntidades::~ListaEntidades() {
	// Elimino todas las entidades distintas
	vector<ModeloEntidad*> entidadesEliminadas;
	for (multimap<std::pair<int, int>, ModeloEntidad*>::iterator entidad = this->_entidades.begin(); entidad != this->_entidades.end(); entidad++) {
		std::vector<ModeloEntidad*>::iterator entidadEliminada = find(entidadesEliminadas.begin(), entidadesEliminadas.end(), (*entidad).second);
		if (entidadEliminada == entidadesEliminadas.end()) {
			entidadesEliminadas.push_back((*entidad).second);
			delete (*entidad).second;
		}
	}
}

void ListaEntidades::agregarEntidad(ModeloEntidad* entidad) {
	this->_mutexEntidades.lockEscritura(__FILE__, __LINE__);
	// Agrego las posiciones ocupadas por la entidad
	for (int x = entidad->posicion().x; x < entidad->posicion().x + entidad->ancho(); x++) {
		for (int y = entidad->posicion().y; y < entidad->posicion().y + entidad->alto(); y++) {
			this->_entidades.insert(make_pair(make_pair(x, y), entidad));
		}
	}
	this->_mutexEntidades.unlock(__FILE__, __LINE__);
}

void ListaEntidades::agregarEntidadMovil(ModeloEntidad* entidadMovil) {
	this->_mutexEntidadesMoviles.lockEscritura(__FILE__, __LINE__);
	this->_entidadesMoviles.push_back(entidadMovil);	
	this->_mutexEntidadesMoviles.unlock(__FILE__, __LINE__);
}

ModeloEntidad* ListaEntidades::detectarColision(ModeloEntidad* entidad, Posicion posicion) {
	this->_mutexEntidadesMoviles.lockLectura(__FILE__, __LINE__);
	list<ModeloEntidad*> listaEntidadesMoviles = this->_entidadesMoviles;
	this->_mutexEntidadesMoviles.unlock(__FILE__, __LINE__);

	// Detecto colision con entidades moviles
	list<ModeloEntidad*>::iterator iterador = listaEntidadesMoviles.begin();
	while (iterador != listaEntidadesMoviles.end()) {
		if (((*iterador) != entidad) && (*iterador)->ocupaPosicion(posicion))
			return *iterador;
		iterador++;
	}

	// Detecto colision con entidades
	this->_mutexEntidades.lockLectura(__FILE__, __LINE__);
	multimap<std::pair<int, int>, ModeloEntidad*>::iterator entidadColisionada = this->_entidades.find(make_pair(posicion.x, posicion.y));
	multimap<std::pair<int, int>, ModeloEntidad*>::iterator fin = this->_entidades.end();
	this->_mutexEntidades.unlock(__FILE__, __LINE__);
	
	return (entidadColisionada == fin) ? NULL : (*entidadColisionada).second;
}

bool ListaEntidades::posicionOcupada(Posicion posicion) {
	this->_mutexEntidadesMoviles.lockLectura(__FILE__, __LINE__);
	list<ModeloEntidad*> listaEntidadesMoviles = this->_entidadesMoviles;
	this->_mutexEntidadesMoviles.unlock(__FILE__, __LINE__);

	// Chequeo con entidades moviles
	list<ModeloEntidad*>::iterator iterador = listaEntidadesMoviles.begin();
	while (iterador != listaEntidadesMoviles.end()) {
		if ((*iterador)->ocupaPosicion(posicion))
			return true;
		iterador++;
	}

	// Chequeo con entidades
	this->_mutexEntidades.lockLectura(__FILE__, __LINE__);
	multimap<std::pair<int, int>, ModeloEntidad*>::iterator entidadColisionada = this->_entidades.find(make_pair(posicion.x, posicion.y));
	multimap<std::pair<int, int>, ModeloEntidad*>::iterator fin = this->_entidades.end();
	this->_mutexEntidades.unlock(__FILE__, __LINE__);

	return (entidadColisionada != fin);
}

void ListaEntidades::removerEntidad(ModeloEntidad* entidad) {
	this->_mutexEntidades.lockEscritura(__FILE__, __LINE__);
	// Remuevo las posiciones ocupadas por la entidad
	for (int x = entidad->posicion().x; x < entidad->posicion().x + entidad->ancho(); x++) {
		for (int y = entidad->posicion().y; y < entidad->posicion().y + entidad->alto(); y++) {
			this->_entidades.erase(make_pair(entidad->posicion().x, entidad->posicion().y));
		}
	}
	this->_mutexEntidades.unlock(__FILE__, __LINE__);
}

void ListaEntidades::removerEntidadMovil(ModeloEntidad* entidadMovil) {
	this->_mutexEntidadesMoviles.lockEscritura(__FILE__, __LINE__);
	this->_entidadesMoviles.remove(entidadMovil);	
	this->_mutexEntidadesMoviles.unlock(__FILE__, __LINE__);
}
