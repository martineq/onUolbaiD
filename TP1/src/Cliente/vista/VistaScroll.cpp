#include "VistaScroll.h"

long VistaScroll::contador = 0; // Para el ID

VistaScroll::VistaScroll(double x,double y,double alto,double ancho, double anchoNivel, double altoNivel, SDL_Surface* pantalla){
	this->_id = (int)InterlockedIncrement(&(this->contador));  // Genera un ID
	this->x = x;
	this->y = y;
	this->alto = alto;
	this->ancho = ancho;
	this->altoNivel = altoNivel;
	this->anchoNivel = anchoNivel;
	this->esNecesarioRefrescar = true;
	this->utilidadSDL = new SDLutil(0, 0, ANCHO_TILE, ALTO_TILE, SDL_RUTA_UTIL);
	this->utilidadSDL->setPantalla(pantalla);
}

VistaScroll::~VistaScroll(void){

}

int VistaScroll::id() const {
    return this->_id;
}

void VistaScroll::actualizar(class Observable* s){

	// En este punto ya se que el parámetro <s> se puede castear a ((ModeloScroll*)s)

	// TODO: Ver si están todos los métodos necesarios
	this->x = ((ModeloScroll*)s)->getX();
	this->y = ((ModeloScroll*)s)->getY();	
	this->obtenerTilesLimites(this->posicionInicial,this->posicionFinal);
	this->esNecesarioRefrescar = true;

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

void VistaScroll::obtenerTilesLimites(Posicion& posicionInicial, Posicion& posicionFinal) {
	Posicion posicion1, posicion2, posicion3, posicion4;

	Posicion::convertirPixelATile(this->altoNivel, this->x, this->y, posicion1.x, posicion1.y);
	Posicion::convertirPixelATile(this->altoNivel, this->x + this->ancho, this->y, posicion2.x, posicion2.y);
	Posicion::convertirPixelATile(this->altoNivel, this->x, this->y + this->alto, posicion3.x, posicion3.y);
	Posicion::convertirPixelATile(this->altoNivel, this->x + this->ancho, this->y + this->alto, posicion4.x, posicion4.y);

	posicionInicial.x = posicion1.x;
	if (posicionInicial.x > posicion2.x)
		posicionInicial.x = posicion2.x;
	if (posicionInicial.x > posicion3.x)
		posicionInicial.x = posicion3.x;
	if (posicionInicial.x > posicion4.x)
		posicionInicial.x = posicion4.x;

	posicionInicial.y = posicion1.y;
	if (posicionInicial.y > posicion2.y)
		posicionInicial.y = posicion2.y;
	if (posicionInicial.y > posicion3.y)
		posicionInicial.y = posicion3.y;
	if (posicionInicial.y > posicion4.y)
		posicionInicial.y = posicion4.y;

	if (posicionInicial.x < 0)
		posicionInicial.x = 0;
	if (posicionInicial.y < 0)
		posicionInicial.y = 0;

	posicionFinal.x = posicionFinal.x;
	if (posicionFinal.x < posicion2.x)
		posicionFinal.x = posicion2.x;
	if (posicionFinal.x < posicion3.x)
		posicionFinal.x = posicion3.x;
	if (posicionFinal.x < posicion4.x)
		posicionFinal.x = posicion4.x;

	posicionFinal.y = posicion1.y;
	if (posicionFinal.y < posicion2.y)
		posicionFinal.y = posicion2.y;
	if (posicionFinal.y < posicion3.y)
		posicionFinal.y = posicion3.y;
	if (posicionFinal.y < posicion4.y)
		posicionFinal.y = posicion4.y;

	posicionFinal.x++;
	posicionFinal.y++;

	if (posicionFinal.x > this->anchoNivel)
		posicionFinal.x = this->anchoNivel;
	if (posicionFinal.y > this->altoNivel)
		posicionFinal.y = this->altoNivel;	
}

void VistaScroll::graficar(SDL_Surface* pantalla) {
	int xt = 0, yt = 0, xp = 0, yp = 0;	
	//if (this->esNecesarioRefrescar == true) {
		this->obtenerTilesLimites(this->posicionInicial, this->posicionFinal);

		ImageLoader::getInstance().blanquearPantalla(pantalla);

		for (xt = this->posicionInicial.x; xt < this->posicionFinal.x; xt++) {
			for (yt = posicionInicial.y; yt < posicionFinal.y; yt++) {
				Posicion::convertirTileAPixel(this->altoNivel, xt, yt, xp, yp);				
				
				this->utilidadSDL->graficar(xp - this->x - (ANCHO_TILE / 2), yp - this->y);
			}
		}
		//this->esNecesarioRefrescar = false;
	//}
					
	//ImageLoader::getInstance().refrescarPantalla(pantalla);
}