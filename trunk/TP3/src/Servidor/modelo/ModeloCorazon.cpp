#include "ModeloItem.h"

using namespace std;

ModeloCorazon::ModeloCorazon(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, string nombreEntidad)
	: ModeloItem(alto, ancho, velocidad, posicion, altoNivel, anchoNivel, fps, proxyEntidad, id, nombreEntidad) {
}

ModeloCorazon::~ModeloCorazon() {
}

void ModeloCorazon::aplicar(ModeloJugador* jugador) {
	jugador->recuperarVida(VIDA_RECUPERADA);
}
