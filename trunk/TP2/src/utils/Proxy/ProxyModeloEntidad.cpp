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


// Envío la entidad a través del socket
// Devuelve true lo pudo enviar exitosamente. Devuelve false si hubo error al enviar. // TODO: Después se deberá verificar quien tuvo el error y eliminarlo, en cada loop
bool ProxyModeloEntidad::enviarEntidad(ProxyModeloEntidad::stEntidad entidad){
	// TODO: Implementar
	// Acá uso this->pCliente;
	return true;
}

// Devuelve true si sacó datos de la cola de sockets. Devuelve false la cola estaba vacía
// Para ver si hubo errores al recibir del socket debo ver ProxyModeloEntidad::stEntidad.errorEnSocket, y ver si es true
bool ProxyModeloEntidad::recibirEntidad(ProxyModeloEntidad::stEntidad& entidad){
	// TODO: Implementar
	// Acá uso this->pCliente = NULL;
	return true;
}