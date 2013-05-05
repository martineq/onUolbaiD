#include "ProxyControladorEvento.h"

ProxyControladorEvento::ProxyControladorEvento(void){
	this->pCliente = NULL;
	this->pServidor = NULL;
}

ProxyControladorEvento::~ProxyControladorEvento(void){

}

void ProxyControladorEvento::setSocketCliente(SocketCliente* pCliente){
	this->pCliente = pCliente;
}

void ProxyControladorEvento::setSocketServidor(SocketServidor* pServidor){
	this->pServidor = pServidor;
}


// Envío el evento a través del socket
// Devuelve true lo pudo enviar exitosamente. Devuelve false si hubo error al enviar 
bool ProxyControladorEvento::enviarEvento(ProxyControladorEvento::stEvento entidad){
	// TODO: Implementar
	// Acá uso this->pCliente;
	return true;
}

// Devuelve true si sacó datos de la cola de sockets. Devuelve false si la cola estaba vacía
// Para ver si hubo errores al recibir del socket debo ver ProxyModeloEntidad::stEntidad.errorEnSocket, y ver si es true
bool ProxyControladorEvento::recibirEvento(ProxyControladorEvento::stEvento& evento){
	// TODO: Implementar
	// Acá uso this->pServidor;
	return true;
}

