#include "ModeloItem.h"

ModeloEspada::ModeloEspada(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad)
	: ModeloItem(alto, ancho, velocidad, posicion, altoNivel, anchoNivel, fps, proxyEntidad, id, nombreEntidad) {
}

ModeloEspada::~ModeloEspada() {

}

void ModeloEspada::aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos) {
	int nuevoDanio = ( jugador->danioAtaque() + (DANIO_ESPADA) );
	jugador->danioAtaque(nuevoDanio);
	return void();
}
