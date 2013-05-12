#include "ControladorScroll.h"

ControladorScroll::ControladorScroll(int pPantallaAncho, int pPantallaAlto, int tEscenarioAncho, int tEscenarioAlto, int tMargen, int personajeX, int personajeY) {
	this->pPantallaAncho = pPantallaAncho;
	this->pPantallaAlto = pPantallaAlto;
	this->tEscenarioAncho = tEscenarioAncho;
	this->tEscenarioAlto = tEscenarioAlto;

	this->margen = tMargen;
	
	this->desplazamientoX = 0;
	this->desplazamientoY = 0;

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

ControladorScroll::~ControladorScroll(){
}

int ControladorScroll::getX() {
	return this->x;
}

int ControladorScroll::getY() {
	return this->y;
}

int ControladorScroll::getAncho() {
	return this->pPantallaAncho;
}

int ControladorScroll::getAlto() {
	return this->pPantallaAlto;
}

int ControladorScroll::getMargen() {
	return this->margen;
}

void ControladorScroll::actualizar(int mouseX, int mouseY) {
	this->desplazamientoX = 0;
	if (this->pPantallaAncho < this->pEscenarioAncho) {
		if (mouseX <= this->margen) { // toco el margen izquierdo
			this->desplazamientoX = -VELOCIDAD_SCROLL;
		}
		else if (mouseX >= (this->pPantallaAncho - margen)) { // toco margen derecho
			this->desplazamientoX = VELOCIDAD_SCROLL;
		}
	}

	this->desplazamientoY = 0;
	if (this->pPantallaAlto < this->pEscenarioAlto) {
		if (mouseY  <= this->margen) { // toco el margen superior
			this->desplazamientoY = -VELOCIDAD_SCROLL;
		}
		else if (mouseY >= (this->pPantallaAlto - margen)) { // toco margen inferior
			this->desplazamientoY = VELOCIDAD_SCROLL;
		}
	}
}

void ControladorScroll::detener() {
	this->desplazamientoX = 0;
	this->desplazamientoY = 0;
}

void ControladorScroll::cambiarEstado() {
	if ((this->desplazamientoX == 0) && (this->desplazamientoY == 0))
		return;

	int xAnterior = this->x, yAnterior = this->y;

	this->x += this->desplazamientoX;
	this->y += this->desplazamientoY;

	if (this->x + this->pPantallaAncho > this->pEscenarioAncho)
		this->x = this->pEscenarioAncho - this->pPantallaAncho;
	if (this->x < 0)
		this->x = 0;

	if (this->y + this->pPantallaAlto > this->pEscenarioAlto)
		this->y = this->pEscenarioAlto - this->pPantallaAlto;
	if (this->y < 0)
		this->y = 0;

	Posicion tileFoco;
	Posicion::convertirPixelATile(this->tEscenarioAlto, this->x + (this->pPantallaAncho / 2), this->y + (this->pPantallaAlto / 2), tileFoco.x, tileFoco.y);
	
	if ((tileFoco.x < 0) || (tileFoco.x >= this->tEscenarioAncho) || (tileFoco.y < 0) || (tileFoco.y >= this->tEscenarioAlto)) {
		this->x = xAnterior;
		this->y = yAnterior;
	}

	if ((this->x != xAnterior) || (this->y != yAnterior))
		this->notificarObservadores();
}
