#include "ModeloItem.h"

bool ModeloEspada::aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos, ListaJugadores* listaGolems) {
	jugador->incrementarDanioAtaque(DANIO_ESPADA);
	return true;
}

ModeloEspada::ModeloEspada(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad)
	: ModeloItem(alto, ancho, velocidad, posicion, altoNivel, anchoNivel, fps, proxyEntidad, id, nombreEntidad, TIPO_ITEM_ESPADA) {
}

ModeloEspada::~ModeloEspada() {

}
