#include "./VistaNivel.h"


VistaNivel::VistaNivel(){
	this->scroll = NULL;
	this->jugador = NULL;
}

VistaNivel::~VistaNivel(){
 // Los punteros ya son destruidos desde el Administrador
}

VistaScroll* VistaNivel::getScroll(void){
	return this->scroll;
}

VistaEntidad* VistaNivel::getJugador(void){
	return this->jugador;
}


std::list<VistaEntidad*> VistaNivel::getListaEntidades(void){
	return this->listaEntidades;
}

void VistaNivel::agregarJugador(VistaEntidad* pJugador){
	this->jugador = pJugador;
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

void VistaNivel::agregarTamanioNivel(double anchoNivel,double altoNivel){	
	int dummy = 0;
	int altoReal = 0;
	int anchoReal = 0;
	Posicion::convertirTileAPixel(altoNivel, anchoNivel - 1, altoNivel - 1, dummy, altoReal);
	Posicion::convertirTileAPixel(altoNivel, anchoNivel - 1, 0, anchoReal, dummy);

	altoReal += ALTO_TILE;
	anchoReal += ANCHO_TILE / 2;

	this->anchoNivel = anchoReal;
	this->altoNivel = altoReal;
}

double VistaNivel::getAltoNivel(){
	return this->altoNivel;
}

double VistaNivel::getAnchoNivel(){
	return this->anchoNivel;
}

void VistaNivel::destruirListaEntidades(){
	// Destruyo las entidades instanciadas (incluye al jugador)
	for (std::list<VistaEntidad*>::iterator entidad = this->listaEntidades.begin(); entidad != this->listaEntidades.end(); entidad++){
		delete (*entidad);
	}
	if( this->jugador != NULL ) delete this->jugador;
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