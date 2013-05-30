#include "ModeloItem.h"

using namespace std;

ModeloItem::ModeloItem(const ModeloItem &modeloItem) {
}

ModeloItem& ModeloItem::operator=(const ModeloItem &modeloItem) {
	return *this;
}

ModeloItem::ModeloItem(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, string nombreEntidad) {
	this->_modeloEntidad = new ModeloEntidad(alto, ancho, velocidad, posicion, altoNivel, anchoNivel, fps, proxyEntidad, id, nombreEntidad);
	this->_disponible = true;
}

ModeloItem::~ModeloItem() {
	delete this->_modeloEntidad;
}

bool ModeloItem::disponible() {
	return this->_disponible;
}

void ModeloItem::disponible(bool disponible) {
	this->_disponible = disponible;
}

ModeloEntidad* ModeloItem::modeloEntidad() {
	return this->_modeloEntidad;
}

ProxyModeloEntidad::stEntidad ModeloItem::stEntidad() {
	ProxyModeloEntidad::stEntidad estado = this->_modeloEntidad->stEntidad();
	return estado;
}
