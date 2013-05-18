#pragma once

#include <math.h>
#include <iostream>

#include "Posicion.h"

class Tile {
	private:
		int _distanciaDestino;
		int _distanciaOrigen;
		Tile* _padre;
		Posicion _posicion;

	public:
		Tile() {
			this->_distanciaDestino = 0;
			this->_distanciaOrigen = 0;
			this->_padre = NULL;
		}

		virtual ~Tile() {
		}

		Tile* padre() {
			return this->_padre;
		}

		void padre(Tile* padre, int distancia) {
			if (padre == NULL) {
				this->_padre = NULL;
				this->_distanciaOrigen = 0;
			}
			else if ((this->_padre == NULL) || (this->_distanciaOrigen > padre->_distanciaOrigen + distancia)) {
				this->_padre = padre;
				this->_distanciaOrigen = this->_padre->_distanciaOrigen + distancia;
			}
		}

		Posicion posicion() {
			return this->_posicion;
		}

		void posicion(Posicion posicion) {
			this->_posicion = posicion;
		}

		void posicionDestino(Posicion posicionDestino) {
			this->_distanciaDestino = pow((double)this->_posicion.x - (double)posicionDestino.x, 2) + pow((double)this->_posicion.y - (double)posicionDestino.y, 2);
		}

		bool operator==(const Tile& tile) const {
			return ((this->_distanciaOrigen + this->_distanciaDestino) == (tile._distanciaOrigen + tile._distanciaDestino));
		}

		bool operator!=(const Tile& tile) const {
			return !(*this == tile);
		}

		bool operator>(const Tile& tile) const
		{
			return ((this->_distanciaOrigen + this->_distanciaDestino) > (tile._distanciaOrigen + tile._distanciaDestino));
		}

		bool operator<(const Tile& tile) const
		{
			return ((this->_distanciaOrigen + this->_distanciaDestino) < (tile._distanciaOrigen + tile._distanciaDestino));
		}

		bool operator>=(const Tile& tile) const
		{
			return ((*this > tile) || (*this == tile));
		}

		bool operator<=(const Tile& tile) const
		{
			return ((*this < tile) || (*this == tile));;
		}
};
