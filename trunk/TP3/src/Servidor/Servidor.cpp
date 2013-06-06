#include "Servidor.h"

Servidor::Servidor(void){

}

Servidor::~Servidor(void){

}

bool Servidor::iniciar(bool singlePlayer){

	SocketServidor* pSocket = &(this->socket);

	// Inicio el escenario sin jugadores
	if( this->modeloJuego.iniciarEscenario(pSocket) == false ) return false;
	
	// inicio el hilo que recibe a cada uno de los jugadores
	if( this->modeloJuego.iniciarRecepcion(pSocket,singlePlayer) == false ) return false;

	return true;
}

void Servidor::loop(void){

	while( this->modeloJuego.cantidadJugadores() < CANTIDAD_MINIMA_JUGADORES_INICIAR_MULTI_PLAYER ){  // Espero mientras no haya jugadores
		// Se puede poner un delay de tiempo para que no de muchas vueltas mientras espera un jugador
	}

	bool quit = false;		
	while (quit == false){

		// Habilito nuevos jugadores que entraron
		this->modeloJuego.iniciarNuevosJugadores();

		if( this->modeloJuego.loop() == false) quit = true;
	
		// Si no tengo jugadores conectados cierro el juego
		if( this->modeloJuego.cantidadJugadores() < CANTIDAD_MINIMA_JUGADORES_JUGAR_MULTI_PLAYER ){
			// Emitir mensaje  "FIN DEL JUEGO"
			quit = true;
		}
	}

	// Al finalizar el juego cierro la recepción de jugadores
	this->modeloJuego.finalizarRecepcion();
	
	return void();
}

void Servidor::loopSinglePlayer(){

	while( this->modeloJuego.cantidadJugadores() != CANTIDAD_MINIMA_JUGADORES_SINGLE_PLAYER ){  // Espero mientras no haya jugadores
		// Se puede poner un delay de tiempo para que no de muchas vueltas mientras espera un jugador
	}

	// Al iniciar el juego con un cliente cierro la recepción de jugadores
	this->modeloJuego.finalizarRecepcion();

	// Solo inicio a un jugador 
	this->modeloJuego.iniciarNuevosJugadores();

	bool quit = false;		
	while (quit == false){
		if( this->modeloJuego.loop() == false) quit = true;

		// Si el jugador se desconecto
		if( this->modeloJuego.cantidadJugadores() != CANTIDAD_MINIMA_JUGADORES_SINGLE_PLAYER ){
			// Emitir mensaje  "FIN DEL JUEGO"
			quit = true;
		}
	}

	return void();
}

bool Servidor::correrJuego(void){
	if( this->iniciar(false) == true ){
		this->loop();
	}else{
		Log::getInstance().log(1,__FILE__,__LINE__,"Error al iniciar el juego el servidor.");
		return false;
	}
	return true;
}

void Servidor::correrJuegoSinglePlayer(void){
	this->loopSinglePlayer();
	return void();
}

bool Servidor::iniciarSinglePlayer(void){
	if( this->iniciar(true) == true ){
		return true;
	}else{
		Log::getInstance().log(1,__FILE__,__LINE__,"Error al iniciar el juego el servidor.");
		return false;
	}
}

void Servidor::destruirEntidades(void){
	this->modeloJuego.destruirEntidades();
}
