#include "ModeloItem.h"

using namespace std;

ModeloItem::ModeloItem(const ModeloItem &modeloItem) {
}

ModeloItem& ModeloItem::operator=(const ModeloItem &modeloItem) {
	return *this;
}

ModeloItem::ModeloItem(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, string nombreEntidad) {
	this->_activo = false;
	this->_modeloEntidad = new ModeloEntidad(alto, ancho, velocidad, posicion, altoNivel, anchoNivel, fps, proxyEntidad, id, nombreEntidad);
	this->_jugador = NULL;
	this->_listaJugadores = NULL;
	this->_listaEnemigos = NULL;
}

ModeloItem::~ModeloItem() {
	delete this->_modeloEntidad;
}

bool ModeloItem::disponible() {
	return this->_jugador == NULL;
}

ModeloEntidad* ModeloItem::modeloEntidad() {
	return this->_modeloEntidad;
}

ProxyModeloEntidad::stEntidad ModeloItem::stEntidad() {
	ProxyModeloEntidad::stEntidad estado = this->_modeloEntidad->stEntidad();
	return estado;
}

void ModeloItem::activar() {
	this->_activo = (this->_jugador != NULL) && (this->_listaJugadores != NULL) && (this->_listaEnemigos != NULL);
}

void ModeloItem::asignarJugador(ModeloJugador* jugador) {
	this->_jugador = jugador;
	this->enviarEstado();
}

void ModeloItem::asignarListaJugadores(ListaJugadores* listaJugadores) {
	this->_listaJugadores = listaJugadores;
}

void ModeloItem::asignarListaEnemigos(ListaJugadores* listaEnemigos) {
	this->_listaEnemigos = listaEnemigos;
}

void ModeloItem::cambiarEstado() {
	// Si el item esta activo lo aplico y cambio el estado si se termino de aplicar lo desactivo
	if (this->_activo)
		this->_activo = !this->aplicar(this->_jugador, this->_listaJugadores, this->_listaEnemigos);
}

void ModeloItem::enviarEstado() {
	this->_modeloEntidad->enviarEstado(this->stEntidad());
}
