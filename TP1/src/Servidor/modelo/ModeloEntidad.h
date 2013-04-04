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
		Posicion _pixelSiguiente;
		Direccion _direccion;
		VistaMovimiento* _vistaMovimiento;
		ModeloMovimiento* _modeloMovimientoActual;
		int _altoMapa;
		int _anchoMapa;

		ModeloEntidad(const ModeloEntidad &modeloEntidad);

		ModeloEntidad& operator=(const ModeloEntidad &modeloEntidad);

		//TODO: Borrar
		class VistaEntidad : public Observador {
			private:
				SDL_Surface* _pantalla;
				SDL_Surface* _mapa;
				SDL_Surface* _personaje;
				
			public:
				VistaEntidad(SDL_Surface* pantalla,SDL_Surface* mapa) {
					this->_pantalla = pantalla;
					this->_mapa = mapa;
					this->_personaje = SDL_LoadBMP("img/sprite.bmp");
				}

				virtual ~VistaEntidad() {
					SDL_FreeSurface(this->_personaje);
				}

				void actualizar(Observable* s) {
					ModeloEntidad* modeloEntidad = (ModeloEntidad*)s;
					SDL_Rect destino;

					destino.h = 32;
					destino.w = 32;
					destino.x = modeloEntidad->pixelSiguiente().x;
					destino.y = modeloEntidad->pixelSiguiente().y;
					
					SDL_BlitSurface(this->_mapa, NULL, this->_pantalla, NULL);
					SDL_BlitSurface(this->_personaje, NULL, this->_pantalla, &destino);
					SDL_UpdateRect(this->_pantalla, 0, 0, 0, 0);
				}
		};

	public:
		//TODO: Borrar
		static void prueba() {
			bool salir = false;
			int xt = 0, yt = 0, xp = 0, yp = 0;
			SDL_Rect destino;
			SDL_Event evento;
			Posicion posicion;

			SDL_Init(SDL_INIT_VIDEO);

			SDL_Surface* pantalla = SDL_SetVideoMode(1000, 500, 0, 0);
			SDL_Surface* tile = SDL_LoadBMP("img/tile.bmp");
			SDL_Surface* mapa = SDL_CreateRGBSurface(SDL_SWSURFACE, 1000, 500, 32, 0, 0, 0, 0);

			posicion.x = 0;
			posicion.y = 0;

			VistaEntidad vistaEntidad(pantalla, mapa);
			ModeloEntidad modeloEntidad(1, 1, 200, posicion, true, ALTO_MATRIZ, ANCHO_MATRIZ, 15);
			
			modeloEntidad.agregarObservador(&vistaEntidad);
			
			destino.h = ALTO_TILE;
			destino.w = ANCHO_TILE;

			for (xt = 0; xt < ANCHO_MATRIZ; xt++) {
				for (yt = 0; yt < ALTO_MATRIZ; yt++) {
					Posicion::convertirTileAPixel(ALTO_MATRIZ, xt, yt, xp, yp);
					destino.x = (Sint16)xp - (ANCHO_TILE / 2);
					destino.y = (Sint16)yp;
					SDL_BlitSurface(tile, NULL, mapa, &destino);
				}
			}

			SDL_BlitSurface(mapa, NULL, pantalla, NULL);
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
