#include "ModeloLoop.h"

ModeloLoop::ModeloLoop(){
	this->tiempoUltimoChequeo = 0;
}

ModeloLoop::~ModeloLoop(){

}

bool ModeloLoop::loop(ModeloNivel& modeloNivel){

	// Envia datos a todos los clientes cada cierto tiempo, para ver si no se desconectaron
	this->chequearConexion(modeloNivel);

	// Acá lo primero que hago es congelar a los clientes, para los que tuvieron error de sockets
	this->desconectarJugadoresConError(modeloNivel);

	// Recorro varios eventos en un solo loop. Está asegurado que no habrá 2 eventos del mismo ID.
	while (this->_modeloEvento.getActualizado()) {
	
		// Obtengo el id para ubicarlo en el nivel
		int idJugador = this->_modeloEvento.getIdJugador(); 

		// Si el cliente finalizo su juego tambien lo congelo
		if( this->_modeloEvento.finalizoElJuego() == true ){
			// En caso de finalización del juego o error de sockets se congela al jugador
			modeloNivel.desconectarJugador(idJugador);
		}
		else if (this->_modeloEvento.getIdDestinatarioChat() != -1) {
			ModeloJugador* remitente = modeloNivel.obtenerJugador(this->_modeloEvento.getIdJugador());
			if (remitente == NULL)
				return true;
			ModeloJugador* destinatario = modeloNivel.obtenerJugador(this->_modeloEvento.getIdDestinatarioChat());
			if (destinatario == NULL)
				return true;
			destinatario->enviarMensaje(remitente, this->_modeloEvento.getMensajeChat());
		}
		else if (this->_modeloEvento.getMouseClickIzquierdo()) {
			// En el caso de no haber errores y no haber terminado el juego se obtienen los datos para acutalizar
			modeloNivel.ejecutarAccionJugador(this->_modeloEvento.getMousePosX(), this->_modeloEvento.getMousePosY(), idJugador);
		}
		else if (this->_modeloEvento.getKeyD())
			modeloNivel.activarHechizoHielo(idJugador);
		
		this->_modeloEvento.cargarProximoEvento();  // Con esto descarto el evento que acabo de leer y cargo el próximo
	}

	modeloNivel.actualizar();

	return true;
}

void ModeloLoop::desconectarJugadoresConError(ModeloNivel& modeloNivel){

	std::list<int> listaIdErroneos = this->_modeloEvento.getClientesConError();
	
	for( std::list<int>::iterator it = listaIdErroneos.begin() ; it != listaIdErroneos.end() ; it++){
		int idErroneo = (*it);
		modeloNivel.desconectarJugador(idErroneo);
	}

	return void();
}

void ModeloLoop::setProxyControladorEvento(ProxyControladorEvento* pProxyEvento){
	this->_modeloEvento.setProxyControladorEvento(pProxyEvento);
	return void();
}

void ModeloLoop::chequearConexion(ModeloNivel& modeloNivel){
	
	unsigned long periodoTranscurrido = (Temporizador::getInstance().obtenerTics()) - (this->tiempoUltimoChequeo);

	// Tiempo en milisegundos
	if( periodoTranscurrido > PERIODO_VERIFICACION_ERROR_DESCONEXION ){
		modeloNivel.chequearConexion();
		this->tiempoUltimoChequeo = Temporizador::getInstance().obtenerTics();
	}
	
	return void();
}
