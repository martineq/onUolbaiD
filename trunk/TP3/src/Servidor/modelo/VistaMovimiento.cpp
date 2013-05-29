#include "ModeloJugador.h"

using namespace std;

VistaMovimiento::VistaMovimiento(const VistaMovimiento &modeloMovimiento) {
}

VistaMovimiento& VistaMovimiento::operator=(const VistaMovimiento &modeloMovimiento) {
	return *this;
}

VistaMovimiento::VistaMovimiento(ModeloEntidad* modeloEntidad, int altoMapa, int anchoMapa, int fps) {
	this->_modeloEntidad = modeloEntidad;
	this->_altoMapa = altoMapa;
	this->_anchoMapa = anchoMapa;	
	this->_cantidadCuadros = (this->_modeloEntidad->velocidad() * fps) / 1000;
	
	// Si la cantidad de cuadros a mostrar es 0 al menos muestro el cuadro final
	if (this->_cantidadCuadros == 0)
		this->_cantidadCuadros = 1;

	this->_espera = this->_modeloEntidad->velocidad() / this->_cantidadCuadros;

	this->_cuadroActual = this->_cantidadCuadros + 1;
	this->_instanteUltimoCambioEstado = 0;
}

VistaMovimiento::~VistaMovimiento() {
}

void VistaMovimiento::actualizar(Observable* observable) {
	ModeloMovimiento* modeloMovimiento = (ModeloMovimiento*)observable;

	// Calcula posiciones en pixeles
	Posicion::convertirTileAPixel(this->_altoMapa, this->_modeloEntidad->posicion().x, this->_modeloEntidad->posicion().y, this->_posicionOrigen.x, this->_posicionOrigen.y);
	Posicion::convertirTileAPixel(this->_altoMapa, modeloMovimiento->posicionSiguiente().x, modeloMovimiento->posicionSiguiente().y, this->_posicionDestino.x, this->_posicionDestino.y);

	// Calcula desplazamientos
	int deltaX = abs(this->_posicionDestino.x - this->_posicionOrigen.x);
	int deltaY = abs(this->_posicionDestino.y - this->_posicionOrigen.y);
	int desplazamientoX = (this->_posicionOrigen.x < this->_posicionDestino.x) ? 1 : -1;
	int desplazamientoY = (this->_posicionOrigen.y < this->_posicionDestino.y) ? 1 : -1;
	int error = (deltaX >= deltaY) ? deltaX : deltaY;
	int desplazamientoErrorX = 2 * deltaX;
	int desplazamientoErrorY = 2 * deltaY;
	Posicion posicionActual = this->_posicionOrigen;

	this->_posiciones.clear();

	// Obtiene el camino pixel por pixel
	while (posicionActual != this->_posicionDestino) {
		posicionActual.x += (deltaX >= deltaY) ? desplazamientoX : 0;
		posicionActual.y += (deltaX >= deltaY) ? 0 : desplazamientoY;
		error += (deltaX >= deltaY) ? desplazamientoErrorY : desplazamientoErrorX; 
		
		if (deltaX >= deltaY) {
			if (error > desplazamientoErrorX) {
				posicionActual.y += desplazamientoY; 
				error -= desplazamientoErrorX; 
			}
		}
		else {
			if (error > desplazamientoErrorY) {
				posicionActual.x += desplazamientoX;
				error -= desplazamientoErrorY;
			}
		}

		this->_posiciones.push_back(posicionActual);
	}

	this->_desplazamiento = this->_posiciones.size() / this->_cantidadCuadros;
	this->_cuadroActual = 0;
}

void VistaMovimiento::cambiarEstado() {
	if (this->_cuadroActual > this->_cantidadCuadros)
		return;

	if (this->_instanteUltimoCambioEstado == 0) {
		this->_instanteUltimoCambioEstado = GetTickCount();
		return;
	}
	
	if (this->_espera > (GetTickCount() - this->_instanteUltimoCambioEstado))
		return;

	Posicion pixelSiguiente;
	this->_modeloEntidad->esUltimoMovimiento(this->_cuadroActual == this->_cantidadCuadros);

	if (this->_modeloEntidad->esUltimoMovimiento()) {
		pixelSiguiente = this->_posicionDestino;
	}
	else {
		list<Posicion>::iterator iterador = this->_posiciones.begin();
		advance(iterador, this->_cuadroActual * this->_desplazamiento);
		pixelSiguiente = *iterador;
	}

	this->_modeloEntidad->pixel(pixelSiguiente);
	this->_modeloEntidad->notificar(true);
	
	this->_cuadroActual++;
	this->_instanteUltimoCambioEstado = GetTickCount();
}

bool VistaMovimiento::terminado() const {
	return this->_cuadroActual > this->_cantidadCuadros;
}
