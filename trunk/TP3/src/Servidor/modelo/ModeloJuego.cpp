#include "ModeloJuego.h"

ModeloJuego::ModeloJuego() {
	this->pHiloReceptor = NULL;
}

ModeloJuego::~ModeloJuego() {

}

bool ModeloJuego::iniciarEscenario(SocketServidor* pSocket, bool primeraVez){
	return this->_modeloFactory.crearNivel(this->_modeloNivel,this->_modeloLoop,pSocket,primeraVez);
}

// Inicio el hilo de recepción acá
bool ModeloJuego::iniciarRecepcion(SocketServidor* pSocket,bool singlePlayer){

	//Cargo los prámetros necesarios para la configuración del jugador
	HiloConfiguracion::stParametrosConfiguracion parametros;
	parametros.pModeloNivel = &(this->_modeloNivel);
	parametros.pModeloFactory = &(this->_modeloFactory);
	parametros.pServidor = pSocket;
	parametros.singlePlayer = singlePlayer;

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
	return this->_modeloLoop.loop(this->_modeloNivel);
}

int ModeloJuego::cantidadJugadores(void){
	return this->_modeloNivel.cantidadJugadores();
}

void ModeloJuego::iniciarNuevosJugadores(void){
	this->_modeloNivel.iniciarNuevosJugadores();
	return void();
}

void ModeloJuego::destruirEntidades(){
	this->_modeloNivel.destruirListas();
}

void ModeloJuego::reset(){
	this->_modeloNivel.reset();
	return void();
}
