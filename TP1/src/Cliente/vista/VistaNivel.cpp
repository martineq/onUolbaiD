#include "./VistaNivel.h"


VistaNivel::VistaNivel(){
	this->scroll = NULL;
}

VistaNivel::~VistaNivel(){
 // Los punteros ya son destruidos desde el Administrador
}

Observador* VistaNivel::obtenerObservadorJugador(void){
	Observador* pObservador;

	for (std::list<VistaEntidad*>::iterator it=this->listaEntidades.begin() ; it != this->listaEntidades.end(); it++ ){
		if( (*it)->getEsJugador() == false ){
			pObservador = ((Observador*)*it);
		}
	}
	return pObservador;
}

Observador* VistaNivel::obtenerObservadorScroll(void){
	return (Observador*)this->scroll;
}

std::list<Observador*> VistaNivel::obtenerObservadoresEntidad(void){

	std::list<Observador*> listaObservadoresEntidad;

	for (std::list<VistaEntidad*>::iterator it=this->listaEntidades.begin() ; it != this->listaEntidades.end(); it++ ){
		if( (*it)->getEsJugador() == false ){
			listaObservadoresEntidad.push_back( ((Observador*)*it) );
		}
	}

	return listaObservadoresEntidad;

}

VistaScroll* VistaNivel::getScroll(void){
	return this->scroll;
}

std::list<VistaEntidad*> VistaNivel::getListaEntidades(void){
	return this->listaEntidades;
}

void VistaNivel::agregarJugador(VistaEntidad* pJugador){
	this->listaEntidades.push_back(pJugador);
	return void();
}

void VistaNivel::agregarEntidad(VistaEntidad* pEntidad){
	this->listaEntidades.push_back(pEntidad);
	return void();
}

void VistaNivel::agregarScroll(VistaScroll* pScroll){
	this->scroll = pScroll;
	return void();
}

int VistaNivel::getAltoPantalla(void){
	return this->alto;
}

int VistaNivel::getAnchoPantalla(void){
	return this->ancho;
}

void VistaNivel::setAltoPantalla(int alto){
	this->alto = alto;
}

void VistaNivel::setAnchoPantalla(int ancho){
	this->ancho = ancho;
}

void VistaNivel::agregarTamanioNivel(double ancho,double largo){
	this->anchoNivel = ancho;
	this->altoNivel = alto;
	int dummy = 0;
	int altoReal = 0;
	int anchoReal = 0;
	Posicion::convertirTileAPixel(this->altoNivel, this->anchoNivel - 1, this->altoNivel - 1, dummy, altoReal);
	Posicion::convertirTileAPixel(this->altoNivel, this->anchoNivel - 1, 0, anchoReal, dummy);

	this->altoNivel += ALTO_TILE;
	this->anchoNivel += ANCHO_TILE / 2;
}

double VistaNivel::getAltoNivel(){
	return this->altoNivel;
}

double VistaNivel::getAnchoNivel(){
	return this->anchoNivel;
}

void VistaNivel::destruirListaEntidades(){
	// Destruyo las entidades instanciadas (incluye al personaje)
	for (std::list<VistaEntidad*>::iterator entidad = this->listaEntidades.begin(); entidad != this->listaEntidades.end(); entidad++){
		delete (*entidad);
	}
	return void();
}

void VistaNivel::destruirScroll(){
	// Destruyo el scroll
	if( this->scroll != NULL ) delete this->scroll;
	return void();
}

void VistaNivel::destruirEntidadesYScroll(){
	this->destruirListaEntidades();
	this->destruirScroll();
	return void();
}