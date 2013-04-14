#pragma once

#include <math.h>
#include <iostream>
#include <Windows.h>
#include <WinSock.h>

#include "../../utils/Constantes/Constantes.h"
#include "../../utils/Observador/Observable.h"
#include "../../utils/Observador/Identificable.h"
#include "../../utils/Hilos/Hilo.h"

typedef enum Direccion { NORTE, SUR, ESTE, OESTE, NORESTE, NOROESTE, SUDESTE, SUDOESTE, CENTRO };

typedef struct Posicion {
	int x;
	int y;

	static void convertirTileAPixel(int altoEnTiles, int xTile, int yTile, int &xPixel, int &yPixel) {
		xPixel = (ANCHO_TILE / 2) * (xTile - yTile) + (ANCHO_TILE / 2) * altoEnTiles;
		yPixel = (ALTO_TILE / 2) * (xTile + yTile);
	}

	static void convertirPixelATile(int altoEnTiles, int xPixel, int yPixel, int &xTile, int &yTile) {
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

	bool operator==(const Posicion &posicion) const {
		return ((this->x == posicion.x) && (this->y == posicion.y));
	}

	bool operator!=(const Posicion &posicion) const {
		return !(*this == posicion);
	}
} Posicion;

class ModeloEntidad : public Observable, public Identificable {
	private:
		class ModeloMovimiento : public Hilo, public Observable {
			private:
				ModeloEntidad* _modeloEntidad;
				Posicion _posicionDestino;
				bool _ejecutando;

				void* run(void* parametro);

				void cambiarEstado();

				ModeloMovimiento(const ModeloMovimiento &modeloMovimiento);

				ModeloMovimiento& operator=(const ModeloMovimiento &modeloMovimiento);

			public:
				ModeloMovimiento(ModeloEntidad* modeloEntidad, Posicion posicionDestino);

				virtual ~ModeloMovimiento();

				void detener();
		};

		class VistaMovimiento : public Observador {
			private:
				ModeloEntidad* _modeloEntidad;
				int _altoMapa;
				int _anchoMapa;
				int _fps;
				
				Direccion obtenerDireccion(Posicion posicionOrigen, Posicion posicionDestino);

				VistaMovimiento(const VistaMovimiento &vistaMovimiento);

				VistaMovimiento& operator=(const VistaMovimiento &vistaMovimiento);

			public:
				VistaMovimiento(ModeloEntidad* modeloEntidad, int altoMapa, int anchoMapa, int fps);

				virtual ~VistaMovimiento();
				
				void actualizar(Observable* observable);
		};

		static long _ultimoId;

		int _id;
		bool _esJugador;
		int _alto;
		int _ancho;
		int _velocidad;
		Posicion _posicionActual;
		Posicion _posicionSiguiente;
		Posicion _pixelActual;
		Posicion _pixelSiguiente;
		Direccion _direccion;
		VistaMovimiento* _vistaMovimiento;
		ModeloMovimiento* _modeloMovimientoActual;
		int _altoMapa;
		int _anchoMapa;

		ModeloEntidad(const ModeloEntidad &modeloEntidad);

		ModeloEntidad& operator=(const ModeloEntidad &modeloEntidad);

	public:
		ModeloEntidad(int alto, int ancho, int velocidad, Posicion posicion, bool esJugador, int altoMapa, int anchoMapa, int fps);

		virtual ~ModeloEntidad();

		void cambiarEstado();

		int id() const;

		bool esJugador() const;

		int alto() const;

		int ancho() const;
		
		int velocidad() const;

		Posicion posicionActual() const;

		Posicion posicionSiguiente() const;

		Posicion pixelActual() const;

		Posicion pixelSiguiente() const;

		Direccion direccion() const;

		void mover(Posicion posicion);

		bool operator==(const ModeloEntidad &modeloEntidad) const;
};
