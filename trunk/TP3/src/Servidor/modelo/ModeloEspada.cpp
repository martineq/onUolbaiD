#include "ModeloItem.h"

bool ModeloEspada::aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos) {
	int nuevoDanio = ( jugador->danioAtaque() + (DANIO_ESPADA) );
	jugador->danioAtaque(nuevoDanio);
	return true;
}

ModeloEspada::ModeloEspada(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad)
	: ModeloItem(alto, ancho, velocidad, posicion, altoNivel, anchoNivel, fps, proxyEntidad, id, nombreEntidad,TIPO_ENTIDAD_ITEM) {
}

ModeloEspada::~ModeloEspada() {

}

bool ModeloEspada::inmediato() {
	return true;
}
