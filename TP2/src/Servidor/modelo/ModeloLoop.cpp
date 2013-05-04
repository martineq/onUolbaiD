#include "ModeloLoop.h"

using namespace std;

ModeloLoop::ModeloLoop() {
}

ModeloLoop::~ModeloLoop(){

}

bool ModeloLoop::loop(ModeloNivel& modeloNivel){
	
	// Recorro varios eventos en un solo loop. Está asegurado que no habrá 2 eventos del mismo ID.
	while( this->_modeloEvento.getActualizado() ){
		int idJugador = this->_modeloEvento.getIdJugador();
		int mousePosX = this->_modeloEvento.getMousePosX();
		int mousePosY = this->_modeloEvento.getMousePosY();

		//TODO: Verificar la lista de ids (TP2)
		if (this->_modeloEvento.getMouseClickIzquierdo()){
			modeloNivel.moverJugador(mousePosX,mousePosY,idJugador);
		}

		modeloNivel.actualizar(idJugador); // TODO: Ver si esta línea va acá o si va afuera del while y se debe actualizar a todos los jugadores existentes
	}

	return true;
}
