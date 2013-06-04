#include "ModeloItem.h"

using namespace std;

bool ModeloBotella::aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos) {
	jugador->recuperarMagia(MAGIA_RECUPERADA);
	return true;
}

ModeloBotella::ModeloBotella(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, string nombreEntidad)
	: ModeloItem(alto, ancho, velocidad, posicion, altoNivel, anchoNivel, fps, proxyEntidad, id, nombreEntidad) {
}

ModeloBotella::~ModeloBotella() {
}

bool ModeloBotella::inmediato() {
	return true;
}
