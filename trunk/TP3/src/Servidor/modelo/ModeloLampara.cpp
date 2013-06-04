#include "ModeloItem.h"

ModeloLampara::ModeloLampara(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad)
	: ModeloItem(alto, ancho, velocidad, posicion, altoNivel, anchoNivel, fps, proxyEntidad, id, nombreEntidad) {
}

ModeloLampara::~ModeloLampara() {
}

bool ModeloLampara::inmediato() {
	return true;
}

void ModeloLampara::aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos) {
	jugador->getEstadoNivel()->rangoVision(RANGO_VISION*2);
}
