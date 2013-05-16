#include "./Administrador.h"

Administrador::Administrador(void){
	this->modoServidor = false;
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
	return void();
}

void Administrador::menuLineaComandos(void){

	std::string opc;

	while( opc.compare("s") != 0 && opc.compare("S") != 0  && opc.compare("c") != 0 && opc.compare("C") != 0 ){
		std::cout << "Ingrese \"s\" para modo Servidor o \"c\" para Cliente: " << std::endl;
		getline (std::cin,opc);
		if( opc.compare("s") != 0 && opc.compare("S") != 0  && opc.compare("c") != 0 && opc.compare("C") != 0 ){
			std::cout << "Se ha ingresado: "<< opc << std::endl;
		}
	}

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

void Administrador::correrPruebas(void){

	Pruebas p;

}