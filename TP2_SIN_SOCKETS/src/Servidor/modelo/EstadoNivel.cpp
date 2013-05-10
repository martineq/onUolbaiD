#include "EstadoNivel.h"

using namespace std;

EstadoNivel::EstadoNivel(const EstadoNivel &estadoNivel) {
}

EstadoNivel& EstadoNivel::operator=(const EstadoNivel &estadoNivel) {
	return *this;
}

EstadoNivel::EstadoNivel(int alto, int ancho, int x, int y) {
	this->_alto = alto;
	this->_ancho = ancho;
	this->_posicion.x = x;
	this->_posicion.y = y;
	this->_nivel = new char[this->_alto * this->_ancho * sizeof(char)];
	memset(this->_nivel, NO_CONOCIDO, this->_alto * this->_ancho * sizeof(char));
}

EstadoNivel::~EstadoNivel() {
	delete[] this->_nivel;
}

void EstadoNivel::visitar(int x, int y) {
	int rangoVisible = ZONA_VISIBLE / 2;

	// Obtengo los limites de la submatriz que tengo que modificar
	int xDesde = (x < this->_posicion.x) ? x : this->_posicion.x;
	int yDesde = (y < this->_posicion.y) ? y : this->_posicion.y;
	int xHasta = (x > this->_posicion.x) ? x : this->_posicion.x;
	int yHasta = (y > this->_posicion.y) ? y : this->_posicion.y;
	
	xDesde -= rangoVisible;
	yDesde -= rangoVisible;
	xHasta += rangoVisible;
	yHasta += rangoVisible;

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
			// Si el tile esta dentro de la zona visible lo marco
			if ((i >= x - rangoVisible) && (i <= x + rangoVisible) && (j >= y - rangoVisible) && (j <= y + rangoVisible))
				this->_nivel[(this->_ancho * j) + i] = VISIBLE;
			else if (this->_nivel[(this->_ancho * j) + i] != NO_CONOCIDO)
				this->_nivel[(this->_ancho * j) + i] = CONOCIDO_NO_VISIBLE;
		}
	}

	this->_posicion.x = x;
	this->_posicion.y = y;

	//TODO: BORRAR!
	/*for (int j = 0; j < this->_ancho; j++) {
		for (int i = 0; i < this->_ancho; i++) {
			cout << (int)this->_nivel[(this->_ancho * j) + i];
		}
		cout << endl;
	}
	cout << "-----------------------------" << endl;*/
}

char EstadoNivel::visibilidad(int x, int y) {
	return this->_nivel[(this->_ancho * y) + x];
}
