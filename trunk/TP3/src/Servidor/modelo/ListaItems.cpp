#include "ModeloItem.h"

using namespace std;

ListaItems::ListaItems() {
}

ListaItems::~ListaItems() {
}

void ListaItems::agregarItem(ModeloItem* item) {
	this->_mutex.lockEscritura(__FILE__, __LINE__);
	this->_items.insert(make_pair(make_pair(item->modeloEntidad()->posicion().x, item->modeloEntidad()->posicion().y), item));
	this->_mutex.unlock(__FILE__, __LINE__);
	this->_listaEntidades->agregarEntidad(item->modeloEntidad());
	item->enviarEstado();
}

void ListaItems::asignarListaEntidades(ListaEntidades* listaEntidades) {
	this->_listaEntidades = listaEntidades;
}

void ListaItems::destruirItems() {
	for (multimap<std::pair<int, int>, ModeloItem*>::iterator item = this->_items.begin(); item != this->_items.end(); item++) {
		this->_listaEntidades->removerEntidad((*item).second->modeloEntidad());
		delete (*item).second;
	}
}

ModeloItem* ListaItems::obtenerItem(Posicion posicion) {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	pair<multimap<pair<int, int>, ModeloItem*>::iterator, multimap<pair<int, int>, ModeloItem*>::iterator> resultado = this->_items.equal_range(make_pair(posicion.x, posicion.y));
	this->_mutex.unlock(__FILE__, __LINE__);
	for (multimap<pair<int, int>, ModeloItem*>::iterator item = resultado.first; item != resultado.second; item++) {
		if ((*item).second->disponible())
			return (*item).second;
	}
	return (resultado.first == resultado.second) ? NULL : (*resultado.first).second;
}

std::multimap<std::pair<int, int>, ModeloItem*> ListaItems::obtenerItems() {
	return this->_items;
}

void ListaItems::removerItem(ModeloItem* item) {
	this->_listaEntidades->removerEntidad(item->modeloEntidad());
}
