#include "ProxyModeloEntidad.h"

ProxyModeloEntidad::ProxyModeloEntidad(void){
	this->pCliente = NULL;
	this->pServidor = NULL;
}

ProxyModeloEntidad::~ProxyModeloEntidad(void){

}

void ProxyModeloEntidad::setSocketCliente(SocketCliente* pCliente){
	this->pCliente = pCliente;
}

void ProxyModeloEntidad::setSocketServidor(SocketServidor* pServidor){
	this->pServidor = pServidor;
}


// Env�o la entidad a trav�s del socket
// Devuelve true lo pudo enviar exitosamente. Devuelve false si hubo error al enviar. // TODO: Despu�s se deber� verificar quien tuvo el error y eliminarlo, en cada loop
bool ProxyModeloEntidad::enviarEntidad(ProxyModeloEntidad::stEntidad entidad){
	// TODO: Implementar
	// Ac� uso this->pCliente;
	return true;
}

// Devuelve true si sac� datos de la cola de sockets. Devuelve false la cola estaba vac�a
// Para ver si hubo errores al recibir del socket debo ver ProxyModeloEntidad::stEntidad.errorEnSocket, y ver si es true
bool ProxyModeloEntidad::recibirEntidad(ProxyModeloEntidad::stEntidad& entidad){
	// TODO: Implementar
	// Ac� uso this->pCliente = NULL;
	return true;
}