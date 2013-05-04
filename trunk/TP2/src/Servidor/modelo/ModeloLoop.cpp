#include "ModeloLoop.h"

ModeloLoop::ModeloLoop(){

}

ModeloLoop::~ModeloLoop(){

}

bool ModeloLoop::loop(ModeloNivel& modeloNivel,int* jugadoresConectados,Mutex* mutexJugadoresConectados){
	
	this->procesarJugadoresEliminados(modeloNivel,jugadoresConectados,mutexJugadoresConectados);

	// Recorro varios eventos en un solo loop. Está asegurado que no habrá 2 eventos del mismo ID.
	while( this->_modeloEvento.getActualizado() ){
		int idJugador = this->_modeloEvento.getIdJugador();
		int mousePosX = this->_modeloEvento.getMousePosX();
		int mousePosY = this->_modeloEvento.getMousePosY();

		//TODO: Verificar la lista de ids (TP2)
		if (this->_modeloEvento.getMouseClickIzquierdo()){
			modeloNivel.moverJugador(mousePosX,mousePosY,idJugador);
		}
		
		this->_modeloEvento.cargarProximoEvento();  // Con esto descarto el evento que acabo de leer y carga el próximo

		modeloNivel.actualizar(idJugador); // TODO: Ver si esta línea va acá o si va afuera del while y se debe actualizar a todos los jugadores existentes
	}

	return true;
}

void ModeloLoop::setProxyControladorEvento(ProxyControladorEvento* pProxyEvento){
	this->_modeloEvento.setProxyControladorEvento(pProxyEvento);
	return void();
}

void ModeloLoop::procesarJugadoresEliminados(ModeloNivel& modeloNivel,int* jugadoresConectados,Mutex* mutexJugadoresConectados){
	// TODO: Implementar. La idea es tomar todos los jugadores que tienen error de socket y borrarlos del modelo nivel, restando la cantidad de jugadores conectados
	return void();
}