#pragma once

#include "ModeloMision.h"

ModeloMisionCarnicero::ModeloMisionCarnicero() {
	this->_enemigo = NULL;
}

ModeloMisionCarnicero::~ModeloMisionCarnicero() {
}

void ModeloMisionCarnicero::agregarJugador(ModeloJugador* jugador){
	//Nada
}

void ModeloMisionCarnicero::agregarEnemigo(ModeloJugador* enemigo){
	if (enemigo->modeloEntidad()->tipoEntidad() == TIPO_ENTIDAD_CARNICERO)
		this->_enemigo = enemigo;
}

void ModeloMisionCarnicero::agregarItem(ModeloItem* item){
	//Nada
}

void ModeloMisionCarnicero::calcularGanador(ModeloJugador* jugador){
	if (this->_enemigo == NULL) {
		this->asignarGanador(jugador);
		return;
	}
	// Si ya tengo un ganador no calculo nada
	if (this->ganador() != NULL)
		return;
	if (this->_enemigo->vida() == 0) 
		this->asignarGanador(jugador);
}