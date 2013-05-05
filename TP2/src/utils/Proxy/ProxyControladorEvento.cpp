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


// Env�o el evento a trav�s del socket
// Devuelve true lo pudo enviar exitosamente. Devuelve false si hubo error al enviar 
bool ProxyControladorEvento::enviarEvento(ProxyControladorEvento::stEvento entidad){
	// TODO: Implementar
	// Ac� uso this->pCliente;
	return true;
}

// Devuelve true si sac� datos de la cola de sockets. Devuelve false si la cola estaba vac�a
// Para ver si hubo errores al recibir del socket debo ver ProxyModeloEntidad::stEntidad.errorEnSocket, y ver si es true
bool ProxyControladorEvento::recibirEvento(ProxyControladorEvento::stEvento& evento){
	// TODO: Implementar
	// Ac� uso this->pServidor;
	return true;
}

