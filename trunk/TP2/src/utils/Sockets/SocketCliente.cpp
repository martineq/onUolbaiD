#include "SocketCliente.h"

SocketCliente::SocketCliente(void){
	this->miConexion.setEsIndividual();
	this->envioDirecto = true;
	this->miConexion.iniciarAplicacion();
}

SocketCliente::~SocketCliente(void){
	this->miConexion.cerrarActividad();
	this->miConexion.cerrar();
	this->miConexion.finalizarAplicacion();
}

bool SocketCliente::iniciarCliente(const char* nombreHost, int puerto){
	if( this->miConexion.abrir() == false ) return false;
	if( this->miConexion.conectar(nombreHost,puerto) == false ) return false;
	this->miConexion.iniciarRecepcion(NULL,NULL,NULL);
	this->miConexion.iniciarEnvio();
	Log::getInstance().log(1,__FILE__,__LINE__,"[CLIENTE]Conexiones creadas" );
	return true;
}

void SocketCliente::setEnvioDirecto(void){
	this->miConexion.setEsIndividual();
	this->envioDirecto = true;
}

void SocketCliente::setEnvioIndirecto(void){
	this->miConexion.setMasiva();
	this->envioDirecto = false;
}

bool SocketCliente::enviar(const char *pBuffer,unsigned int tamanio){

	if( this->envioDirecto == true ){
		return this->miConexion.enviarDirecto(pBuffer,tamanio);
	}else{
		return this->miConexion.enviar(pBuffer,tamanio);
	}
}

bool SocketCliente::recibir(char **pBuffer,unsigned int& tamanioRecibido){
	if( this->envioDirecto == true ){
		return this->miConexion.recibirDirecto(pBuffer,tamanioRecibido);
	}else{
		return this->miConexion.recibir(pBuffer,tamanioRecibido);
	}
}

bool SocketCliente::enviarArchivo(const char *rutaOrigen){
	return this->miConexion.enviarArchivo(rutaOrigen);
}

bool SocketCliente::recibirArchivo(const char *rutaDestino){
	return this->miConexion.recibirArchivo(rutaDestino);
}