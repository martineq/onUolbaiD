#include "ModeloLoop.h"

ModeloLoop::ModeloLoop(){

}

ModeloLoop::~ModeloLoop(){

}

bool ModeloLoop::loop(ModeloNivel& modeloNivel){

	// Recorro varios eventos en un solo loop. Está asegurado que no habrá 2 eventos del mismo ID.
	while( this->_modeloEvento.getActualizado() ){

		// Obtengo el id para ubicarlo en el nivel
		int idJugador = this->_modeloEvento.getIdJugador();

		// Acá lo primero preguntor es si el cliente finalizo su juego o si tuvo error de sockets
		if( this->_modeloEvento.errorEnSocket() == true || this->_modeloEvento.finalizoElJuego() == true ){

			// En caso de finalización del juego o error de sockets se congela al jugador
			modeloNivel.congelarJugador(idJugador);

		}else{

			// En el caso de no haber errores y no haber terminado el juego se obtienen los datos para acutalizar
			int mousePosX = this->_modeloEvento.getMousePosX();
			int mousePosY = this->_modeloEvento.getMousePosY();
			// Tambien hay:
			//this->_modeloEvento.getKeyA();
			//this->_modeloEvento.getKeyS();
			//this->_modeloEvento.getMouseDentroPantalla(); // <<< Confirmar si no hace falta, así lo borro

			if (this->_modeloEvento.getMouseClickIzquierdo()){
				modeloNivel.moverJugador(mousePosX,mousePosY,idJugador); // Busca por ID el jugador a mover
			}
			
		}
		
		this->_modeloEvento.cargarProximoEvento();  // Con esto descarto el evento que acabo de leer y cargo el próximo

		modeloNivel.actualizar(idJugador); // TODO: Ver si esta línea va acá, o si va afuera del while, y de esa forma se debe actualizar a todos los jugadores existentes Preguntar Mati
	}

	return true;
}

void ModeloLoop::setProxyControladorEvento(ProxyControladorEvento* pProxyEvento){
	this->_modeloEvento.setProxyControladorEvento(pProxyEvento);
	return void();
}
