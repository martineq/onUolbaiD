#pragma once

#include <math.h>
#include <iostream>
#include <Windows.h>
#include <WinSock.h>

#include "../../utils/Constantes/Constantes.h"
#include "../../utils/Observador/Observable.h"
#include "../../utils/Observador/Identificable.h"
#include "../../utils/Hilos/Hilo.h"

typedef enum Direccion { NORTE, NORESTE, ESTE, SUDESTE, SUR, SUDOESTE, OESTE, NOROESTE, CENTRO };

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
		class ModeloMovimiento : public Observable {
			private:
				ModeloEntidad* _modeloEntidad;
				Posicion _posicionDestino;
				int _deltaX;
				int _deltaY;
				int _desplazamientoX;
				int _desplazamientoY;
				int _error;
				int _desplazamientoErrorX;
				int _desplazamientoErrorY;
				DWORD _instanteUltimoCambioEstado;
				
				ModeloMovimiento(const ModeloMovimiento &modeloMovimiento);

				ModeloMovimiento& operator=(const ModeloMovimiento &modeloMovimiento);

			public:
				ModeloMovimiento(ModeloEntidad* modeloEntidad);

				virtual ~ModeloMovimiento();

				void actualizar(Posicion posicion);

				void cambiarEstado();
		};

		class VistaMovimiento : public Observador {
			private:
				ModeloEntidad* _modeloEntidad;
				Posicion _posicionOrigen;
				Posicion _posicionDestino;
				int _altoMapa;
				int _anchoMapa;
				int _cantidadCuadros;
				int _desplazamiento;
				DWORD _espera;
				int _cuadroActual;
				std::list<Posicion> _posiciones;
				DWORD _instanteUltimoCambioEstado;
				
				Direccion obtenerDireccion(Posicion posicionOrigen, Posicion posicionDestino);

				VistaMovimiento(const VistaMovimiento &vistaMovimiento);

				VistaMovimiento& operator=(const VistaMovimiento &vistaMovimiento);

			public:
				VistaMovimiento(ModeloEntidad* modeloEntidad, int altoMapa, int anchoMapa, int fps);

				virtual ~VistaMovimiento();
				
				void actualizar(Observable* observable);

				void cambiarEstado();
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
		ModeloMovimiento* _modeloMovimiento;
		VistaMovimiento* _vistaMovimiento;
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

// TODO: Importante: El método cambiarEstado() tiene que estar regulado por un timer para poder controlar
//                   el tráfico de datos que le será enviado a la VistaEntidad. La idea es que el ModeloLoop
//					 tenga ese timer y cada cierto período (1/15 seg) ordene a toda la lista de ModeloEntidad 
//					 que contiene ModeloNivel hacer el cambiarEstado(), si es que de verdad cambió el estado.
//					 De esta manera el Modelo calcula todo lo que le llega a través del controlador,
//					 pero sólo lo envía a la Vista cuando esta lo necesita. (Lo pongo acá para no olvidarme)
