#include "./Administrador.h"

Administrador::Administrador(void){
	this->modoServidor = false;
	this->modoUnJugador = false;
	this->servidor = NULL;
	this->cliente = NULL;
}

Administrador::~Administrador(void){
	if( this->servidor != NULL){
		this->servidor->destruirEntidades();
		delete this->servidor;
		this->servidor = NULL;
	}

	if( this->cliente != NULL){
		this->cliente->destruirEntidades();
		delete this->cliente;
		this->cliente = NULL;
	}
}

void Administrador::correrJuego(std::string mote,std::string personaje){

	this->menuLineaComandos();

	if( this->modoUnJugador == true ){

		// Inicio el modo para un jugador
		this->correrSinglePlayer(mote,personaje);

	}else{
		if( this->modoServidor == true ){
			this->servidor = new Servidor();
			if( this->servidor->correrJuego() == false ){
				Log::getInstance().log(1,__FILE__,__LINE__,"Error al correr el juego en modo Servidor");
			}
		}else{
			this->cliente = new Cliente();
			if( this->cliente->correrJuego(mote,personaje) == false ){
			Log::getInstance().log(1,__FILE__,__LINE__,"Error al correr el juego en modo Cliente");
			}	
		}
	}

	return void();
}

void Administrador::menuLineaComandos(void){

	std::string opc;


	// Pregunto por el modo de un jugador
	std::cout << "Ingrese \"s\" para modo de Un Jugador, otra tecla para rechazar " << std::endl;
	getline (std::cin,opc);
	if( opc.compare("s") == 0 || opc.compare("S") == 0 ){
		this->modoUnJugador = true;
		std::cout << "Modo de Un Jugador seleccionado" << std::endl;
		Log::getInstance().log(1,__FILE__,__LINE__,"Modo de Un Jugador seleccionado");
		return void();
	}else{
		this->modoUnJugador = false;
	}
	
	// Elijo servidor o cliente
	while( opc.compare("s") != 0 && opc.compare("S") != 0  && opc.compare("c") != 0 && opc.compare("C") != 0 ){
		std::cout << "Ingrese \"s\" para modo Servidor o \"c\" para Cliente: " << std::endl;
		getline (std::cin,opc);
		if( opc.compare("s") != 0 && opc.compare("S") != 0  && opc.compare("c") != 0 && opc.compare("C") != 0 ){
			std::cout << "Se ha ingresado: "<< opc << std::endl;
		}
	}

	// Seteo la elección hecha
	if( opc.compare("s") == 0 || opc.compare("S") == 0 ){
		this->modoServidor = true;
		std::cout << "Modo Servidor seleccionado" << std::endl;
		Log::getInstance().log(1,__FILE__,__LINE__,"Modo Servidor seleccionado");
	}
	if( opc.compare("c") == 0 || opc.compare("C") == 0 ){
		this->modoServidor = false;
		std::cout << "Modo Cliente seleccionado" << std::endl;
		Log::getInstance().log(1,__FILE__,__LINE__,"Modo Cliente seleccionado");
	}

	return void();
}

void Administrador::correrSinglePlayer(std::string mote,std::string personaje){

	HiloSinglePlayer hiloServidorSinglePlayer;

	this->servidor = new Servidor();
	this->cliente = new Cliente();

	HiloSinglePlayer::stParametrosSinglePlayer parametrosServidor;
	parametrosServidor.esServidor = true;
	parametrosServidor.mote.assign(mote);
	parametrosServidor.personaje.assign(personaje);
	parametrosServidor.pCliente = NULL;
	parametrosServidor.pServidor = this->servidor;

	// Inicio el servidor
	if( this->servidor->iniciarSinglePlayer() == false ){
		Log::getInstance().log(1,__FILE__,__LINE__,"Error al correr el juego en modo Servidor");
		return void();
	}

	// Corro el juego del lado del Servidor en un hilo
	hiloServidorSinglePlayer.correrSinglePlayer(parametrosServidor);

	// Corro el Cliente en el hilo principal
	this->cliente->correrJuegoSinglePlayer(mote,personaje);

	// Una vez que terminó el cliente, puedo hacer el join del hilo del servidor
	hiloServidorSinglePlayer.join();

	return void();
}

void Administrador::correrPruebas(void){

	Pruebas p;

}