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

bool ProxyControladorEvento::enviarEvento(ProxyControladorEvento::stEvento entidad){
	// TODO: Implementar
	// Ac� uso this->pCliente;
	return true;
}

bool ProxyControladorEvento::recibirEvento(ProxyControladorEvento::stEvento& evento){
	// TODO: Implementar
	// Ac� uso this->pServidor;
	return true;
}

