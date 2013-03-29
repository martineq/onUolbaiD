#include "ModeloScroll.h"

ModeloScroll::ModeloScroll(int tAncho, int tAlto, int tMargen, int tVelocidad, class Observable *m){
	x = 0;
	y = 0;
	ancho = tAncho;
	alto = tAlto;
	margen = tMargen;
	velocidad = tVelocidad;

	//m->agregarObservador(this);
}

ModeloScroll::~ModeloScroll(void){
}

void ModeloScroll::calcularPosicion(int mouseX, int mouseY) {
	if (mouseX <= this->margen) { // toco el margen izquierdo
		if (this->x - velocidad <= 0) {
			this->x = 0;
		} else {
			this->x -= velocidad;
		}
	} else if (mouseX >= (this->ancho - margen)) { // toco margen derecho
		if (this->x + velocidad >= PANTALLA_ANCHO) {
			this->x = PANTALLA_ANCHO;
		} else {
			this->x += velocidad;
		}
	}

	
	if (mouseY  <= this->margen) { // toco el margen superior
		if (this->y - velocidad <= 0) {
			this->y = 0;
		} else {
			this->y -= velocidad;
		}
	} else if (mouseY >= (this->alto - margen)) { // toco margen inferior
		if (this->y + velocidad >= PANTALLA_ALTO) {
			this->y = PANTALLA_ANCHO;
		} else {
			this->y += velocidad;
		}
	}
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

void ModeloScroll::cambiarEstado(){
	this->notificarObservadores();
}
