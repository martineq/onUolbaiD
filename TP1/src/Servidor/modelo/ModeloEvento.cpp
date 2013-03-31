#include "ModeloEvento.h"

void ModeloEvento::obtenerTile(int xp, int yp, int &xt, int &yt) {
	double desplazamientoX = 0, desplazamientoY = 0;
	
	//TODO: Arreglar esta funcion con lo que esta en ModeloEntidad
	// (necesito tener el alto y ancho del nivel para que calcule bien)
	xp -= ANCHO_TILE + (ANCHO_TILE / 2);
	desplazamientoX = (double)xp / ANCHO_TILE;
	desplazamientoY = (double)yp / ALTO_TILE;

	xt = floor(desplazamientoY + desplazamientoX);
	yt = floor(desplazamientoY - desplazamientoX);
}

ModeloEvento::ModeloEvento() {
	this->_modeloNivel = NULL;
}

ModeloEvento::~ModeloEvento() {
}

void ModeloEvento::actualizar(Observable* observable) {
	ControladorEvento* controladorEvento = (ControladorEvento*)observable;
	
	// Avisa al scroll que se movio el mouse
	//TODO: implementar
	//this->_modeloNivel->moverScroll(controladorEvento->getPosicionMouseX(), controladorEvento->getPosicionMouseY());

	// Si se hizo clic con el boton derecho del mouse avisa al personaje que se mueva
	if (controladorEvento->getClicMouseBotonDerecho()) {
		int x = 0, y = 0;
		this->obtenerTile(controladorEvento->getPosicionMouseX(), controladorEvento->getPosicionMouseY(), x, y);
		//TODO: implementar
		//this->_modeloNivel->moverPersonaje(x, y);
	}
}

void ModeloEvento::asignarModeloNivel(ModeloNivel* modeloNivel) {
	this->_modeloNivel = modeloNivel;
}
