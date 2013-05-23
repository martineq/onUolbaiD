#include "ConexionServidor.h"

ConexionServidor::ConexionServidor(void){
	
}

ConexionServidor::~ConexionServidor(void){

}

bool ConexionServidor::iniciarAplicacion(void){
	return this->socketApp.iniciarAplicacion();
}

bool ConexionServidor::finalizarAplicacion(void){
	return this->socketApp.finalizarAplicacion();
}	

bool ConexionServidor::abrir(void){
	return this->socketApp.abrir();
}

bool ConexionServidor::cerrar(void){
	return this->socketApp.cerrar();
}

// Hace el enlazado (bind) del socket
bool ConexionServidor::enlazarConexion(int puerto){
	return this->socketApp.enlazarConexion(puerto);
}

// Pone el socket del servidor en modo de escucha, para luego poder aceptar clientes
bool ConexionServidor::escuchar(void){
	return this->socketApp.escuchar();
}

// Inicio el socket de un cliente y lo agrego a mi lista de clientes. Devulve false en caso de error
bool ConexionServidor::aceptarCliente(ConexionCliente* cliente){
	SOCKET socketCliente;
	if( this->socketApp.aceptarCliente(socketCliente) == false ) return false;
	cliente->setSocket(socketCliente);
	return true;
}

int ConexionServidor::selectLectura(void){
	return this->socketApp.selectLectura(3000000); // 1000000 uSeg = 1000 mSeg = 1 seg					
}

int ConexionServidor::selectEscritura(void){
	return this->socketApp.selectEscritura(3000000); // 1000000 uSeg = 1000 mSeg = 1 seg					
}