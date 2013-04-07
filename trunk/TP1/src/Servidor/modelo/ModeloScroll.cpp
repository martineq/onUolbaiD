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
	std::cout << pEscenarioAlto << " - " << tEscenarioAlto << std::endl;
	std::cout << pEscenarioAncho << " - " << tEscenarioAncho <<std::endl;

	//La idea es que el personaje arranque en el medio de la pantalla
	//Posicion::convertirTileAPixel(this->tEscenarioAlto, personajeX, personajeY, this->x, this->y);
	//this->x -= floor((double)(this->pPantallaAncho / 2));
	//if (this->x < 0) {
	//	this->x =0;
	//}

	//this->y -= floor((double)(this->pPantallaAlto / 2));
	//if (this->y < 0) {
	//	this->y =0;
	//}
	this->x = 0;
	this->y = 0;

}

ModeloScroll::~ModeloScroll(void){
}

bool ModeloScroll::calcularPosicion(int mouseX, int mouseY) {
	bool chg = false;
	
	/*int maxX = 10*this->tEscenarioAncho;
	int maxY = 10*this->tEscenarioAlto;*/

	if (mouseX <= this->margen) { // toco el margen izquierdo
		if (this->x - velocidad <= 0) {
			this->x = 0;
		} else {
			this->x -= velocidad;
		}
		chg = true;
	} else if (mouseX >= (this->pPantallaAncho - margen)) { // toco margen derecho
		if (this->x + velocidad >= this->pEscenarioAncho) {
			this->x = this->pEscenarioAncho;
		} else {
			this->x += velocidad;
		}
		std::cout << "X=" << this->x << std::endl;
		/*this->x +=velocidad;*/
		chg = true;
	}

	
	if (mouseY  <= this->margen) { // toco el margen superior
		if (this->y - velocidad <= 0) {
			this->y = 0;
		} else {
			this->y -= velocidad;
		}
		chg = true;
	} else if (mouseY >= (this->pPantallaAlto - margen)) { // toco margen inferior
		if (this->y + velocidad >= this->pEscenarioAlto) {
			this->y = this->pEscenarioAlto;
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