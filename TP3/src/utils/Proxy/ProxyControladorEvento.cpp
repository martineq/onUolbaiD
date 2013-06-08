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
	s.addInt(evento.mouseX);
	s.addInt(evento.mouseY);
	s.addBool(evento.teclaA);
	s.addBool(evento.teclaS);
	s.addBool(evento.teclaD);
	s.addBool(evento.teclaF);
	s.addBool(evento.mouseClickIzquierdo);
	s.addBool(evento.finalizoElJuego);
	s.addInt(evento.idReceptorChat);
	s.addString(evento.mensajeChat);
}

void ProxyControladorEvento::hidratar(Serializadora& s,ProxyControladorEvento::stEvento& evento){
	evento.errorEnSocket = false; // Si se llamó a hidratar es porque no hubo error en el socket
	evento.id = s.getInt();
	evento.mouseX = s.getInt();
	evento.mouseY = s.getInt();
	evento.teclaA = s.getBool();
	evento.teclaS = s.getBool();
	evento.teclaD = s.getBool();
	evento.teclaF = s.getBool();
	evento.mouseClickIzquierdo = s.getBool();
	evento.finalizoElJuego = s.getBool();
	evento.idReceptorChat = s.getInt();
	evento.mensajeChat = s.getString();
}


void ProxyControladorEvento::cargarStEvento(ProxyControladorEvento::stEvento& evento,int id,bool errorEnSocket,int mouseX,int mouseY,
	bool teclaA,bool teclaS,bool teclaD,bool teclaF,bool mouseClickIzquierdo,bool finalizoElJuego){

	evento.id = id;
	evento.errorEnSocket = errorEnSocket;
	evento.mouseX = mouseX;
	evento.mouseY = mouseY;
	evento.teclaA = teclaA;
	evento.teclaS = teclaS;
	evento.teclaD = teclaD;
	evento.teclaF = teclaF;
	evento.mouseClickIzquierdo = mouseClickIzquierdo;
	evento.finalizoElJuego = finalizoElJuego;
	evento.idReceptorChat = -1;
	evento.mensajeChat = "";
}

void ProxyControladorEvento::cargarStEventoChat(ProxyControladorEvento::stEvento& evento,int id,int idReceptorChat,std::string mensajeChat){

	evento.id = id;
	evento.errorEnSocket = false;
	evento.mouseX = 0;
	evento.mouseY = 0;
	evento.teclaA = false;
	evento.teclaS = false;
	evento.teclaD = false;
	evento.teclaF = false;
	evento.mouseClickIzquierdo = false;
	evento.finalizoElJuego = false;
	evento.idReceptorChat = idReceptorChat;
	evento.mensajeChat = mensajeChat;
}

std::list<int> ProxyControladorEvento::getClientesConError(void){
	std::list<int> lista;
	if ( this->pServidor != NULL ){
		lista = this->pServidor->getNuevosClientesErroneos();
	}
	return lista;
}