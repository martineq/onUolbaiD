#include "ModeloNivel.h"

using namespace std;

ModeloNivel::ModeloNivel(){
	this->jugadores.clear();
	this->entidadesNivel.clear(); 
}

ModeloNivel::~ModeloNivel(void){
}

int ModeloNivel::agregarJugador (ModeloEntidad jugador) {
	this->jugadores.push_back(jugador);

	return 0;
}

int ModeloNivel::removerJugador (ModeloEntidad jugador) {
	this->jugadores.remove(jugador);

	return 0;
}

int ModeloNivel::agregarEntidadNivel (ModeloEntidad entidad) {
	this->entidadesNivel.push_back(entidad);

	return 0;
}

int ModeloNivel::removerEntidadNivel (ModeloEntidad entidad) {
	this->entidadesNivel.remove(entidad);

	return 0;
}


void ModeloNivel::limpiarNivel() {
	this->jugadores.clear();
	this->entidadesNivel.clear();
}