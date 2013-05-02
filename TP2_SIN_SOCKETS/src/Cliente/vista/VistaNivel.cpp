#include "./VistaNivel.h"

bool VistaNivel::ordenadorEntidades(VistaEntidad* entidad1, VistaEntidad* entidad2) {
	Posicion posicion1, posicion2;

	posicion1.x = entidad1->getTileX() + (entidad1->getAncho() / ANCHO_TILE) - 1;
	posicion1.y = entidad1->getTileY() + (entidad1->getAlto() / ALTO_TILE) - 1;
	posicion2.x = entidad2->getTileX() + (entidad2->getAncho() / ANCHO_TILE) - 1;
	posicion2.y = entidad2->getTileY() + (entidad2->getAlto() / ALTO_TILE) - 1;

	if (posicion1 == posicion2)
		return entidad1->id() < entidad2->id();
	else
		return posicion1 < posicion2;
}

VistaNivel::VistaNivel(){
	this->scroll = NULL;
	this->jugador = NULL;
}

VistaNivel::~VistaNivel(){
 // Los punteros ya son destruidos desde el Administrador
}

Observador* VistaNivel::obtenerObservadorJugador(void){
	return (Observador*)this->jugador;
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

VistaEntidad* VistaNivel::getJugador(void){
	return this->jugador;
}


std::list<VistaEntidad*> VistaNivel::getListaEntidades(void){
	return this->listaEntidades;
}

void VistaNivel::agregarJugador(VistaEntidad* pJugador){
	this->jugador = pJugador;
}

void VistaNivel::agregarEntidad(VistaEntidad* pEntidad){
	this->listaEntidades.push_back(pEntidad);
	this->listaEntidades.sort(VistaNivel::ordenadorEntidades);
}

void VistaNivel::agregarScroll(VistaScroll* pScroll){
	this->scroll = pScroll;
	return void();
}

int VistaNivel::getAltoDePantallaEnPixel(void){
	return this->altoDePantallaEnPixel;
}

int VistaNivel::getAnchoDePantallaEnPixel(void){
	return this->anchoDePantallaEnPixel;
}

void VistaNivel::setAltoDePantallaEnPixel(int alto){
	this->altoDePantallaEnPixel = alto;
}

void VistaNivel::setAnchoDePantallaEnPixel(int ancho){
	this->anchoDePantallaEnPixel = ancho;
}

void VistaNivel::setAltoDeNivelEnTiles(int alto){
	this->altoDeNivelEnTiles = alto;
}

void VistaNivel::setAnchoDeNivelEnTiles(int ancho){
	this->anchoDeNivelEnTiles = ancho;
}

void VistaNivel::agregarTamanioNivel(double anchoNivel,double altoNivel){	
	int dummy = 0;
	int altoReal = 0;
	int anchoReal = 0;
	Posicion::convertirTileAPixel(altoNivel, anchoNivel - 1, altoNivel - 1, dummy, altoReal);
	Posicion::convertirTileAPixel(altoNivel, anchoNivel - 1, 0, anchoReal, dummy);

	altoReal += ALTO_TILE;
	anchoReal += ANCHO_TILE / 2;

	this->anchoNivelEnPixel = anchoReal;
	this->altoNivelEnPixel = altoReal;
	this->altoDeNivelEnTiles = altoNivel;
	this->anchoDeNivelEnTiles = anchoNivel;
}

double VistaNivel::getAltoDeNivelEnPixel(){
	return this->altoNivelEnPixel;
}

double VistaNivel::getAnchoDeNivelEnPixel(){
	return this->anchoNivelEnPixel;
}

int VistaNivel::getAltoDeNivelEnTiles(){
	return this->altoDeNivelEnTiles;
}

int VistaNivel::getAnchoDeNivelEnTiles(){
	return this->anchoDeNivelEnTiles;
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