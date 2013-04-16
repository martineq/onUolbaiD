#include "ModeloScroll.h"

ModeloScroll::ModeloScroll(int pPantallaAncho, int pPantallaAlto, int tEscenarioAncho, int tEscenarioAlto, int tMargen, int personajeX, int personajeY, int idPersonaje) {
	
	this->pPantallaAncho = pPantallaAncho;
	this->pPantallaAlto = pPantallaAlto;
	this->tEscenarioAncho = tEscenarioAncho;
	this->tEscenarioAlto = tEscenarioAlto;

	this->margen = tMargen;
	
	this->desplazamientoX = 0;
	this->desplazamientoY = 0;

	this->_id = idPersonaje;

	int dummy;
	Posicion::convertirTileAPixel(tEscenarioAlto, tEscenarioAncho - 1, tEscenarioAlto - 1, dummy, pEscenarioAlto); 
	Posicion::convertirTileAPixel(tEscenarioAlto, tEscenarioAncho - 1, 0, pEscenarioAncho, dummy);

	pEscenarioAlto += ALTO_TILE;
	pEscenarioAncho += ANCHO_TILE / 2;

	//La idea es que el personaje arranque en el medio de la pantalla
	Posicion::convertirTileAPixel(this->tEscenarioAlto, personajeX, personajeY, this->x, this->y);
	
	this->x -= this->pPantallaAncho / 2;
	if (this->x < 0) {
		this->x = 0;
	}

	this->y -= this->pPantallaAlto / 2;
	if (this->y < 0) {
		this->y =0;
	}
}

ModeloScroll::~ModeloScroll(){
}

int ModeloScroll::getX() {
	return this->x;
}

int ModeloScroll::getY() {
	return this->y;
}

int ModeloScroll::getAncho() {
	return this->pPantallaAncho;
}

void ModeloScroll::setAncho(int nuevoAncho) {
	this->pPantallaAncho = nuevoAncho;
}

void ModeloScroll::setAlto(int nuevoAlto) {
	this->pPantallaAlto = nuevoAlto;
}

int ModeloScroll::getAlto() {
	return this->pPantallaAlto;
}

int ModeloScroll::getMargen() {
	return this->margen;
}

void ModeloScroll::actualizar(int mouseX, int mouseY) {
	this->desplazamientoX = 0;
	if (mouseX <= this->margen) { // toco el margen izquierdo
		this->desplazamientoX = -VELOCIDAD_SCROLL;
	}
	else if (mouseX >= (this->pPantallaAncho - margen)) { // toco margen derecho
		this->desplazamientoX = VELOCIDAD_SCROLL;
	}

	this->desplazamientoY = 0;
	if (mouseY  <= this->margen) { // toco el margen superior
		this->desplazamientoY = -VELOCIDAD_SCROLL;
	}
	else if (mouseY >= (this->pPantallaAlto - margen)) { // toco margen inferior
		this->desplazamientoY = VELOCIDAD_SCROLL;
	}
}

void ModeloScroll::cambiarEstado() {
	if ((this->desplazamientoX == 0) && (this->desplazamientoY == 0))
		return;
	this->x += this->desplazamientoX;
	this->y += this->desplazamientoY;

	if (this->x < 0)
		this->x = 0;
	else if (this->x + this->pPantallaAncho > this->pEscenarioAncho)
		this->x = this->pEscenarioAncho - this->pPantallaAncho;

	if (this->y < 0)
		this->y = 0;
	else if (this->y + this->pPantallaAlto > this->pEscenarioAlto)
		this->y = this->pEscenarioAlto - this->pPantallaAlto;

	this->notificarObservadores();
}

int ModeloScroll::id() const {
    return this->_id;
}

void ModeloScroll::notificarPosicionInicial() {
	this->notificarObservadores();
}
