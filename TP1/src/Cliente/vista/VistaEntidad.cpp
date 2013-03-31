#include "VistaEntidad.h"

long VistaEntidad::contador = 0; // Para el ID

VistaEntidad::VistaEntidad(double x,double y,double alto,double ancho,double posicionReferenciaX,double posicionReferenciaY,double fps,double delay,std::list<std::string> listaAnimaciones,bool esJugador){
	this->id = (int)InterlockedIncrement(&(this->contador));  // Genera un ID
	this->x = x;
	this->y = y;
	this->alto = alto;
	this->ancho = ancho;
	this->posicionReferenciaX = posicionReferenciaX;
	this->posicionReferenciaY = posicionReferenciaY;
	this->fps = fps;
	this->delay = delay;
	this->esJugador = esJugador;
	this->listaAnimaciones = listaAnimaciones;
	this->esNecesarioRefrescar = true;
}

VistaEntidad::~VistaEntidad(void){

}

void VistaEntidad::actualizar(class Observable* s){

	// En este punto ya se que el parámetro <s> se puede castear a ((ModeloEntidad*)s)

    // Actualizo datos, por ejemplo...
	// this->posX = ((ModeloEntidad*)s)->obtenerPosX();
	//...completar con lo necesario

}


bool VistaEntidad::getEsJugador(void){
	return (this->esJugador);
}

int VistaEntidad::getId(void){	// Para el ID
    return (this->id);
}

double VistaEntidad::getX(void){
	return (this->x);
}

double VistaEntidad::getY(void){
	return (this->y);
}

double VistaEntidad::getAlto(void){
	return (this->alto);
}

double VistaEntidad::getAncho(void){
	return (this->ancho);
}

double VistaEntidad::getPosRefX(void){
	return (this->posicionReferenciaX);
}

double VistaEntidad::getPosRefY(void){
	return (this->posicionReferenciaY);
}

double VistaEntidad::getFps(void){
	return (this->fps);
}

double VistaEntidad::getDelay(void){
	return (this->delay);
}

std::list<std::string> VistaEntidad::getListaAnimaciones(void){
	return (this->listaAnimaciones);
}

bool VistaEntidad::getEsNecesarioRefrescar(void){
	return this->esNecesarioRefrescar;
}


void VistaEntidad::setX(double x){
	this->x = x;
}

void VistaEntidad::setY(double y){
	this->y = y;
}

void VistaEntidad::setEsNecesarioRefrescar(bool boolRefrescar){
	this->esNecesarioRefrescar = boolRefrescar;
}