#include "ModeloEvento.h"

ModeloEvento::ModeloEvento() {
	this->hayEventoEnEspera = false;
	this->eventoEnEspera.id = -1;
	this->pProxyEvento = NULL;
}

ModeloEvento::~ModeloEvento(){
	if( this->pProxyEvento != NULL) delete this->pProxyEvento;
}

bool ModeloEvento::getActualizado(){

	if( this->listaEventos.empty() == false ){
		return true;
	}else{

		// Si antes corté por tener evento con ID repetido, el mismo quedó en espera y entonces ahora lo agrego a la lista primero
		if( this->hayEventoEnEspera == true ){
			this->listaEventos.push_back(this->eventoEnEspera);
			this->hayEventoEnEspera = false;
		}else{ // Si no hay nada para cargar, pido del proxy
			if( this->pProxyEvento->recibirEvento(this->eventoEnEspera) == false ){
				return false;
			}else{
				this->listaEventos.push_back(this->eventoEnEspera);
				this->hayEventoEnEspera = false;
			}
		}

		// Cargo la lista hasta que por alguna razon me detenga. Puede ser por que se vació el proxy o porque tengo dos eventos de un mismo ID
		bool leerDeProxy = true;
		while( leerDeProxy == true ){
			if( this->pProxyEvento->recibirEvento(this->eventoEnEspera) == false ){	// Caso: El proxy no tiene eventos para dar
				leerDeProxy = false;
			}else{
				if( this->eventoEnEspera.id == this->listaEventos.back().id ){		// Caso: Recibo evento pero tengo uno de ese ID
					this->hayEventoEnEspera = true;// Como este evento se queda, lo notifico			
					leerDeProxy = false;
				}else{																// Caso: Recibo evento de un ID que no tenía hasta ahora
					this->listaEventos.push_back(this->eventoEnEspera);
					this->hayEventoEnEspera = false;
				}

			}
			
		}

		return false;
	}

	return true;
}

int ModeloEvento::getIdJugador(){
	return this->listaEventos.front().id;
}

int ModeloEvento::getMousePosX(){
	return this->listaEventos.front().mouseX;
}

int ModeloEvento::getMousePosY(){
	return this->listaEventos.front().mouseY;
}

bool ModeloEvento::getMouseClickIzquierdo() {
	return this->listaEventos.front().mouseClickIzquierdo;
}

bool ModeloEvento::getKeyA(){
	return this->listaEventos.front().teclaA;
}

bool ModeloEvento::getKeyS(){
	return this->listaEventos.front().teclaS;
}

bool ModeloEvento::getKeyD(){
	return this->listaEventos.front().teclaD;
}

bool ModeloEvento::getKeyF(){
	return this->listaEventos.front().teclaF;
}

bool ModeloEvento::getKeyG(){
	return this->listaEventos.front().teclaG;
}

bool ModeloEvento::errorEnSocket(){
	return this->listaEventos.front().errorEnSocket;
}

bool ModeloEvento::finalizoElJuego(){
	return this->listaEventos.front().finalizoElJuego;
}

void ModeloEvento::setProxyControladorEvento(ProxyControladorEvento* pProxyEvento){
	this->pProxyEvento = pProxyEvento;
	return void();
}

void ModeloEvento::cargarProximoEvento(void){
	this->listaEventos.pop_front();
	return void();
}

std::list<int> ModeloEvento::getClientesConError(void){
	return this->pProxyEvento->getClientesConError();
}

int ModeloEvento::getIdDestinatarioChat() {
	return this->listaEventos.front().idReceptorChat;
}

std::string ModeloEvento::getMensajeChat()  {
	return this->listaEventos.front().mensajeChat;
}
