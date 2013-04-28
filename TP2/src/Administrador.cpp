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

bool Administrador::iniciar(){

	if( this->modoServidor == true ){
		this->servidor = new Servidor();
		if( this->servidor->iniciar() == false ){
			Log::getInstance().log(1,__FILE__,__LINE__,"No se pudo iniciar el juego en modo Servidor");
			return false;
		}
	}else{
		this->cliente = new Cliente();
		if( this->cliente->iniciar() == false ){
		Log::getInstance().log(1,__FILE__,__LINE__,"No se pudo iniciar el juego en modo Cliente");
		return false;
		}	
	}
	
	return true;
}

void Administrador::loop(){

	if( this->modoServidor == true ){
		this->servidor->loop();
	}else{
		this->cliente->loop();
	}

	return void();
}

void Administrador::setModoServidor(bool modoServidor){
	this->modoServidor = modoServidor;
	return void();
}

void Administrador::correrPruebas(void){

	Pruebas p;
	//p.PruebaSdl(); // Prueba SDL + log
	//p.PruebaYAML();	// Prueba YAML
	//p.PruebaModeloEntidad();
	//p.PruebaControladorJuego();
	//p.PruebaHilos();
	//p.PruebaAnimacion();
	p.PruebaSockets();
}
