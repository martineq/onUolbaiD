#include "ModeloBotella.h"

using namespace std;

ModeloBotella::ModeloBotella(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, string nombreEntidad)
	: ModeloItem(alto, ancho, velocidad, posicion, altoNivel, anchoNivel, fps, proxyEntidad, id, nombreEntidad) {
}

ModeloBotella::~ModeloBotella() {
}

void ModeloBotella::aplicar(ModeloJugador* jugador) {
	jugador->recuperarMagia(MAGIA_RECUPERADA);
}
