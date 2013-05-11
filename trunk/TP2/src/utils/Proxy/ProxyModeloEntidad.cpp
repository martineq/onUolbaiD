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
	// >>> Implementar
	// Ac� uso this->pServidor->enviarIndividual;
	return true;
}

// Idem enviarEntidad() pero para recibir directo
// Nota: Este m�todo est� creado para ser usado desde el VistaFactory.
// El cliente debe estar seteado en Individual para que funcione. 
// OJO: Ac� se da por supuesto que el cliente se encuentra en modo directo ("EnvioDirecto")
bool ProxyModeloEntidad::recibirEntidadIndividual(ProxyModeloEntidad::stEntidad& entidad){
	
	this->recibirEntidad(entidad);

	// Ac� uso:
	// if( this->pCliente->recibir(...) == false ) entidad.errorEnSocket = true;

	if( entidad.errorEnSocket == true){
		return false;
	}else{
		return true;
	}

}	

// Env�o la entidad a trav�s del socket
// Devuelve true lo pudo enviar exitosamente. Devuelve false si hubo error al enviar.
// Nota: Despu�s se deber� verificar quien tuvo el error y eliminarlo, en cada loop
bool ProxyModeloEntidad::enviarEntidad(ProxyModeloEntidad::stEntidad entidad){
	// >>> Implementar
	// Ac� uso this->pServidor->enviarMasivo;
	return true;
}

// Devuelve true si sac� datos de la cola de sockets. Devuelve false la cola estaba vac�a
// Para ver si hubo errores al recibir del socket debo ver ProxyModeloEntidad::stEntidad.errorEnSocket, y ver si es true
bool ProxyModeloEntidad::recibirEntidad(ProxyModeloEntidad::stEntidad& entidad){
	// >>> Implementar
	// Este m�todo tiene que hacerse cargo de poner en true o false el valor errorEnSocket
	// Ac� uso this->pCliente->recibir;
	return true;
}

// para los que usan el proxy y quieren cargar el struct
void ProxyModeloEntidad::cargarStEntidad(ProxyModeloEntidad::stEntidad& entidad,int id,bool errorEnSocket,bool entidadCongelada,std::string nombreEntidad,double pixelSiguienteX,double pixelSiguienteY,int direccion,bool esUltimoMovimiento){
	entidad.id = id;
	entidad.errorEnSocket = errorEnSocket;
	entidad.entidadCongelada = entidadCongelada;
	entidad.nombreEntidad = nombreEntidad;
	entidad.pixelSiguienteX = pixelSiguienteX;
	entidad.pixelSiguienteY = pixelSiguienteY;
	entidad.direccion = direccion;
	entidad.esUltimoMovimiento = esUltimoMovimiento;

}

// TODO: Implementar los m�todos del proxy. Ver si hace falta agregar al struct mas variables necesarias 