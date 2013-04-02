#include "ModeloEntidad.h"

//TODO: Reemplazar por las variables cargadas del YAML
#define FPS YAML_DEAFAULT_FPS
#define ALTO_TILES 10

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
	this->_fps;
}

ModeloEntidad::VistaMovimiento::~VistaMovimiento() {
}

void ModeloEntidad::VistaMovimiento::actualizar(Observable* observable) {
	Posicion posicionOrigen, posicionDestino, posicionActual;
	int deltaX, deltaY, desplazamientoX, desplazamientoY, error, desplazamientoErrorX, desplazamientoErrorY;
	list<Posicion> posiciones;

	Posicion::convertirTileAPixel(ALTO_TILES, this->_modeloEntidad->posicionActual().x, this->_modeloEntidad->posicionActual().y, posicionOrigen.x, posicionOrigen.y);
	Posicion::convertirTileAPixel(ALTO_TILES, this->_modeloEntidad->posicionSiguiente().x, this->_modeloEntidad->posicionSiguiente().y, posicionDestino.x, posicionDestino.y);
	posicionActual = posicionOrigen;

	deltaX = abs(posicionDestino.x - posicionOrigen.x);
	deltaY = abs(posicionDestino.y - posicionOrigen.y);
	desplazamientoX = (posicionOrigen.x < posicionDestino.x) ? 1 : -1;
	desplazamientoY = (posicionOrigen.y < posicionDestino.y) ? 1 : -1;
	error = (deltaX >= deltaY) ? deltaX : deltaY;
	desplazamientoErrorX = 2 * deltaX;
	desplazamientoErrorY = 2 * deltaY;
	
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

	list<Posicion>::iterator iterador = posiciones.begin();
	int cuadros = posiciones.size() / ((this->_modeloEntidad->velocidad() * FPS) / 1000);

	this->_modeloEntidad->_pixelActual = posicionOrigen;
	for (int i = 0; i < cuadros; i++) {
		advance(iterador, i * ((this->_modeloEntidad->velocidad() * FPS) / 1000));
		this->_modeloEntidad->_pixelSiguente = *iterador;
		this->_modeloEntidad->_direccion = this->obtenerDireccion(this->_modeloEntidad->_pixelActual, this->_modeloEntidad->_pixelSiguente);
		this->_modeloEntidad->notificarObservadores();
		this->_modeloEntidad->_pixelActual = this->_modeloEntidad->_pixelSiguente;
		Sleep(FPS / 1000);
	}
}
