#pragma once

#include <list>

#include "modelo/ModeloJuego.h"
#include "modelo/ModeloScroll.h"

//TODO: Borrar
#include <SDL.h>
#include "../utils/Observador/Identificable.h"
#include "../Cliente/vista/VistaEntidad.h"
#include "../Cliente/vista/SDLutil.h"

//TODO: Borrar
#define ALTO_PANTALLA 500
#define ANCHO_PANTALLA 1000
#define ALTO_IMAGEN 70
#define ANCHO_IMAGEN 50
#define ALTO_MATRIZ 200
#define ANCHO_MATRIZ 200

class Servidor {
	private:
		ModeloJuego modeloJuego;

		//TODO: Borrar
		class VistaEntidadPrueba : public Observador, public Identificable {
			private:
				SDLutil* _utilidadSDL;
				Posicion _posicion;
				
			public:
				VistaEntidadPrueba() {
					this->_utilidadSDL = new SDLutil(0, 0, ANCHO_IMAGEN, ALTO_IMAGEN, "img/testxyh_S1.png");
				}

				virtual ~VistaEntidadPrueba() {
					delete this->_utilidadSDL;
				}

				void actualizar(Observable* s) {
					ModeloEntidad* modeloEntidad = (ModeloEntidad*)s;
					this->_posicion = modeloEntidad->pixelSiguiente();
				}

				void setPantalla(SDL_Surface* nivel) {
					this->_utilidadSDL->setPantalla(nivel);
				}

				void graficar(int xScroll, int yScroll) {
					this->_utilidadSDL->graficar(this->_posicion.x - xScroll, this->_posicion.y - yScroll);
				}

				Posicion posicion() {
					return this->_posicion;
				}

				int id() const {
					return 1;
				}
		};

		//TODO: Borrar
		class VistaScrollPrueba : public Observador, public Identificable {
			private:
				SDLutil* _utilidadSDL;
				VistaEntidadPrueba* _vistaEntidad;
				Posicion _destinoScroll;
				SDL_Surface* _pantalla;
				bool _actualizar;
				
				bool entraEnPantalla(VistaEntidadPrueba* vistaEntidad){
					bool entraEnX = false, entraEnY = false;

					if ((vistaEntidad->posicion().x > this->_destinoScroll.x) &&
						(vistaEntidad->posicion().x < (this->_destinoScroll.x + ANCHO_PANTALLA)) ||
						(((vistaEntidad->posicion().x + ANCHO_IMAGEN) > this->_destinoScroll.x) && 
						((vistaEntidad->posicion().x + ANCHO_IMAGEN) < this->_destinoScroll.x + ANCHO_PANTALLA))) {
						entraEnX = true;
					}

					if (((vistaEntidad->posicion().y > this->_destinoScroll.y) &&
						(vistaEntidad->posicion().y < (this->_destinoScroll.y + ALTO_PANTALLA)) ||
						(((vistaEntidad->posicion().y + ALTO_IMAGEN) > this->_destinoScroll.y) && 
						((vistaEntidad->posicion().y + ALTO_IMAGEN) < this->_destinoScroll.y + ALTO_PANTALLA)))) {
						entraEnY = true;
					}

					return entraEnX && entraEnY;
				}

				void obtenerTilesLimites(Posicion& posicionInicial, Posicion& posicionFinal) {
					Posicion posicion1, posicion2, posicion3, posicion4;

					Posicion::convertirPixelATile(ALTO_MATRIZ, this->_destinoScroll.x, this->_destinoScroll.y, posicion1.x, posicion1.y);
					Posicion::convertirPixelATile(ALTO_MATRIZ, this->_destinoScroll.x + ANCHO_PANTALLA, this->_destinoScroll.y, posicion2.x, posicion2.y);
					Posicion::convertirPixelATile(ALTO_MATRIZ, this->_destinoScroll.x, this->_destinoScroll.y + ALTO_PANTALLA, posicion3.x, posicion3.y);
					Posicion::convertirPixelATile(ALTO_MATRIZ, this->_destinoScroll.x + ANCHO_PANTALLA, this->_destinoScroll.y + ALTO_PANTALLA, posicion4.x, posicion4.y);

					posicionInicial.x = posicion1.x;
					if (posicionInicial.x > posicion2.x)
						posicionInicial.x = posicion2.x;
					if (posicionInicial.x > posicion3.x)
						posicionInicial.x = posicion3.x;
					if (posicionInicial.x > posicion4.x)
						posicionInicial.x = posicion4.x;

					posicionInicial.y = posicion1.y;
					if (posicionInicial.y > posicion2.y)
						posicionInicial.y = posicion2.y;
					if (posicionInicial.y > posicion3.y)
						posicionInicial.y = posicion3.y;
					if (posicionInicial.y > posicion4.y)
						posicionInicial.y = posicion4.y;

					if (posicionInicial.x < 0)
						posicionInicial.x = 0;
					if (posicionInicial.y < 0)
						posicionInicial.y = 0;

					posicionFinal.x = posicionFinal.x;
					if (posicionFinal.x < posicion2.x)
						posicionFinal.x = posicion2.x;
					if (posicionFinal.x < posicion3.x)
						posicionFinal.x = posicion3.x;
					if (posicionFinal.x < posicion4.x)
						posicionFinal.x = posicion4.x;

					posicionFinal.y = posicion1.y;
					if (posicionFinal.y < posicion2.y)
						posicionFinal.y = posicion2.y;
					if (posicionFinal.y < posicion3.y)
						posicionFinal.y = posicion3.y;
					if (posicionFinal.y < posicion4.y)
						posicionFinal.y = posicion4.y;

					posicionFinal.x++;
					posicionFinal.y++;

					if (posicionFinal.x > ANCHO_MATRIZ)
						posicionFinal.x = ANCHO_MATRIZ;
					if (posicionFinal.y > ALTO_MATRIZ)
						posicionFinal.y = ALTO_MATRIZ;
				}

			public:
				VistaScrollPrueba(VistaEntidadPrueba* vistaEntidad) {
					this->_utilidadSDL = new SDLutil(0, 0, ANCHO_TILE, ALTO_TILE, "img/tile.png");
					this->_vistaEntidad = vistaEntidad;
					this->_actualizar = false;
				}

				virtual ~VistaScrollPrueba() {
				}

				void actualizar(Observable* s) {
					ModeloScroll* modeloScroll = (ModeloScroll*)s;
					
					this->_destinoScroll.x = modeloScroll->getX();
					this->_destinoScroll.y = modeloScroll->getY();
					this->_actualizar = true;
				}

				void setPantalla(SDL_Surface* pantalla) {
					this->_pantalla = pantalla;
					this->_utilidadSDL->setPantalla(pantalla);
				}

				void graficar() {
					int xt = 0, yt = 0, xp = 0, yp = 0;
					Posicion posicionInicial, posicionFinal;
					this->obtenerTilesLimites(posicionInicial, posicionFinal);

					SDL_FillRect(this->_pantalla, NULL, 0x000000);

					for (xt = posicionInicial.x; xt < posicionFinal.x; xt++) {
						for (yt = posicionInicial.y; yt < posicionFinal.y; yt++) {
							Posicion::convertirTileAPixel(ALTO_MATRIZ, xt, yt, xp, yp);
							this->_utilidadSDL->graficar(xp - this->_destinoScroll.x - (ANCHO_TILE / 2), yp - this->_destinoScroll.y);
						}
					}
					this->_actualizar = false;
					
					if (this->entraEnPantalla(this->_vistaEntidad))
						this->_vistaEntidad->graficar(this->_destinoScroll.x, this->_destinoScroll.y);
					
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
			SDL_Event evento;
			
			Posicion::convertirTileAPixel(ALTO_MATRIZ, ANCHO_MATRIZ - 1, ALTO_MATRIZ - 1, dummy, alto);
			Posicion::convertirTileAPixel(ALTO_MATRIZ, ANCHO_MATRIZ - 1, 0, ancho, dummy);

			alto += ALTO_TILE + (ALTO_IMAGEN / 4);
			ancho += ANCHO_TILE / 2;

			SDL_Init(SDL_INIT_VIDEO);

			SDL_Surface* pantalla = SDL_SetVideoMode(ANCHO_PANTALLA, ALTO_PANTALLA, 0, 0);
			
			std::list<list<string>> animacionesJugador;
			std::list<string> animacionesJugadorNorte;
			std::list<string> animacionesJugadorNoreste;
			std::list<string> animacionesJugadorEste;
			std::list<string> animacionesJugadorSudeste;
			std::list<string> animacionesJugadorSur;
			std::list<string> animacionesJugadorSudoeste;
			std::list<string> animacionesJugadorOeste;
			std::list<string> animacionesJugadorNoroeste;

			animacionesJugadorNorte.push_back("./img/testxyh_N1.png");
			animacionesJugadorNorte.push_back("./img/testxyh_N2.png");
			animacionesJugadorNorte.push_back("./img/testxyh_N3.png");
			animacionesJugadorNorte.push_back("./img/testxyh_N4.png");

			animacionesJugadorNoreste.push_back("./img/testxyh_NE1.png");
			animacionesJugadorNoreste.push_back("./img/testxyh_NE2.png");
			animacionesJugadorNoreste.push_back("./img/testxyh_NE3.png");
			animacionesJugadorNoreste.push_back("./img/testxyh_NE4.png");
			
			animacionesJugadorEste.push_back("./img/testxyh_E1.png");
			animacionesJugadorEste.push_back("./img/testxyh_E2.png");
			animacionesJugadorEste.push_back("./img/testxyh_E3.png");
			animacionesJugadorEste.push_back("./img/testxyh_E4.png");

			animacionesJugadorSudeste.push_back("./img/testxyh_SE1.png");
			animacionesJugadorSudeste.push_back("./img/testxyh_SE2.png");
			animacionesJugadorSudeste.push_back("./img/testxyh_SE3.png");
			animacionesJugadorSudeste.push_back("./img/testxyh_SE4.png");

			animacionesJugadorSur.push_back("./img/testxyh_S1.png");
			animacionesJugadorSur.push_back("./img/testxyh_S2.png");
			animacionesJugadorSur.push_back("./img/testxyh_S3.png");
			animacionesJugadorSur.push_back("./img/testxyh_S4.png");

			animacionesJugadorSudoeste.push_back("./img/testxyh_SO1.png");
			animacionesJugadorSudoeste.push_back("./img/testxyh_SO2.png");
			animacionesJugadorSudoeste.push_back("./img/testxyh_SO3.png");
			animacionesJugadorSudoeste.push_back("./img/testxyh_SO4.png");

			animacionesJugadorOeste.push_back("./img/testxyh_O1.png");
			animacionesJugadorOeste.push_back("./img/testxyh_O2.png");
			animacionesJugadorOeste.push_back("./img/testxyh_O3.png");
			animacionesJugadorOeste.push_back("./img/testxyh_O4.png");

			animacionesJugadorNoroeste.push_back("./img/testxyh_NO1.png");
			animacionesJugadorNoroeste.push_back("./img/testxyh_NO2.png");
			animacionesJugadorNoroeste.push_back("./img/testxyh_NO3.png");
			animacionesJugadorNoroeste.push_back("./img/testxyh_NO4.png");
			
			animacionesJugador.push_back(animacionesJugadorNorte);
			animacionesJugador.push_back(animacionesJugadorNoreste);
			animacionesJugador.push_back(animacionesJugadorEste);
			animacionesJugador.push_back(animacionesJugadorSudeste);
			animacionesJugador.push_back(animacionesJugadorSur);
			animacionesJugador.push_back(animacionesJugadorSudoeste);
			animacionesJugador.push_back(animacionesJugadorOeste);
			animacionesJugador.push_back(animacionesJugadorNoroeste);

			Posicion posicionPersonaje;
			posicionPersonaje.x = 0;
			posicionPersonaje.y = 0;

			ControladorEvento controladorEvento;
			ModeloLoop modeloLoop;
			ModeloNivel modeloNivel;
			ModeloEntidad modeloJugador(1, 1, 200, posicionPersonaje, true, ALTO_MATRIZ, ANCHO_MATRIZ, 15);
			ModeloScroll modeloScroll(ANCHO_PANTALLA, ALTO_PANTALLA, ANCHO_MATRIZ, ALTO_MATRIZ, 20, 0, 0, modeloJugador.id());
			VistaEntidadPrueba vistaJugador;
			//VistaEntidad vistaJugador(0, 0, 70, 50, 0, 0, 15, 1000, listaAnimaciones, true);
			VistaScrollPrueba vistaScroll(&vistaJugador);

			vistaScroll.setPantalla(pantalla);
			vistaJugador.setPantalla(pantalla);
			
//			controladorEvento.agregarObservador(modeloLoop.obtenerObservadorEvento());

			modeloNivel.setAltoTiles(ALTO_MATRIZ);
			modeloNivel.setAnchoTiles(ANCHO_MATRIZ);
			modeloNivel.agregarScroll(&modeloScroll);
			modeloNivel.agregarJugador(&modeloJugador);

			std::list<Observador*> listaObservadoresJugador;
			listaObservadoresJugador.push_back(&vistaJugador);
//			modeloNivel.agregarObservadoresJugador(listaObservadoresJugador);
			
			std::list<Observador*> listaObservadoresScroll;
			listaObservadoresScroll.push_back(&vistaScroll);
//			modeloNivel.agregarObservadoresScroll(listaObservadoresScroll);
			
			while (!salir) {
				if (SDL_PollEvent(&evento)) {
					if (evento.type == SDL_MOUSEMOTION)
						controladorEvento.setPosicionMouseXY(evento.motion.x, evento.motion.y);
					else if (evento.type == SDL_MOUSEBUTTONDOWN)
						controladorEvento.setClicMouseBotonIzquierdo(1);
					else if (evento.type == SDL_MOUSEBUTTONUP)
						controladorEvento.setClicMouseBotonIzquierdo(0);
				}
				
				modeloLoop.loop(modeloNivel);

				vistaScroll.graficar();

				salir = (evento.type == SDL_QUIT);
			}

			SDL_Quit();
		}

		Servidor();
		
		virtual ~Servidor();

		// Inicia el Modelo Juego
		bool iniciar();

		// Inicia el loop de Modelo Juego
		void loop();

		void destruirEntidades();
};

// TODO: Sacar los vincular observadores