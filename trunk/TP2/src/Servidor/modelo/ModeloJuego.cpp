#include "ModeloJuego.h"

ModeloJuego::ModeloJuego() {
	this->jugadoresConectados = 0;
	this->pHiloReceptor = NULL;
}

ModeloJuego::~ModeloJuego() {

}

bool ModeloJuego::iniciarEscenario(SocketServidor* pSocket){
	return this->_modeloFactory.crearNivel(this->_modeloNivel,this->_modeloLoop,pSocket);
}

// Inicio el hilo de recepción acá
bool ModeloJuego::iniciarRecepcion(SocketServidor* pSocket){

	//Cargo los prámetros necesarios para la configuración del jugador
	HiloConfiguracion::stParametrosConfiguracion parametros;
	parametros.pJugadoresConectados = &(this->jugadoresConectados);
	parametros.pModeloFactory = &(this->_modeloFactory);
	parametros.pModeloJuego = (this);
	parametros.pMutexJugadoresConectados = &(this->mutexJugadoresConectados);
	parametros.pServidor = pSocket;

	this->pHiloReceptor = new HiloReceptor();
	this->pHiloReceptor->correrRecepcion(parametros);

	return true;
}

void ModeloJuego::finalizarRecepcion(){
	if( this->pHiloReceptor != NULL ){
		this->pHiloReceptor->detenerActividad();
		this->pHiloReceptor->join();
		delete this->pHiloReceptor;
		this->pHiloReceptor = NULL;
	}
	return void();
}

bool ModeloJuego::loop() {
	return this->_modeloLoop.loop(this->_modeloNivel,&(this->jugadoresConectados), &(this->mutexJugadoresConectados));
}

void ModeloJuego::destruirEntidades(){
	this->_modeloNivel.destruirListas();
}

bool ModeloJuego::hayJugadores(void){
	bool resultado = false;
	this->mutexJugadoresConectados.lockLectura(__FILE__,__LINE__);
	if( this->jugadoresConectados > 0 ) resultado = true;
	this->mutexJugadoresConectados.unlock(__FILE__,__LINE__);
	return resultado;
}