#pragma once

#include <list>

#include "../utils/Observador/Observador.h"
#include "modelo/ModeloJuego.h"
#include "modelo/ModeloScroll.h"

//TODO: Borrar
#include <SDL.h>

//TODO: Borrar
#define ALTO_MATRIZ 20
#define ANCHO_MATRIZ 20
#define DESPLAZAMIENTO_SCROLL 1

class Servidor{
	private:
		ModeloJuego modeloJuego;

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
			int alto = 0, ancho = 0, dummy = 0, xt = 0, yt = 0, xp = 0, yp = 0;
			Posicion posicionPersonaje;
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
			
			ModeloScroll modeloScroll(500, 500, ancho, alto, 20, 1, 0, 0, 0);
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
			destinoScroll.x = modeloScroll.getX();
			destinoScroll.y = modeloScroll.getY();

			SDL_BlitSurface(mapa, &destinoScroll, pantalla, NULL);
			SDL_UpdateRect(pantalla, 0, 0, 0, 0);

			while (!salir) {
				if (SDL_PollEvent(&evento)) {
					if (evento.type == SDL_MOUSEMOTION) {
						modeloScroll.actualizar(evento.motion.x, evento.motion.y);
					}
					else if (evento.type == SDL_MOUSEBUTTONDOWN) {
						Posicion::convertirPixelATile(ALTO_MATRIZ, evento.motion.x + modeloScroll.getX(), evento.motion.y + modeloScroll.getY(), xt, yt);
						posicionPersonaje.x = xt;
						posicionPersonaje.y = yt;
						modeloEntidad.mover(posicionPersonaje);
					}
					
					salir = (evento.type == SDL_QUIT);    
				}

				destinoScroll.x = (Sint16)modeloScroll.getX();
				destinoScroll.y = (Sint16)modeloScroll.getY();

				SDL_BlitSurface(mapa, &destinoScroll, pantalla, NULL);
				SDL_UpdateRect(pantalla, 0, 0, 0, 0);
			}

			SDL_FreeSurface(tile);

			SDL_Quit();
		}

		Servidor();
		
		virtual ~Servidor();

		// Inicia el Modelo Juego
		bool iniciar();
		
		void agregarObservadoresScroll(std::list<Observador*>);
		
		void agregarObservadoresEntidad(std::list<Observador*>);
		
		Observador* obtenerObservadorEvento();
		
		// Inicia el loop de Modelo Juego
		bool loop();
};
