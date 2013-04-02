#pragma once

#include <math.h>
#include <iostream>
#include <Windows.h>
#include <WinSock.h>

//TODO: Borrar
#include <SDL.h>

#include "../../utils/Constantes/Constantes.h"
#include "../../utils/Observador/Observable.h"
#include "../../utils/Hilos/Hilo.h"

//TODO: Borrar
#define ALTO_MATRIZ 10
#define ANCHO_MATRIZ 10

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

class ModeloEntidad : public Observable {
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
		Posicion _pixelSiguente;
		Direccion _direccion;
		VistaMovimiento* _vistaMovimiento;
		ModeloMovimiento* _modeloMovimientoActual;

		ModeloEntidad(const ModeloEntidad &modeloEntidad);

		ModeloEntidad& operator=(const ModeloEntidad &modeloEntidad);

		//TODO: Borrar
		class VistaEntidad : public Observador {
			private:
				char _mapa[ANCHO_MATRIZ][ALTO_MATRIZ];

			public:
				VistaEntidad() {
					unsigned int x = 0, y = 0;
					for (x = 0; x < ANCHO_MATRIZ; x++) {
						for (y = 0; y < ALTO_MATRIZ; y++) {
							this->_mapa[x][y] = '-';
						}
					}
				}

				virtual ~VistaEntidad() {
				}

				void actualizar(Observable* s) {
					ModeloEntidad* modeloEntidad = (ModeloEntidad*)s;
					Posicion posicionActual = modeloEntidad->posicionActual();
					Posicion posicionSiguiente = modeloEntidad->posicionSiguiente();
					unsigned int x = 0, y = 0;

					this->_mapa[posicionActual.x][posicionActual.y] = '-';
					this->_mapa[posicionSiguiente.x][posicionSiguiente.y] = 'X';

					system("cls");
					for (y = 0; y < ALTO_MATRIZ; y++) {
						for (x = 0; x < ANCHO_MATRIZ; x++) {
							std::cout << this->_mapa[x][y];
						}
						std::cout << std::endl;
					}
				}
		};

		//TODO: Borrar
		static void mover(ModeloEntidad* modeloEntidad, int x, int y) {
			Posicion posicionDestino;
			posicionDestino.x = x;
			posicionDestino.y = y;
			modeloEntidad->mover(posicionDestino);
		}

	public:
		//TODO: Borrar
		static void prueba() {
			bool salir = false;
			int xt = 0, yt = 0, xp = 0, yp = 0;
			SDL_Rect destino;
			SDL_Event evento;
			Posicion posicion;

			posicion.x = 0;
			posicion.y = 0;

			VistaEntidad vistaEntidad;
			ModeloEntidad modeloEntidad(1, 1, 200, posicion, true, ALTO_MATRIZ, ANCHO_MATRIZ, 15);
			
			modeloEntidad.agregarObservador(&vistaEntidad);
			
			SDL_Init(SDL_INIT_VIDEO);
			
			SDL_Surface *pantalla = SDL_SetVideoMode(1000, 500, 0, 0);
			SDL_Surface *tile = SDL_LoadBMP("img/tile.bmp");

			destino.h = ALTO_TILE;
			destino.w = ANCHO_TILE;

			for (xt = 0; xt < ANCHO_MATRIZ; xt++) {
				for (yt = 0; yt < ALTO_MATRIZ; yt++) {
					Posicion::convertirTileAPixel(ALTO_MATRIZ, xt, yt, xp, yp);
					destino.x = (Sint16)xp - (ANCHO_TILE / 2);
					destino.y = (Sint16)yp;
					SDL_BlitSurface(tile, NULL, pantalla, &destino);
				}
			}

			SDL_UpdateRect(pantalla, 0, 0, 0, 0);

			while (!salir) {
				if (SDL_PollEvent(&evento)) {
					if (evento.type == SDL_MOUSEBUTTONDOWN) {
						Posicion::convertirPixelATile(ALTO_MATRIZ, evento.motion.x, evento.motion.y, xt, yt);
						posicion.x = xt;
						posicion.y = yt;
						modeloEntidad.mover(posicion);
					}
            
					salir = (evento.type == SDL_QUIT);    
				}
			}

			SDL_FreeSurface(tile);

			SDL_Quit();
		}

		ModeloEntidad(int alto, int ancho, int velocidad, Posicion posicion, bool esJugador, int altoMapa, int anchoMapa, int fps);

		virtual ~ModeloEntidad();

		void cambiarEstado();

		int obtenerId() const;

		bool esJugador() const;

		int alto() const;

		int ancho() const;
		
		int velocidad() const;

		Posicion posicionActual() const;

		Posicion posicionSiguiente() const;

		Posicion pixelActual() const;

		Posicion pixelSiguente() const;

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
