#include "./VistaNivel.h"

bool VistaNivel::ordenadorEntidades(VistaEntidad* entidad1, VistaEntidad* entidad2) {
	Posicion posicion1, posicion2;

	posicion1.x = entidad1->getTileXAnterior() + (entidad1->getAncho() / ANCHO_TILE) - 1;
	posicion1.y = entidad1->getTileYAnterior() + (entidad1->getAlto() / ALTO_TILE) - 1;
	posicion2.x = entidad2->getTileXAnterior() + (entidad2->getAncho() / ANCHO_TILE) - 1;
	posicion2.y = entidad2->getTileYAnterior() + (entidad2->getAlto() / ALTO_TILE) - 1;

	if (posicion1 == posicion2)
		return entidad1->id() < entidad2->id();
	else
		return posicion1 < posicion2;
}

VistaNivel::VistaNivel(){
	this->scroll = NULL;
	this->jugador = NULL;
	this->pngBomba = NULL;
	this->pngMagia = NULL;
	this->pngGolem = NULL;
}

VistaNivel::~VistaNivel(){
 // Los punteros ya son destruidos desde el Administrador
	if (this->pngBomba != NULL) SDL_FreeSurface ( this->pngBomba );
	if (this->pngMagia != NULL) SDL_FreeSurface ( this->pngMagia );
	if (this->pngGolem != NULL)
		SDL_FreeSurface ( this->pngGolem );	
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

std::list<VistaEntidad*> VistaNivel::getListaOtrosJugadores(void){
	return this->listaOtrosJugadores;
}

void VistaNivel::agregarJugador(VistaEntidad* pJugador){
	this->jugador = pJugador;
	this->agregarOtroJugador(pJugador);
}

void VistaNivel::agregarOtroJugador(VistaEntidad* pJugador){
	this->listaOtrosJugadores.push_back(pJugador);
	this->ordenarJugadores();
}

void VistaNivel::agregarEntidad(VistaEntidad* pEntidad){
	this->listaEntidades.push_back(pEntidad);
	this->listaEntidades.sort(VistaNivel::ordenadorEntidades);
}

void VistaNivel::agregarScroll(VistaScroll* pScroll){
	this->scroll = pScroll;
	return void();
}

void VistaNivel::setControladorScroll(ControladorScroll* pControladorScroll){
	this->pControladorScroll = pControladorScroll;
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

void VistaNivel::ordenarJugadores() {
	this->listaOtrosJugadores.sort(VistaNivel::ordenadorEntidades);
}

void VistaNivel::reiniciarPosicionScroll() {
	this->pControladorScroll->setPosicionInicial();
	return void();
}

SDL_Surface* VistaNivel::getPngBomba(){
	return this->pngBomba;
}

SDL_Surface* VistaNivel::getPngMagia(){
	return this->pngMagia;
}

SDL_Surface* VistaNivel::getPngGolem(){
	return this->pngGolem;
}

void VistaNivel::setPngBomba(SDL_Surface* png){
	this->pngBomba = png;
}

void VistaNivel::setPngMagia(SDL_Surface* png){
	this->pngMagia = png;
}

void VistaNivel::setPngGolem(SDL_Surface* png){
	this->pngGolem = png;
}