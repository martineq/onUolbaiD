#include "VistaScroll.h"

long VistaScroll::contador = 0; // Para el ID

VistaScroll::VistaScroll(double x,double y,double alto,double ancho){
	this->id = (int)InterlockedIncrement(&(this->contador));  // Genera un ID
	this->x = x;
	this->y = y;
	this->alto = alto;
	this->ancho = ancho;
}

VistaScroll::~VistaScroll(void){

}

void VistaScroll::actualizar(class Observable* s){

	// En este punto ya se que el parámetro <s> se puede castear a ((ModeloScroll*)s)

    // Actualizo datos, por ejemplo...
	// this->posX = ((ModeloScroll*)s)->obtenerPosX();
	//...completar con lo necesario
}

int VistaScroll::getId(void){
    return (this->id);
}

double VistaScroll::getX(void){
    return (this->x);	
}

double VistaScroll::getY(void){
    return (this->y);		
}

double VistaScroll::getAlto(void){
    return (this->alto);	
}

double VistaScroll::getAncho(void){
    return (this->ancho);		
}

void VistaScroll::setX(double x){
	this->x = x;
}

void VistaScroll::setY(double y){
	this->y = y;
}