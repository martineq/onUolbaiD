#include "ModeloItem.h"

using namespace std;

bool ModeloBomba::aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos, ListaJugadores* listaGolems) {
	if (this->_instanteActivacion == 0) {
		this->_instanteActivacion = GetTickCount();
		return false;
	}

	if (DELAY_BOMBA > GetTickCount() - this->_instanteActivacion)
		return false;

	int xDesde = this->modeloEntidad()->posicion().x - RANGO_BOMBA;
	int xHasta = this->modeloEntidad()->posicion().x + RANGO_BOMBA;
	int yDesde = this->modeloEntidad()->posicion().y - RANGO_BOMBA;
	int yHasta = this->modeloEntidad()->posicion().y + RANGO_BOMBA;

	if (xDesde < 0)
		xDesde = 0;
	if (xHasta >= this->_anchoNivel)
		xHasta = this->_anchoNivel - 1;
	if (yDesde < 0)
		yDesde = 0;
	if (yHasta >= this->_altoNivel)
		yHasta = this->_altoNivel - 1;

	for (int x = xDesde; x <= xHasta; x++) {
		for (int y = yDesde; y <= yHasta; y++) {
			Posicion posicion;
			posicion.x = x;
			posicion.y = y;
			ModeloJugador* victima = listaJugadores->obtenerJugador(posicion);
			if (victima == NULL)
				victima = listaEnemigos->obtenerJugador(posicion);
			if (victima != NULL)
				victima->consumirVida(DANIO_BOMBA);
		}
	}

	//Para cuando agarra la bomba
	jugador->setCantidadBombas(true);

	return true;
}

ModeloBomba::ModeloBomba(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, string nombreEntidad)
	: ModeloItem(alto, ancho, velocidad, posicion, altoNivel, anchoNivel, fps, proxyEntidad, id, nombreEntidad, TIPO_ENTIDAD_ITEM) {
	this->_altoNivel = altoNivel;
	this->_anchoNivel = anchoNivel;
	this->_instanteActivacion = 0;
}

ModeloBomba::~ModeloBomba() {
}

bool ModeloBomba::inmediato() {
	return false;
}


















