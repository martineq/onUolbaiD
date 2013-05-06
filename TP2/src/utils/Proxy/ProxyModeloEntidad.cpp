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
// Nota: Este método está creado para ser usado en el hilo de configuración, desde el ModeloFactory.
// El cliente debe estar seteado en Individual para que funcione. 
bool ProxyModeloEntidad::enviarEntidadIndividual(ProxyModeloEntidad::stEntidad entidad,int id){
	// >>> Implementar
	// Acá uso this->pServidor->enviarIndividual;
	return true;
}

// Idem enviarEntidad() pero para recibir directo
// Nota: Este método está creado para ser usado desde el VistaFactory.
// El cliente debe estar seteado en Individual para que funcione. 
bool ProxyModeloEntidad::recibirEntidadIndividual(ProxyModeloEntidad::stEntidad& entidad){
	return this->recibirEntidad(entidad);
}	

// Envío la entidad a través del socket
// Devuelve true lo pudo enviar exitosamente. Devuelve false si hubo error al enviar.
// Nota: Después se deberá verificar quien tuvo el error y eliminarlo, en cada loop
bool ProxyModeloEntidad::enviarEntidad(ProxyModeloEntidad::stEntidad entidad){
	// >>> Implementar
	// Acá uso this->pServidor->enviarMasivo;
	return true;
}

// Devuelve true si sacó datos de la cola de sockets. Devuelve false la cola estaba vacía
// Para ver si hubo errores al recibir del socket debo ver ProxyModeloEntidad::stEntidad.errorEnSocket, y ver si es true
bool ProxyModeloEntidad::recibirEntidad(ProxyModeloEntidad::stEntidad& entidad){
	// >>> Implementar
	// Este método tiene que hacerse cargo de poner en true o false el valor errorEnSocket
	// Acá uso this->pCliente->recibir;
	return true;
}

// TODO: Implementar los métodos de los proxys