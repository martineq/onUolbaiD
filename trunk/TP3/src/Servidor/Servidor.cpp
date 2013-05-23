#include "Servidor.h"

Servidor::Servidor(void){

}

Servidor::~Servidor(void){

}

bool Servidor::iniciar(void){

	SocketServidor* pSocket = &(this->socket);

	// Inicio el escenario sin jugadores
	if( this->modeloJuego.iniciarEscenario(pSocket) == false ) return false;
	
	// inicio el hilo que recibe a cada uno de los jugadores
	if( this->modeloJuego.iniciarRecepcion(pSocket) == false ) return false;

	return true;
}

void Servidor::loop(void){

	while( this->modeloJuego.cantidadJugadores() < 1 ){  // Espero mientras no haya jugadores
		// Se puede poner un delay de tiempo para que no de muchas vueltas mientras espera un jugador
	}

	bool quit = false;		
	while (quit == false){
		if( this->modeloJuego.loop() == false) quit = true;
	
		// Si no tengo jugadores conectados cierro el juego
		if( this->modeloJuego.cantidadJugadores() < 1 ){
			// Emitir mensaje  "FIN DEL JUEGO"
			quit = true;
		}
	}

	// Al finalizar el juego cierro la recepción de jugadores
	this->modeloJuego.finalizarRecepcion();
	
		return void();
}

bool Servidor::correrJuego(void){
	if( this->iniciar() == true ){
		this->loop();
		this->modeloJuego.finalizarRecepcion();
	}else{
		Log::getInstance().log(1,__FILE__,__LINE__,"Error al iniciar el juego el cliente.");
		return false;
	}
	return true;
}

void Servidor::destruirEntidades(void){
	this->modeloJuego.destruirEntidades();
}
