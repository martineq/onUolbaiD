#include "ModeloItem.h"

using namespace std;

bool ModeloMapa::aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos, ListaJugadores* listaGolems) {
	jugador->setTieneMapa(true);
	return true;
}

ModeloMapa::ModeloMapa(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, string nombreEntidad)
	: ModeloItem(alto, ancho, velocidad, posicion, altoNivel, anchoNivel, fps, proxyEntidad, id, nombreEntidad, TIPO_ENTIDAD_ITEM) {
}

ModeloMapa::~ModeloMapa() {
}

bool ModeloMapa::inmediato() {
	return true;
}
