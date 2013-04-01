#include "ModeloScroll.h"


long ModeloScroll::contador = 0; // Para el ID

ModeloScroll::ModeloScroll(int tAncho, int tAlto, int tMargen, int tVelocidad){

	x = 0;
	y = 0;
	ancho = tAncho;
	alto = tAlto;
	margen = tMargen;
	velocidad = tVelocidad;

	this->id = (int)InterlockedIncrement(&(this->contador));  // Genera un ID
	
	
}

ModeloScroll::~ModeloScroll(void){
}

bool ModeloScroll::calcularPosicion(int mouseX, int mouseY) {
	bool chg = false;
	
	if (mouseX <= this->margen) { // toco el margen izquierdo
		if (this->x - velocidad <= 0) {
			this->x = 0;
		} else {
			this->x -= velocidad;
		}
		chg = true;
	} else if (mouseX >= (this->ancho - margen)) { // toco margen derecho
		if (this->x + velocidad >= this->ancho) {
			this->x = this->ancho;
		} else {
			this->x += velocidad;
		}
		chg = true;
	}

	
	if (mouseY  <= this->margen) { // toco el margen superior
		if (this->y - velocidad <= 0) {
			this->y = 0;
		} else {
			this->y -= velocidad;
		}
		chg = true;
	} else if (mouseY >= (this->alto - margen)) { // toco margen inferior
		if (this->y + velocidad >= this->alto) {
			this->y = this->alto;
		} else {
			this->y += velocidad;
		}
		chg = true;
	}

	return chg;
}

int ModeloScroll::getX() {
	return this->x;
}

int ModeloScroll::getY() {
	return this->y;
}

int ModeloScroll::getAncho() {
	return this->ancho;
}

void ModeloScroll::setAncho(int nuevoAncho) {
	this->ancho = nuevoAncho;
}

void ModeloScroll::setAlto(int nuevoAlto) {
	this->alto = nuevoAlto;
}

int ModeloScroll::getAlto() {
	return this->alto;
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
	//this->notificarObservadores();
}


void ModeloScroll::agregarObservador(Observador *m) {
	this->observadores.push_back(m);
}

void ModeloScroll::removerObservador(Observador *m) {
	this->observadores.remove(m);
}

int ModeloScroll::obtenerId(void){	// Para el ID
    return (this->id);
}
