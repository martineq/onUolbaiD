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

// Idem enviarEntidad() pero para enviar a un cliente en particular
// Nota: Este m�todo est� creado para ser usado en el hilo de configuraci�n, desde el ModeloFactory.
// El cliente debe estar seteado en Individual para que funcione. 
bool ProxyModeloEntidad::enviarEntidadIndividual(ProxyModeloEntidad::stEntidad entidad,int id){
	// TODO: Implementar igual que enviarEntidad() pero usando el enviarIndividual()
	// Ac� uso this->pServidor->enviarIndividual;
	return true;
}

// Idem enviarEntidad() pero para recibir directo
// Nota: Este m�todo est� creado para ser usado desde el VistaFactory.
// El cliente debe estar seteado en Individual para que funcione. 
bool ProxyModeloEntidad::recibirEntidadIndividual(ProxyModeloEntidad::stEntidad& entidad){
	return this->recibirEntidad(entidad);
}	

// Env�o la entidad a trav�s del socket
// Devuelve true lo pudo enviar exitosamente. Devuelve false si hubo error al enviar. // TODO: Despu�s se deber� verificar quien tuvo el error y eliminarlo, en cada loop
bool ProxyModeloEntidad::enviarEntidad(ProxyModeloEntidad::stEntidad entidad){
	// TODO: Implementar
	// Ac� uso this->pServidor->enviarMasivo;
	return true;
}

// Devuelve true si sac� datos de la cola de sockets. Devuelve false la cola estaba vac�a
// Para ver si hubo errores al recibir del socket debo ver ProxyModeloEntidad::stEntidad.errorEnSocket, y ver si es true
bool ProxyModeloEntidad::recibirEntidad(ProxyModeloEntidad::stEntidad& entidad){
	// TODO: Implementar
	// Ac� uso this->pCliente->recibir;
	return true;
}