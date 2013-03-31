#include "VistaScroll.h"

long VistaScroll::contador = 0; // Para el ID

VistaScroll::VistaScroll(double x,double y,double alto,double ancho){
	this->id = InterlockedIncrement(&(this->contador));  // Genera un ID
	this->x = x;
	this->y = y;
	this->alto = alto;
	this->ancho = ancho;
}

VistaScroll::~VistaScroll(void){

}

int VistaScroll::obtenerId(void){	// Para el ID
    return ((int)this->id);
}

void VistaScroll::actualizar(class Observable* s){

	// En este punto ya se que el parámetro <s> se puede castear a ((ModeloScroll*)s)

    // Actualizo datos, por ejemplo...
	// this->posX = ((ModeloScroll*)s)->obtenerPosX();
	//...completar con lo necesario

}