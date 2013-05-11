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
	// >>> Implementar
	// Acá uso this->pCliente;
	return true;
}

// Devuelve true si sacó datos de la cola de sockets. Devuelve false si la cola estaba vacía
// Para ver si hubo errores al recibir del socket debo ver ProxyModeloEntidad::stEntidad.errorEnSocket, y ver si es true
bool ProxyControladorEvento::recibirEvento(ProxyControladorEvento::stEvento& evento){
	// >>> Implementar
	// Acá uso this->pServidor;
	return true;
}

void ProxyControladorEvento::cargarStEvento(ProxyControladorEvento::stEvento& evento,int id,bool errorEnSocket,int mouseX,int mouseY,bool teclaA,bool teclaS,bool mouseClickIzquierdo,bool mouseDentroPantalla,bool finalizoElJuego){
	evento.errorEnSocket = errorEnSocket;
	evento.finalizoElJuego = finalizoElJuego;
	evento.id = id;
	evento.mouseClickIzquierdo = mouseClickIzquierdo;
	evento.mouseDentroPantalla = mouseDentroPantalla;
	evento.mouseX = mouseX;
	evento.mouseY = mouseY;
	evento.teclaA = teclaA;
	evento.teclaS = teclaS;
}

// TODO: Implementar los métodos del proxy. Ver si hace falta agregar al struct mas variables necesarias 