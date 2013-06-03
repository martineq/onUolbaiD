#include "ModeloItem.h"

ModeloLampara::ModeloLampara(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad)
	: ModeloItem(alto, ancho, velocidad, posicion, altoNivel, anchoNivel, fps, proxyEntidad, id, nombreEntidad) {}

ModeloLampara::~ModeloLampara() {}

void ModeloLampara::aplicar(ModeloJugador* jugador) {
	jugador->getEstadoNivel()->rangoVision(RANGO_VISION*2);
}
