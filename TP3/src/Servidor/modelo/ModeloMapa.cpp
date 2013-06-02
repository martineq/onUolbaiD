#include "ModeloMapa.h"

using namespace std;

ModeloMapa::ModeloMapa(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, string nombreEntidad)
	: ModeloItem(alto, ancho, velocidad, posicion, altoNivel, anchoNivel, fps, proxyEntidad, id, nombreEntidad) {
}

ModeloMapa::~ModeloMapa() {
}

void ModeloMapa::aplicar(ModeloJugador* jugador) {
	jugador->setTieneMapa(true);
}
