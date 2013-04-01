#pragma once

#include <iostream>
#include <Windows.h>
#include <winsock.h>
#include <SDL.h>
#include <math.h>

#include "../../utils/Constantes/Constantes.h"
#include "../../utils/Observador/Observable.h"
#include "../../utils/Hilos/Hilo.h"

//TODO: Borrar
#define ALTO_MATRIZ 10
#define ANCHO_MATRIZ 10

typedef struct Posicion {
	int x;
	int y;

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
		class Movimiento : public Hilo {
			private:
				ModeloEntidad* _modeloEntidad;
				Posicion _posicionDestino;
				bool _ejecutando;

				void* run(void* parametro);

				Movimiento(const Movimiento &movimiento);

				Movimiento& operator=(const Movimiento &movimiento);

			public:
				Movimiento(ModeloEntidad* modeloEntidad, Posicion posicionDestino);

				virtual ~Movimiento();

				void detener();
		};

		static long _ultimoId;

		int _id;
		bool _esJugador;
		unsigned int _alto;
		unsigned int _ancho;
		unsigned int _velocidad;
		Posicion _posicionActual;
		Posicion _posicionSiguiente;
		Movimiento* _movimientoActual;

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
		static void mover(ModeloEntidad* modeloEntidad, unsigned int x, unsigned int y) {
			Posicion posicionDestino;
			posicionDestino.x = x;
			posicionDestino.y = y;
			modeloEntidad->mover(posicionDestino);
		}

		//TODO: Borrar
		static void obtenerPixel(int xt, int yt, Sint16 &xp, Sint16 &yp) {
			xp = (ANCHO_TILE / 2) * (xt - yt) + (ANCHO_TILE / 2) * (ALTO_MATRIZ) - (ANCHO_TILE / 2);
			yp = (ALTO_TILE / 2) * (xt + yt);
		}

		//TODO: Borrar
		static void obtenerTile(int xp, int yp, int &xt, int &yt) {
			double desplazamientoX = 0, desplazamientoY = 0;
	
			xp -= (ANCHO_TILE / 2) * ALTO_MATRIZ;
			desplazamientoX = (double)xp / ANCHO_TILE;
			desplazamientoY = (double)yp / ALTO_TILE;

			xt = floor(desplazamientoY + desplazamientoX);
			yt = floor(desplazamientoY - desplazamientoX);
		}

	public:
		//TODO: Borrar
		static void prueba() {
			bool salir = false;
			int xt = 0, yt = 0;
			SDL_Rect destino;
			SDL_Event evento;
			Posicion posicion;

			posicion.x = 0;
			posicion.y = 0;

			VistaEntidad vistaEntidad;
			ModeloEntidad modeloEntidad(1, 1, 200, posicion, true);
			
			modeloEntidad.agregarObservador(&vistaEntidad);
			
			SDL_Init(SDL_INIT_VIDEO);
			
			SDL_Surface *pantalla = SDL_SetVideoMode(1000, 500, 0, 0);
			SDL_Surface *tile = SDL_LoadBMP("img/tile.bmp");

			destino.h = ALTO_TILE;
			destino.w = ANCHO_TILE;

			for (xt = 0; xt < ANCHO_MATRIZ; xt++) {
				for (yt = 0; yt < ALTO_MATRIZ; yt++) {
					ModeloEntidad::obtenerPixel(xt, yt, destino.x, destino.y);
					SDL_BlitSurface(tile, NULL, pantalla, &destino);
				}
			}

			SDL_UpdateRect(pantalla, 0, 0, 0, 0);

			while (!salir) {
				if (SDL_PollEvent(&evento)) {
					if (evento.type == SDL_MOUSEBUTTONDOWN) {
						ModeloEntidad::obtenerTile(evento.motion.x, evento.motion.y, xt, yt);
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

		ModeloEntidad(unsigned int alto, unsigned int ancho, unsigned int velocidad, Posicion posicion, bool esJugador);

		virtual ~ModeloEntidad();

		void cambiarEstado();

		int obtenerId() const;

		bool esJugador() const;

		unsigned int alto() const;

		unsigned int ancho() const;
		
		unsigned int velocidad() const;

		Posicion posicionActual() const;

		Posicion posicionSiguiente() const;

		void mover(Posicion posicion);

		bool operator==(const ModeloEntidad &modeloEntidad) const;
};

// TODO: Importante: El método cambiarEstado() tiene que estar regulado por un timer para poder controlar
//                   el tráfico de datos que le será enviado a la VistaEntidad. La idea es que el ModeloLoop
//					 tenga ese timer y cada cierto período (1/15 seg) ordene a toda la lista de ModeloEntidad 
//					 que contiene ModeloNivel hacer el cambiarEstado(), si es que de verdad cambió el estado.
//					 De esta manera el Modelo calcula todo lo que le llega a través del controlador,
//					 pero sólo lo envía a la Vista cuando esta lo necesita. (Lo pongo acá para no olvidarme)