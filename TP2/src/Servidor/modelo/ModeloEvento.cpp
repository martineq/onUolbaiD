#include "ModeloEvento.h"

ModeloEvento::ModeloEvento() {
	this->hayEventoEnEspera = false;
	this->eventoEnEspera.id = -1;
}

ModeloEvento::~ModeloEvento(){

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

bool ModeloEvento::getMouseDentroPantalla() {
	return this->listaEventos.front().mouseDentroPantalla;
}

void ModeloEvento::SetProxyControladorEvento(ProxyControladorEvento* pProxyEvento){
	this->pProxyEvento = pProxyEvento;
	return void();
}