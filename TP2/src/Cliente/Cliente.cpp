#include "./Cliente.h"

Cliente::Cliente(void){
	this->vistaChat = NULL;
}

Cliente::~Cliente(void){
	if (this->vistaChat != NULL)
		delete this->vistaChat;
}

bool Cliente::iniciar(std::string mote,std::string personaje){

	SocketCliente* pSocket = &(this->socket);
	
	// Instancia el nivel en vistaJuego y el scroll con su proxy en ControladorEvento
	if( this->vistaJuego.iniciar(pSocket,this->controladorJuego.getControladorLoop()->getControladorEvento(),mote,personaje) == false ) return false;
	
	if (this->vistaChat == NULL) {
		//TODO: Arreglar la posicion para que se vea abajo de la pantalla
		Posicion posicion;
		this->vistaChat = new VistaChat(posicion, this->vistaJuego.getVistaNivel()->getJugador(), this->controladorJuego.getControladorLoop()->getControladorEvento()->getProxyEvento());
	}

	this->controladorJuego.asignarChat(this->vistaChat);
	this->vistaJuego.asignarChat(this->vistaChat);

	return true;
}

void Cliente::loop(void){

	bool quit = false;		
	while (quit == false){
		if( this->controladorJuego.loop(this->vistaJuego.getVistaNivel()) == false) quit = true;
		if( this->vistaJuego.loop() == false) quit = true;
	}
}

bool Cliente::correrJuego(std::string mote,std::string personaje){
	if( this->iniciar(mote,personaje) == true ){
		this->loop();
	}else{
		Log::getInstance().log(1,__FILE__,__LINE__,"Error al iniciar el juego el cliente.");
		return false;
	}
	return true;
}

void Cliente::destruirEntidades(void){
	return this->vistaJuego.destruirEntidades();
}
