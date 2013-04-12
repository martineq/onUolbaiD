#include "VistaScroll.h"

long VistaScroll::contador = 0; // Para el ID

VistaScroll::VistaScroll(double x,double y,double alto,double ancho){
	this->_id = (int)InterlockedIncrement(&(this->contador));  // Genera un ID
	this->x = x;
	this->y = y;
	this->alto = alto;
	this->ancho = ancho;
	this->esNecesarioRefrescar = true;
}

VistaScroll::~VistaScroll(void){

}

int VistaScroll::id() const {
    return this->_id;
}

void VistaScroll::actualizar(class Observable* s){

	// En este punto ya se que el parámetro <s> se puede castear a ((ModeloScroll*)s)

	// TODO: Completar con los métodos brindados por ModeloEntidad
/*	this->x = ((ModeloScroll*)s)->getX();
	this->y = ((ModeloScroll*)s)->getY();
	this->esNecesarioRefrescar = true;
*/
}

/*int VistaScroll::getId(void){
    return (this->id);
}*/

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

bool VistaScroll::getEsNecesarioRefrescar(void){
	return this->esNecesarioRefrescar;
}

void VistaScroll::setEsNecesarioRefrescar(bool boolRefrescar){
	this->esNecesarioRefrescar = boolRefrescar;
}