#pragma once

#include <list>

#include "../utils/Observador/Observador.h"
#include "modelo/ModeloJuego.h"
#include "modelo/ModeloScroll.h"

//TODO: Borrar
#include <SDL.h>
#include "../utils/Observador/Identificable.h"

//TODO: Borrar
#define ALTO_PANTALLA 500
#define ANCHO_PANTALLA 1000
#define ALTO_IMAGEN 70
#define ANCHO_IMAGEN 50
#define ALTO_MATRIZ 20
#define ANCHO_MATRIZ 20
#define DESPLAZAMIENTO_SCROLL 1

class Servidor {
	private:
		static SDL_Surface* cargarImagen(const char* archivoImagen) {
			SDL_Surface* imagen = SDL_LoadBMP(archivoImagen);
			SDL_Surface* imagenOptimizada = SDL_DisplayFormat(imagen);
			
			SDL_FreeSurface(imagen);

			Uint32 colorFondo = SDL_MapRGB(imagenOptimizada->format, 0xFF, 0xFF, 0xFF);
			SDL_SetColorKey(imagenOptimizada, SDL_SRCCOLORKEY, colorFondo);

			return imagenOptimizada;
		}

		ModeloJuego modeloJuego;

		//TODO: Borrar
		class VistaEntidad : public Observador, public Identificable {
			private:
				SDL_Surface* _nivel;
				SDL_Surface* _personaje;
				
			public:
				VistaEntidad(SDL_Surface* nivel) {
					this->_nivel = nivel;
					this->_personaje = Servidor::cargarImagen("img/SORA_S1.bmp");
				}

				virtual ~VistaEntidad() {
					SDL_FreeSurface(this->_personaje);
				}

				void actualizar(Observable* s) {
					ModeloEntidad* modeloEntidad = (ModeloEntidad*)s;
					SDL_Rect destino;

					destino.h = ALTO_IMAGEN;
					destino.w = ANCHO_IMAGEN;
					destino.x = modeloEntidad->pixelSiguiente().x - (ANCHO_IMAGEN / 2);
					destino.y = modeloEntidad->pixelSiguiente().y;

					SDL_BlitSurface(this->_personaje, NULL, this->_nivel, &destino);
				}

				int id() const {
					return 1;
				}
		};

		//TODO: Borrar
		class VistaScroll : public Observador, public Identificable {
			private:
				SDL_Surface* _pantalla;
				SDL_Surface* _nivel;
				SDL_Rect _destinoScroll;

			public:
				VistaScroll(SDL_Surface* pantalla, SDL_Surface* nivel) {
					this->_pantalla = pantalla;
					this->_nivel = nivel;
					this->_destinoScroll.w = ANCHO_PANTALLA;
					this->_destinoScroll.h = ALTO_PANTALLA;
				}

				virtual ~VistaScroll() {
				}

				void actualizar(Observable* s) {
					ModeloScroll* modeloScroll = (ModeloScroll*)s;
					
					this->_destinoScroll.x = (Sint16)modeloScroll->getX();
					this->_destinoScroll.y = (Sint16)modeloScroll->getY();
				}

				void dibujar() {
					SDL_BlitSurface(this->_nivel, &this->_destinoScroll, this->_pantalla, NULL);
					SDL_UpdateRect(this->_pantalla, 0, 0, 0, 0);
				}

				int id() const {
					return 1;
				}
		};

	public:
		//TODO: Borrar
		static void prueba() {
			bool salir = false;
			int alto = 0, ancho = 0, dummy = 0, xt = 0, yt = 0, xp = 0, yp = 0;
			Posicion posicionPersonaje;
			SDL_Rect destinoPersonaje;
			SDL_Event evento;
			
			Posicion::convertirTileAPixel(ALTO_MATRIZ, ANCHO_MATRIZ - 1, ALTO_MATRIZ - 1, dummy, alto);
			Posicion::convertirTileAPixel(ALTO_MATRIZ, ANCHO_MATRIZ - 1, 0, ancho, dummy);

			alto += ALTO_TILE + (ALTO_IMAGEN / 4);
			ancho += ANCHO_TILE / 2;

			SDL_Init(SDL_INIT_VIDEO);

			SDL_Surface* pantalla = SDL_SetVideoMode(ANCHO_PANTALLA, ALTO_PANTALLA, 0, 0);
			SDL_Surface* tile = Servidor::cargarImagen("img/tile.bmp");
			SDL_Surface* nivel = SDL_CreateRGBSurface(SDL_SWSURFACE, ancho, alto, 32, 0, 0, 0, 0);

			posicionPersonaje.x = 0;
			posicionPersonaje.y = 0;
			
			ModeloNivel modeloNivel;
			ModeloEntidad modeloJugador(1, 1, 200, posicionPersonaje, true, ALTO_MATRIZ, ANCHO_MATRIZ, 15);
			ModeloScroll modeloScroll(ANCHO_PANTALLA, ALTO_PANTALLA, ANCHO_MATRIZ, ALTO_MATRIZ, 20, 1, 0, 0, modeloJugador.id());
			VistaEntidad vistaJugador(nivel);
			VistaScroll vistaScroll(pantalla, nivel);

			modeloNivel.setAltoTiles(ALTO_MATRIZ);
			modeloNivel.setAnchoTiles(ANCHO_MATRIZ);
			modeloNivel.agregarScroll(&modeloScroll);
			modeloNivel.agregarJugador(&modeloJugador);

			std::list<Observador*> listaObservadoresJugador;
			listaObservadoresJugador.push_back(&vistaJugador);
			modeloNivel.agregarObservadoresJugador(listaObservadoresJugador);
			
			std::list<Observador*> listaObservadoresScroll;
			listaObservadoresScroll.push_back(&vistaScroll);
			modeloNivel.agregarObservadoresScroll(listaObservadoresScroll);
			
			destinoPersonaje.h = ALTO_TILE;
			destinoPersonaje.w = ANCHO_TILE;

			for (xt = 0; xt < ANCHO_MATRIZ; xt++) {
				for (yt = 0; yt < ALTO_MATRIZ; yt++) {
					Posicion::convertirTileAPixel(ALTO_MATRIZ, xt, yt, xp, yp);
					destinoPersonaje.x = (Sint16)xp - (ANCHO_TILE / 2);
					destinoPersonaje.y = (Sint16)yp + (ALTO_IMAGEN / 4);
					SDL_BlitSurface(tile, NULL, nivel, &destinoPersonaje);
				}
			}

			SDL_BlitSurface(nivel, NULL, pantalla, NULL);
			
			while (!salir) {
				if (SDL_PollEvent(&evento)) {
					/*if (evento.type == SDL_MOUSEMOTION)
						modeloNivel.moverScroll(evento.motion.x, evento.motion.y, 0);
					else */if (evento.type == SDL_MOUSEBUTTONDOWN)
						modeloNivel.moverJugador(evento.motion.x + modeloScroll.getX(), evento.motion.y + modeloScroll.getY() - (ALTO_IMAGEN / 4), 0);
				}
				
				modeloNivel.moverScroll(evento.motion.x, evento.motion.y, modeloJugador.id());
				vistaScroll.dibujar();

				salir = (evento.type == SDL_QUIT);
			}

			SDL_FreeSurface(tile);
			SDL_FreeSurface(nivel);
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
