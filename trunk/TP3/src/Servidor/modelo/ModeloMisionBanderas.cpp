#include "ModeloMision.h"

using namespace std;

ModeloMisionBanderas::ModeloMisionBanderas() {
}

ModeloMisionBanderas::~ModeloMisionBanderas() {
}

void ModeloMisionBanderas::agregarJugador(ModeloJugador* jugador) {
	this->_marcador.insert(make_pair(jugador, 0));
}

void ModeloMisionBanderas::agregarEnemigo(ModeloJugador* enemigo) {
}

void ModeloMisionBanderas::agregarItem(ModeloItem* item) {
	if (item->modeloEntidad()->tipoEntidad() == TIPO_ITEM_BANDERA)
		this->_banderas.push_back(item);
}

void ModeloMisionBanderas::calcularGanador(ModeloJugador* jugador) {
	// Si ya tengo un ganador no calculo nada
	if (this->ganador() != NULL)
		return;

	// Obtengo el marcador correspondiente al jugador
	map<ModeloJugador*, int>::iterator marcador = this->_marcador.find(jugador);
	if (marcador == this->_marcador.end())
		return;

	// Recorro todas las banderas, y si encuentro alguna no disponible le sumo 1 al marcador del jugador y la quito de la lista
	list<ModeloItem*> banderas = this->_banderas;
	for (list<ModeloItem*>::iterator bandera = banderas.begin(); bandera != banderas.end(); bandera++) {
		if (!(*bandera)->disponible()) {
			marcador->second++;
			this->_banderas.remove(*bandera);
			break;
		}
	}

	// Si no hay mas banderas calculo al ganador
	if (this->_banderas.empty()) {
		map<ModeloJugador*, int>::iterator marcadorGanador = this->_marcador.begin();
		for (map<ModeloJugador*, int>::iterator marcador = this->_marcador.begin(); marcador != this->_marcador.end(); marcador++) {
			if (marcador->second > marcadorGanador->second)
				marcadorGanador = marcador;
		}
		this->asignarGanador(marcadorGanador->first);
	}
}
