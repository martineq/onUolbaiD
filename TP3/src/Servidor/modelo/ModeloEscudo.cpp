#include "ModeloItem.h"

ModeloEscudo::ModeloEscudo(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad)
	: ModeloItem(alto, ancho, velocidad, posicion, altoNivel, anchoNivel, fps, proxyEntidad, id, nombreEntidad) {
}

ModeloEscudo::~ModeloEscudo() {
}

bool ModeloEscudo::inmediato() {
	return true;
}

void ModeloEscudo::aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos) {
	jugador->recuperarEscudo(ESCUDO_RECUPERADO);
	return void();
}
