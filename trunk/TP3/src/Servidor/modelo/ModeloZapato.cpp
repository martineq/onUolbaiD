#include "ModeloItem.h"

ModeloZapato::ModeloZapato(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad)
	: ModeloItem(alto, ancho, velocidad, posicion, altoNivel, anchoNivel, fps, proxyEntidad, id, nombreEntidad) {
}

ModeloZapato::~ModeloZapato() {
}

void ModeloZapato::aplicar(ModeloJugador* jugador) {
	int velocidadRegular = jugador->modeloEntidad()->velocidad();
	int velocidadZapato = velocidadRegular/2;						// Dividiendo aumenta la velocidad... ¿No?
	jugador->modeloEntidad()->velocidad(velocidadZapato);
	return void();
}
