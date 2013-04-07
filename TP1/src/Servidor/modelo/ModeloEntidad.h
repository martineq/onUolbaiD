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
#define ALTO_MATRIZ 20
#define ANCHO_MATRIZ 20
#define DESPLAZAMIENTO_SCROLL 1

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
				SDL_Surface* _mapa;
				SDL_Surface* _personaje;
				bool _rojo;
				
			public:
				VistaEntidad(SDL_Surface* mapa) {
					this->_mapa = mapa;
					this->_personaje = SDL_LoadBMP("img/sprite.bmp");
					this->_rojo = false;
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

					SDL_BlitSurface(this->_personaje, NULL, this->_mapa, &destino);
				}
		};

	public:
		//TODO: Borrar
		static void prueba() {
			bool salir = false;
			int alto = 0, ancho = 0, dummy = 0, xt = 0, yt = 0, xp = 0, yp = 0, dsx = 0, dsy = 0;
			Posicion posicionPersonaje, posicionScroll;
			SDL_Rect destinoPersonaje, destinoScroll;
			SDL_Event evento;
			
			Posicion::convertirTileAPixel(ALTO_MATRIZ, ANCHO_MATRIZ - 1, ALTO_MATRIZ - 1, dummy, alto);
			Posicion::convertirTileAPixel(ALTO_MATRIZ, ANCHO_MATRIZ - 1, 0, ancho, dummy);

			alto += ALTO_TILE;
			ancho += ANCHO_TILE / 2;

			SDL_Init(SDL_INIT_VIDEO);

			SDL_Surface* pantalla = SDL_SetVideoMode(500, 500, 0, 0);
			SDL_Surface* tile = SDL_LoadBMP("img/tile.bmp");
			SDL_Surface* mapa = SDL_CreateRGBSurface(SDL_SWSURFACE, ancho, alto, 32, 0, 0, 0, 0);

			posicionPersonaje.x = 0;
			posicionPersonaje.y = 0;
			posicionScroll.x = 0;
			posicionScroll.y = 0;

			VistaEntidad vistaEntidad(mapa);
			ModeloEntidad modeloEntidad(1, 1, 200, posicionPersonaje, true, ALTO_MATRIZ, ANCHO_MATRIZ, 15);
			
			modeloEntidad.agregarObservador(&vistaEntidad);
			
			destinoPersonaje.h = ALTO_TILE;
			destinoPersonaje.w = ANCHO_TILE;

			for (xt = 0; xt < ANCHO_MATRIZ; xt++) {
				for (yt = 0; yt < ALTO_MATRIZ; yt++) {
					Posicion::convertirTileAPixel(ALTO_MATRIZ, xt, yt, xp, yp);
					destinoPersonaje.x = (Sint16)xp - (ANCHO_TILE / 2);
					destinoPersonaje.y = (Sint16)yp;
					SDL_BlitSurface(tile, NULL, mapa, &destinoPersonaje);
				}
			}

			destinoScroll.h = 500;
			destinoScroll.w = 500;
			destinoScroll.x = 0;
			destinoScroll.y = 0;

			SDL_BlitSurface(mapa, &destinoScroll, pantalla, NULL);
			SDL_UpdateRect(pantalla, 0, 0, 0, 0);

			while (!salir) {
				if (SDL_PollEvent(&evento)) {
					if (evento.type == SDL_MOUSEMOTION) {
						if ((evento.motion.x >= 0) && (evento.motion.x <= 20))
							dsx = -DESPLAZAMIENTO_SCROLL;
						else if ((evento.motion.x >= 480) && (evento.motion.x <= 500))
							dsx = DESPLAZAMIENTO_SCROLL;
						else
							dsx = 0;
						if ((evento.motion.y >= 0) && (evento.motion.y <= 20))
							dsy = -DESPLAZAMIENTO_SCROLL;
						else if ((evento.motion.y >= 480) && (evento.motion.y <= 500))
							dsy = DESPLAZAMIENTO_SCROLL;
						else
							dsy = 0;
					}
					
					if (evento.type == SDL_MOUSEBUTTONDOWN) {
						Posicion::convertirPixelATile(ALTO_MATRIZ, evento.motion.x + posicionScroll.x, evento.motion.y + posicionScroll.y, xt, yt);
						posicionPersonaje.x = xt;
						posicionPersonaje.y = yt;
						modeloEntidad.mover(posicionPersonaje);
					}
					
					salir = (evento.type == SDL_QUIT);    
				}

				posicionScroll.x += dsx;
				posicionScroll.y += dsy;

				if (posicionScroll.x < 0)
					posicionScroll.x = 0;
				else if (posicionScroll.x + 500 > ancho)
					posicionScroll.x = ancho - 500;

				if (posicionScroll.y < 0)
					posicionScroll.y = 0;
				else if (posicionScroll.y + 500 > alto)
					posicionScroll.y = alto - 500;

				destinoScroll.x = (Sint16)posicionScroll.x;
				destinoScroll.y = (Sint16)posicionScroll.y;

				SDL_BlitSurface(mapa, &destinoScroll, pantalla, NULL);
				SDL_UpdateRect(pantalla, 0, 0, 0, 0);
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
