#pragma once

#include <math.h>

#include "../Constantes/Constantes.h"

typedef struct Posicion {
	int x;
	int y;

	static void convertirTileAPixel(int altoEnTiles, int xTile, int yTile, int& xPixel, int& yPixel) {
		xPixel = (ANCHO_TILE / 2) * (xTile - yTile) + (ANCHO_TILE / 2) * altoEnTiles;
		yPixel = (ALTO_TILE / 2) * (xTile + yTile);
	}

	static void convertirPixelATile(int altoEnTiles, int xPixel, int yPixel, int& xTile, int& yTile) {
		double desplazamientoX = 0, desplazamientoY = 0;
		
		xPixel -= (ANCHO_TILE / 2) * altoEnTiles;
		desplazamientoX = (double)xPixel / ANCHO_TILE;
		desplazamientoY = (double)yPixel / ALTO_TILE;
		
		xTile = floor(desplazamientoY + desplazamientoX);
		yTile = floor(desplazamientoY - desplazamientoX);
	} 

	Posicion() {
		this->x = 0;
		this->y = 0;
	}

	bool operator==(const Posicion& posicion) const {
		return ((this->x == posicion.x) && (this->y == posicion.y));
	}

	bool operator!=(const Posicion& posicion) const {
		return !(*this == posicion);
	}

	bool operator>(const Posicion& posicion) const
	{
		if (this->y > posicion.y)
			return true;
		else if (this->y < posicion.y)
			return false;
		else
			return this->x > posicion.x;
	}

	bool operator<(const Posicion& posicion) const
	{
		if (this->y < posicion.y)
			return true;
		else if (this->y > posicion.y)
			return false;
		else
			return this->x < posicion.x;
	}

	bool operator>=(const Posicion& posicion) const
	{
		return ((*this > posicion) || (*this == posicion));
	}

	bool operator<=(const Posicion& posicion) const
	{
		return ((*this < posicion) || (*this == posicion));;
	}
} Posicion;