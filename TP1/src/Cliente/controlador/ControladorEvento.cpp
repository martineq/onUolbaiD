#include "ControladorEvento.h"

ControladorEvento::ControladorEvento(void){

}

ControladorEvento::~ControladorEvento(void){

}

void ControladorEvento::cambiarEstado(){
	this->notificarObservadores();
}