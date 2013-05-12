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
	Serializadora s;
	this->serializar(s,entidad);
	return this->pCliente->enviar(s);
}

// Devuelve true si sacó datos de la cola de sockets. Devuelve false si la cola estaba vacía
// Para ver si hubo errores al recibir del socket debo ver ProxyModeloEntidad::stEntidad.errorEnSocket, y ver si es true
bool ProxyControladorEvento::recibirEvento(ProxyControladorEvento::stEvento& evento){

	// Inicialo el atributo de finalización de juego por si no se actualiza al serializar
	evento.finalizoElJuego = false;

	Serializadora s;
	if (this->pServidor->recibirMasivo(s)){
		if (s.size() > 0){
			this->hidratar(s,evento);
		}else{
			evento.errorEnSocket = false;
			return false;
		}
	}
	else{
		evento.errorEnSocket = true;
	}
	return true;
}

void ProxyControladorEvento::serializar(Serializadora& s,ProxyControladorEvento::stEvento& evento){
	s.addInt(evento.id);
	//s.addBool(evento.errorEnSocket);
	s.addInt(evento.mouseX);
	s.addInt(evento.mouseY);
	s.addBool(evento.teclaA);
	s.addBool(evento.teclaS);
	s.addBool(evento.mouseClickIzquierdo);
	s.addBool(evento.finalizoElJuego);
}

void ProxyControladorEvento::hidratar(Serializadora& s,ProxyControladorEvento::stEvento& evento){
	evento.id = s.getInt();
	//evento.errorEnSocket = s.getBool();
	evento.errorEnSocket = false;
	evento.mouseX = s.getInt();
	evento.mouseY = s.getInt();
	evento.teclaA = s.getBool();
	evento.teclaS = s.getBool();
	evento.mouseClickIzquierdo = s.getBool();
	evento.finalizoElJuego = s.getBool();
}


void ProxyControladorEvento::cargarStEvento(ProxyControladorEvento::stEvento& evento,int id,bool errorEnSocket,int mouseX,int mouseY,bool teclaA,bool teclaS,bool mouseClickIzquierdo,bool finalizoElJuego){
	evento.errorEnSocket = errorEnSocket;
	evento.finalizoElJuego = finalizoElJuego;
	evento.id = id;
	evento.mouseClickIzquierdo = mouseClickIzquierdo;
	evento.mouseX = mouseX;
	evento.mouseY = mouseY;
	evento.teclaA = teclaA;
	evento.teclaS = teclaS;
}

std::list<int> ProxyControladorEvento::getClientesConError(void){
	std::list<int> lista;
	if ( this->pServidor != NULL ){
		lista = this->pServidor->getNuevosClientesErroneos();
	}
	return lista;
}