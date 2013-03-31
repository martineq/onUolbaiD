#include "VistaEntidad.h"

long VistaEntidad::contador = 0; // Para el ID

VistaEntidad::VistaEntidad(double x,double y,double alto,double ancho,double posicionReferenciaX,double posicionReferenciaY,double fps,double delay,bool esPersonaje){
	this->id = InterlockedIncrement(&(this->contador));  // Genera un ID
	this->x = x;
	this->y = y;
	this->alto = alto;
	this->ancho = ancho;
	this->posicionReferenciaX = posicionReferenciaX;
	this->posicionReferenciaY = posicionReferenciaY;
	this->fps = fps;
	this->delay = delay;
}

VistaEntidad::~VistaEntidad(void){

}

int VistaEntidad::obtenerId(void){	// Para el ID
    return ((int)this->id);
}

void VistaEntidad::actualizar(class Observable* s){

	// En este punto ya se que el parámetro <s> se puede castear a ((ModeloEntidad*)s)

    // Actualizo datos, por ejemplo...
	// this->posX = ((ModeloEntidad*)s)->obtenerPosX();
	//...completar con lo necesario

}