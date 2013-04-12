#include "ModeloLoop.h"

using namespace std;

ModeloLoop::ModeloLoop() {
}

ModeloLoop::~ModeloLoop() {
}

Observador* ModeloLoop::obtenerObservadorEvento() {
	return &this->_modeloEvento;
}

bool ModeloLoop::loop(ModeloNivel& modeloNivel) {
	this->_modeloEvento.asignarModeloNivel(&modeloNivel);

	if (!this->_modeloEvento.getActualizado())
		return true;
	
	int mousePosX = this->_modeloEvento.getMousePosX();
	int mousePosY = this->_modeloEvento.getMousePosY();

	list<ModeloScroll*> listaScroll = modeloNivel.getListaScroll();
	
	for (std::list<ModeloScroll*>::iterator scroll = listaScroll.begin(); scroll != listaScroll.end(); scroll++) {
		//TODO: Verificar la lista de ids (TP2)
		(*scroll)->actualizar(mousePosX, mousePosY);
	}

	// Si se hizo clic con el boton derecho del mouse avisa al personaje que se mueva
	if (this->_modeloEvento.getMouseClickDerecho() == 1) {
		int x = 0, y = 0;
		//TODO: Aca necesito el scroll para calcular bien el deplazamiento en el nivel
		//	Como por ahora solo hay un scroll solo tomo el primero de la lista
		ModeloScroll* modeloScroll = *listaScroll.begin();
		Posicion::convertirPixelATile(modeloNivel.getAltoTiles(), mousePosX + modeloScroll->getX(), mousePosY + modeloScroll->getY(), x, y);
		modeloNivel.moverJugador(x, y, 0);
	}

	this->_modeloEvento.setActualizado(false);

	return true;
}
