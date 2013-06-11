#include "ModeloItem.h"

bool ModeloZapato::aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos, ListaJugadores* listaGolems) {
	jugador->incrementarVelocidad(2);
	return true;
}

ModeloZapato::ModeloZapato(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad)
	: ModeloItem(alto, ancho, velocidad, posicion, altoNivel, anchoNivel, fps, proxyEntidad, id, nombreEntidad, TIPO_ITEM_ZAPATO) {
}

ModeloZapato::~ModeloZapato() {
}
