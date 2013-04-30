#include "Periodo.h"

Periodo::Periodo(){
	this->esperandoPeriodo = false;
}

Periodo::~Periodo(){

}

void Periodo::iniciar(int cantSegundos){
	timer.start();
	this->tiempoInicio = timer.get_ticks();
	this->esperandoPeriodo = true;
	this->segundos = cantSegundos;
}

// Pre:: tiene que ejecutarse inciar, para usar este metodo;
bool Periodo::estaCumplido(){
	bool estaCumplido = false;
	uint tiempoTranscurrido = timer.get_ticks() - this->tiempoInicio;
	if (tiempoTranscurrido > 1000 * this->segundos){
		estaCumplido = true;
	}
	return estaCumplido;
}

void Periodo::finalizar(){
	this->esperandoPeriodo = false;
	timer.stop();
}

