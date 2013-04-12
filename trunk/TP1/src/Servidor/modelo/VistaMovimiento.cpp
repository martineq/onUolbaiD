#include "ModeloEntidad.h"

using namespace std;

Direccion ModeloEntidad::VistaMovimiento::obtenerDireccion(Posicion posicionOrigen, Posicion posicionDestino) {
	if (posicionOrigen.x > posicionDestino.x) {
		if (posicionOrigen.y > posicionDestino.y)
			return NOROESTE;
		else if (posicionOrigen.y < posicionDestino.y)
			return SUDOESTE;
		else
			return OESTE;
	}
	else if (posicionOrigen.x < posicionDestino.x)
		if (posicionOrigen.y > posicionDestino.y)
			return NORESTE;
		else if (posicionOrigen.y < posicionDestino.y)
			return SUDESTE;
		else
			return ESTE;
	else {
		if (posicionOrigen.y > posicionDestino.y)
			return NORTE;
		else if (posicionOrigen.y < posicionDestino.y)
			return SUR;
		else
			return CENTRO;
	}
}

ModeloEntidad::VistaMovimiento::VistaMovimiento(const VistaMovimiento &modeloMovimiento) {
}

ModeloEntidad::VistaMovimiento& ModeloEntidad::VistaMovimiento::operator=(const VistaMovimiento &modeloMovimiento) {
	return *this;
}

ModeloEntidad::VistaMovimiento::VistaMovimiento(ModeloEntidad* modeloEntidad, int altoMapa, int anchoMapa, int fps) {
	this->_modeloEntidad = modeloEntidad;
	this->_altoMapa = altoMapa;
	this->_anchoMapa = anchoMapa;
	this->_fps = fps;
}

ModeloEntidad::VistaMovimiento::~VistaMovimiento() {
}

void ModeloEntidad::VistaMovimiento::actualizar(Observable* observable) {
	Posicion posicionOrigen, posicionDestino, posicionActual;
	int deltaX, deltaY, desplazamientoX, desplazamientoY, error, desplazamientoErrorX, desplazamientoErrorY;
	list<Posicion> posiciones;

	// Calcula posiciones en pixeles
	Posicion::convertirTileAPixel(this->_altoMapa, this->_modeloEntidad->posicionActual().x, this->_modeloEntidad->posicionActual().y, posicionOrigen.x, posicionOrigen.y);
	Posicion::convertirTileAPixel(this->_altoMapa, this->_modeloEntidad->posicionSiguiente().x, this->_modeloEntidad->posicionSiguiente().y, posicionDestino.x, posicionDestino.y);
	posicionActual = posicionOrigen;

	// Calcula desplazamientos
	deltaX = abs(posicionDestino.x - posicionOrigen.x);
	deltaY = abs(posicionDestino.y - posicionOrigen.y);
	desplazamientoX = (posicionOrigen.x < posicionDestino.x) ? 1 : -1;
	desplazamientoY = (posicionOrigen.y < posicionDestino.y) ? 1 : -1;
	error = (deltaX >= deltaY) ? deltaX : deltaY;
	desplazamientoErrorX = 2 * deltaX;
	desplazamientoErrorY = 2 * deltaY;
	
	// Obtiene el camino pixel por pixel
	while (posicionActual != posicionDestino) {
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

		posiciones.push_back(posicionActual);
	}

	// Calcula la cantida de cuadros a mostrar y la duracion de cada uno
	list<Posicion>::iterator iterador = posiciones.begin();
	int cuadros = (this->_modeloEntidad->velocidad() * this->_fps) / 1000;
	
	// Si la cantidad de cuadros a mostrar es 0 al menos muestro el cuadro final
	if (cuadros == 0)
		cuadros = 1;
	
	int desplazamiento = posiciones.size() / cuadros;
	DWORD espera = this->_modeloEntidad->velocidad() / cuadros;

	// Recorre la lista de pixeles salteando segun la cantidad de cuadros, sin tener en cuenta el ultimo
	this->_modeloEntidad->_pixelActual = posicionOrigen;
	for (int i = 0; i < cuadros - 1; i++) {
		advance(iterador, desplazamiento);
		this->_modeloEntidad->_pixelSiguiente = *iterador;
		this->_modeloEntidad->_direccion = this->obtenerDireccion(this->_modeloEntidad->_pixelActual, this->_modeloEntidad->_pixelSiguiente);
		this->_modeloEntidad->notificarObservadores();
		this->_modeloEntidad->_pixelActual = this->_modeloEntidad->_pixelSiguiente;
		Sleep(espera);
	}

	// Dibuja el deplazamiento en el ultimo pixel para que quede bien ubicado en el tile que le corresponde
	this->_modeloEntidad->_pixelSiguiente = posicionDestino;
	this->_modeloEntidad->_direccion = this->obtenerDireccion(this->_modeloEntidad->_pixelActual, this->_modeloEntidad->_pixelSiguiente);
	this->_modeloEntidad->notificarObservadores();
	this->_modeloEntidad->_pixelActual = this->_modeloEntidad->_pixelSiguiente;
	Sleep(espera);
}
