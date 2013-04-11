#include "ModeloScroll.h"

ModeloScroll::ModeloScroll(int pPantallaAncho, int pPantallaAlto, int tEscenarioAncho, int tEscenarioAlto, int tMargen, int tVelocidad, int personajeX, int personajeY, int idPersonaje) {
	
	this->pPantallaAncho = pPantallaAncho;
	this->pPantallaAlto = pPantallaAlto;
	this->tEscenarioAncho = tEscenarioAncho;
	this->tEscenarioAlto = tEscenarioAlto;

	this->margen = tMargen;
	this->velocidad = tVelocidad;
	
	this->id = idPersonaje;

	int dummy;
	Posicion::convertirTileAPixel(tEscenarioAlto, tEscenarioAncho - 1, tEscenarioAlto - 1, dummy, pEscenarioAlto); 
	Posicion::convertirTileAPixel(tEscenarioAlto, tEscenarioAncho - 1, 0, pEscenarioAncho, dummy);

	pEscenarioAlto += ALTO_TILE;
	pEscenarioAncho += ANCHO_TILE / 2;

	std::cout << pEscenarioAlto << " - " << tEscenarioAlto << std::endl;
	std::cout << pEscenarioAncho << " - " << tEscenarioAncho <<std::endl;

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

	std::cout << "(" << this->x << "," << this->y << ")" << std::endl;
}

ModeloScroll::~ModeloScroll(void){
}

bool ModeloScroll::calcularPosicion(int mouseX, int mouseY) {
	bool chg = false;
	
	/*int maxX = 10*this->tEscenarioAncho;
	int maxY = 10*this->tEscenarioAlto;*/

	if (mouseX <= this->margen) { // toco el margen izquierdo
		this->x -= velocidad;
		chg = true;
	} else if (mouseX >= (this->pPantallaAncho - margen)) { // toco margen derecho
		this->x += velocidad;
		chg = true;
	}

	if (this->x < 0)
		this->x = 0;
	else if (this->x + this->pPantallaAncho > this->pEscenarioAncho)
		this->x = this->pEscenarioAncho - this->pPantallaAncho;

	if (mouseY  <= this->margen) { // toco el margen superior
		this->y -= velocidad;
		chg = true;
	} else if (mouseY >= (this->pPantallaAlto - margen)) { // toco margen inferior
		this->y += velocidad;
		chg = true;
	}

	if (this->y < 0)
		this->y = 0;
	else if (this->y + this->pPantallaAlto > this->pEscenarioAlto)
		this->y = this->pEscenarioAlto - this->pPantallaAlto;

	return chg;
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
	if (this->calcularPosicion(mouseX, mouseY)) {
		this->cambiarEstado();
	}
}

void ModeloScroll::cambiarEstado(){
	this->notificarObservadores();
}

//Comentado porque se va a usar el agregarObservador de la interfaz
/*void ModeloScroll::agregarObservador(Observador *m) {
	this->observadores.push_back(m);

}*/

//Comentado porque habría que implementar removerObservador en la interfaz
/*void ModeloScroll::removerObservador(Observador *m) {
	this->observadores.remove(m);

}*/

int ModeloScroll::obtenerId(void){	// Para el ID
    return (this->id);
}

bool ModeloScroll::enMargen(int x, int y) {
	if ((x <= this->margen) || (x >= (this->pPantallaAncho - margen)) || (y  <= this->margen) || (y >= (this->pPantallaAlto - margen))){
		return true;
	} else {
		return false;
	}
}