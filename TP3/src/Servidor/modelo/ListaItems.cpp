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

//TODO: Arreglar esto para que si hay varios items en la posicion agarre el primero que encuentre diponible
ModeloItem* ListaItems::obtenerItem(Posicion posicion) {
	this->_mutex.lockLectura(__FILE__, __LINE__);
	multimap<pair<int, int>, ModeloItem*>::iterator item = this->_items.find(make_pair(posicion.x, posicion.y));
	multimap<pair<int, int>, ModeloItem*>::iterator fin = this->_items.end();
	this->_mutex.unlock(__FILE__, __LINE__);
	return (item == fin) ? NULL : (*item).second;
}

std::multimap<std::pair<int, int>, ModeloItem*> ListaItems::obtenerItems() {
	return this->_items;
}

void ListaItems::removerItem(ModeloItem* item) {
	this->_listaEntidades->removerEntidad(item->modeloEntidad());
}
