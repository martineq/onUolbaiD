#include "EstadoNivel.h"

using namespace std;

EstadoNivel::EstadoNivel(const EstadoNivel &estadoNivel) {
}

EstadoNivel& EstadoNivel::operator=(const EstadoNivel &estadoNivel) {
	return *this;
}

EstadoNivel::EstadoNivel(int alto, int ancho, int x, int y, int rangoVision) {
	this->_alto = alto;
	this->_ancho = ancho;
	this->_posicion.x = x;
	this->_posicion.y = y;
	this->_rangoVision = rangoVision;
	this->tieneMapa = false;
	this->_nivel = new char[this->_alto * this->_ancho * sizeof(char)];
	memset(this->_nivel, NO_CONOCIDO, this->_alto * this->_ancho * sizeof(char));
}

EstadoNivel::~EstadoNivel() {
	delete[] this->_nivel;
}

int EstadoNivel::rangoVision() {
	return this->_rangoVision;
}

void EstadoNivel::rangoVision(int rangoVision) {
	this->_rangoVision = rangoVision;
	this->visitar(this->_posicion.x, this->_posicion.y);
}

void EstadoNivel::visitar(int x, int y) {
	int xDesde = (x < this->_posicion.x) ? x : this->_posicion.x;
	int yDesde = (y < this->_posicion.y) ? y : this->_posicion.y;
	int xHasta = (x > this->_posicion.x) ? x : this->_posicion.x;
	int yHasta = (y > this->_posicion.y) ? y : this->_posicion.y;
	
	xDesde -= this->_rangoVision;
	yDesde -= this->_rangoVision;
	xHasta += this->_rangoVision;
	yHasta += this->_rangoVision;

	// Ajusto los rangos dentro del nivel
	if (xDesde < 0)
		xDesde = 0;
	if (yDesde < 0)
		yDesde = 0;
	if (xHasta > this->_ancho - 1)
		xHasta = this->_ancho - 1;
	if (yHasta > this->_alto - 1)
		yHasta = this->_alto - 1;

	for (int i = xDesde; i <= xHasta; i++) {
		for (int j = yDesde; j <= yHasta; j++) {
			// Si el tile esta dentro del rango visible lo marco
			if ((i >= x - this->_rangoVision) && (i <= x + this->_rangoVision) && (j >= y - this->_rangoVision) && (j <= y + this->_rangoVision))
				this->_nivel[(this->_ancho * j) + i] = VISIBLE;
			else if (this->_nivel[(this->_ancho * j) + i] != NO_CONOCIDO)
				this->_nivel[(this->_ancho * j) + i] = CONOCIDO_NO_VISIBLE;
		}
	}

	this->_posicion.x = x;
	this->_posicion.y = y;
}

void EstadoNivel::setTieneMapa(bool loTiene){
	this->tieneMapa = loTiene;
}

bool EstadoNivel::getTieneMapa(){
	return this->tieneMapa;
}

char EstadoNivel::visibilidad(int x, int y) {
	if (this->tieneMapa) {
	 if ( (this->_nivel[(this->_ancho * y) + x]) == NO_CONOCIDO )
		 return CONOCIDO_NO_VISIBLE;
	 else
		 return this->_nivel[(this->_ancho * y) + x];
	}
	else
		return this->_nivel[(this->_ancho * y) + x];
}

string EstadoNivel::getMatriz() {
	std::string matriz(this->_nivel, this->_alto * this->_ancho);
	return matriz;
}

void EstadoNivel::setMatriz(std::string mapa){
	for (int i = 0; i < this->_alto; i++) {
		for (int j = 0; j < this->_ancho; j++) {
			int fila = i * this->_ancho;
			this->_nivel[j + fila] = mapa[fila + j];
		}	
	}
}

int EstadoNivel::getAlto(){
	return this->_alto;
}

int EstadoNivel::getAncho(){
	return this->_ancho;
}