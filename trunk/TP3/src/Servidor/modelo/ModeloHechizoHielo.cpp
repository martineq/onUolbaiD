#include "ModeloItem.h"

using namespace std;

bool ModeloHechizoHielo::aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos, ListaJugadores* listaGolems) {
	if (jugador->magia() < MAGIA_CONSUMIDA_HECHIZO_HIELO)
		return true;
	
	int xDesde = jugador->modeloEntidad()->posicion().x - RANGO_HECHIZO_HIELO;
	int xHasta = jugador->modeloEntidad()->posicion().x + RANGO_HECHIZO_HIELO;
	int yDesde = jugador->modeloEntidad()->posicion().y - RANGO_HECHIZO_HIELO;
	int yHasta = jugador->modeloEntidad()->posicion().y + RANGO_HECHIZO_HIELO;

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
			if ((victima != NULL) && (victima != jugador)){
				ProxyModeloEntidad::stEntidad entidad = this->modeloEntidad()->stEntidad();
				entidad.atacando = true;
				this->modeloEntidad()->enviarEstado(entidad);
				victima->estaCongelado(true);
			}
		}
	}
	
	jugador->consumirMagia(MAGIA_CONSUMIDA_HECHIZO_HIELO);

	return true;
}

ModeloHechizoHielo::ModeloHechizoHielo(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, string nombreEntidad)
	: ModeloItem(alto, ancho, velocidad, posicion, altoNivel, anchoNivel, fps, proxyEntidad, id, nombreEntidad, TIPO_ITEM_HECHIZO_HIELO) {
	this->_altoNivel = altoNivel;
	this->_anchoNivel = anchoNivel;
}

ModeloHechizoHielo::~ModeloHechizoHielo() {
}
