#pragma once

#include <list>

#include "../utils/Observador/Observador.h"
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
#define ALTO_MATRIZ 20
#define ANCHO_MATRIZ 20
#define DESPLAZAMIENTO_SCROLL 1

class Servidor {
	private:
		ModeloJuego modeloJuego;

		//TODO: Borrar
		static SDL_Surface* cargarImagen(const char* archivoImagen) {
			SDL_Surface* imagen = SDL_LoadBMP(archivoImagen);
			SDL_Surface* imagenOptimizada = SDL_DisplayFormat(imagen);
			
			SDL_FreeSurface(imagen);

			Uint32 colorFondo = SDL_MapRGB(imagenOptimizada->format, 0xFF, 0xFF, 0xFF);
			SDL_SetColorKey(imagenOptimizada, SDL_SRCCOLORKEY, colorFondo);

			return imagenOptimizada;
		}

		//TODO: Borrar
		class VistaEntidadPrueba1 : public Observador, public Identificable {
			private:
				SDL_Surface* _nivel;
				SDL_Surface* _personaje;
				int _x;
				int _y;
				
			public:
				VistaEntidadPrueba1() {
					this->_personaje = Servidor::cargarImagen("img/SORA_S1.bmp");
					this->_x = 0;
					this->_y = 0;
				}

				virtual ~VistaEntidadPrueba1() {
					SDL_FreeSurface(this->_personaje);
				}

				void actualizar(Observable* s) {
					ModeloEntidad* modeloEntidad = (ModeloEntidad*)s;
					this->_x = modeloEntidad->pixelSiguiente().x;
					this->_y = modeloEntidad->pixelSiguiente().y;
				}

				void setPantalla(SDL_Surface* nivel) {
					this->_nivel = nivel;
				}

				void graficar() {
					SDL_Rect destino;

					destino.h = ALTO_IMAGEN;
					destino.w = ANCHO_IMAGEN;
					destino.x = this->_x;
					destino.y = this->_y;

					SDL_BlitSurface(this->_personaje, NULL, this->_nivel, &destino);
				}

				int id() const {
					return 1;
				}
		};

		//TODO: Borrar
		class VistaEntidadPrueba2 : public Observador, public Identificable {
			private:
				SDLutil* _utilidadSDL;
				Posicion _posicion;
				
			public:
				VistaEntidadPrueba2() {
					this->_utilidadSDL = new SDLutil(0, 0, ANCHO_IMAGEN, ALTO_IMAGEN, "img/testxyh_S1.png");
				}

				virtual ~VistaEntidadPrueba2() {
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
					this->_utilidadSDL->limpiar();
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
		class VistaScrollPrueba1 : public Observador, public Identificable {
			private:
				SDL_Surface* _pantalla;
				SDL_Surface* _nivel;
				SDL_Rect _destinoScroll;
				
			public:
				VistaScrollPrueba1(SDL_Surface* pantalla, SDL_Surface* nivel) {
					this->_pantalla = pantalla;
					this->_nivel = nivel;
					this->_destinoScroll.w = ANCHO_PANTALLA;
					this->_destinoScroll.h = ALTO_PANTALLA;
				}

				virtual ~VistaScrollPrueba1() {
				}

				void actualizar(Observable* s) {
					ModeloScroll* modeloScroll = (ModeloScroll*)s;
					
					this->_destinoScroll.x = (Sint16)modeloScroll->getX();
					this->_destinoScroll.y = (Sint16)modeloScroll->getY();
				}

				void graficar() {
					SDL_BlitSurface(this->_nivel, &this->_destinoScroll, this->_pantalla, NULL);
					SDL_UpdateRect(this->_pantalla, 0, 0, 0, 0);
				}

				int id() const {
					return 1;
				}
		};

		//TODO: Borrar
		class VistaScrollPrueba2 : public Observador, public Identificable {
			private:
				SDLutil* _utilidadSDL;
				VistaEntidadPrueba2* _vistaEntidad;
				Posicion _destinoScroll;
				SDL_Surface* _pantalla;
				bool _actualizar;
				
				bool entraEnPantalla(VistaEntidadPrueba2* vistaEntidad){
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
				VistaScrollPrueba2(VistaEntidadPrueba2* vistaEntidad) {
					this->_utilidadSDL = new SDLutil(0, 0, ANCHO_TILE, ALTO_TILE, "img/tile.png");
					this->_vistaEntidad = vistaEntidad;
					this->_actualizar = false;
				}

				virtual ~VistaScrollPrueba2() {
				}

				void actualizar(Observable* s) {
					ModeloScroll* modeloScroll = (ModeloScroll*)s;
					
					this->_destinoScroll.x = (Sint16)modeloScroll->getX();
					this->_destinoScroll.y = (Sint16)modeloScroll->getY();
					this->_actualizar = true;
				}

				void setPantalla(SDL_Surface* pantalla) {
					this->_pantalla = pantalla;
					this->_utilidadSDL->setPantalla(pantalla);
				}

				void graficar() {
					int xt = 0, yt = 0, xp = 0, yp = 0;
					Posicion posicionInicial, posicionFinal;
					if (this->_actualizar) {
						this->obtenerTilesLimites(posicionInicial, posicionFinal);

						SDL_FillRect(this->_pantalla, NULL, 0x000000);

						for (xt = posicionInicial.x; xt < posicionFinal.x; xt++) {
							for (yt = posicionInicial.y; yt < posicionFinal.y; yt++) {
								Posicion::convertirTileAPixel(ALTO_MATRIZ, xt, yt, xp, yp);
								this->_utilidadSDL->graficar(xp - this->_destinoScroll.x - (ANCHO_TILE / 2), yp - this->_destinoScroll.y);
							}
						}
						this->_actualizar = false;
					}

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
		static void prueba2() {
			bool salir = false;
			int xt = 0, yt = 0, xp = 0, yp = 0;
			SDL_Event evento;
			
			SDL_Init(SDL_INIT_VIDEO);

			SDL_Surface* pantalla = SDL_SetVideoMode(ANCHO_PANTALLA, ALTO_PANTALLA, 0, 0);
			
			SDLutil utilidadSDL(0, 0, ANCHO_TILE, ALTO_TILE, "./img/tile.png");

			utilidadSDL.setPantalla(pantalla);

			for (xt = 0; xt < 20; xt++) {
				for (yt = 10; yt < 30; yt++) {
					Posicion::convertirTileAPixel(ALTO_MATRIZ, xt, yt, xp, yp);
					utilidadSDL.graficar(xp, yp - 500);
				}
			}

			SDL_UpdateRect(pantalla, 0, 0, 0, 0);
			
			while (!salir) {
				SDL_PollEvent(&evento);
				salir = (evento.type == SDL_QUIT);
			}

			SDL_Quit();
		}

		//TODO: Borrar
		static void prueba() {
			bool salir = false;
			int alto = 0, ancho = 0, dummy = 0, xt = 0, yt = 0, xp = 0, yp = 0;
			Posicion posicionPersonaje;
			//SDL_Rect destinoPersonaje;
			SDL_Event evento;
			
			Posicion::convertirTileAPixel(ALTO_MATRIZ, ANCHO_MATRIZ - 1, ALTO_MATRIZ - 1, dummy, alto);
			Posicion::convertirTileAPixel(ALTO_MATRIZ, ANCHO_MATRIZ - 1, 0, ancho, dummy);

			alto += ALTO_TILE + (ALTO_IMAGEN / 4);
			ancho += ANCHO_TILE / 2;

			SDL_Init(SDL_INIT_VIDEO);

			SDL_Surface* pantalla = SDL_SetVideoMode(ANCHO_PANTALLA, ALTO_PANTALLA, 0, 0);
			/*SDL_Surface* tile = Servidor::cargarImagen("img/tile.bmp");
			SDL_Surface* nivel = SDL_CreateRGBSurface(SDL_SWSURFACE, ancho, alto, 32, 0, 0, 0, 0);*/
			
			std::list<list<string>> listaAnimaciones;
			std::list<string> listaN;
			std::list<string> listaNE;
			std::list<string> listaE;
			std::list<string> listaSE;
			std::list<string> listaS;
			std::list<string> listaSO;
			std::list<string> listaO;
			std::list<string> listaNO;

			listaN.push_back("./img/testxyh_N1.png");
			listaN.push_back("./img/testxyh_N2.png");
			listaN.push_back("./img/testxyh_N3.png");
			listaN.push_back("./img/testxyh_N4.png");
			listaNE.push_back("./img/testxyh_NE1.png");
			listaNE.push_back("./img/testxyh_NE2.png");
			listaNE.push_back("./img/testxyh_NE3.png");
			listaNE.push_back("./img/testxyh_NE4.png");
			listaE.push_back("./img/testxyh_E1.png");
			listaE.push_back("./img/testxyh_E2.png");
			listaE.push_back("./img/testxyh_E3.png");
			listaE.push_back("./img/testxyh_E4.png");
			listaSE.push_back("./img/testxyh_SE1.png");
			listaSE.push_back("./img/testxyh_SE2.png");
			listaSE.push_back("./img/testxyh_SE3.png");
			listaSE.push_back("./img/testxyh_SE4.png");
			listaS.push_back("./img/testxyh_S1.png");
			listaS.push_back("./img/testxyh_S2.png");
			listaS.push_back("./img/testxyh_S3.png");
			listaS.push_back("./img/testxyh_S4.png");
			listaSO.push_back("./img/testxyh_SO1.png");
			listaSO.push_back("./img/testxyh_SO2.png");
			listaSO.push_back("./img/testxyh_SO3.png");
			listaSO.push_back("./img/testxyh_SO4.png");
			listaO.push_back("./img/testxyh_O1.png");
			listaO.push_back("./img/testxyh_O2.png");
			listaO.push_back("./img/testxyh_O3.png");
			listaO.push_back("./img/testxyh_O4.png");
			listaNO.push_back("./img/testxyh_NO1.png");
			listaNO.push_back("./img/testxyh_NO2.png");
			listaNO.push_back("./img/testxyh_NO3.png");
			listaNO.push_back("./img/testxyh_NO4.png");
			
			listaAnimaciones.push_back(listaN);
			listaAnimaciones.push_back(listaNE);
			listaAnimaciones.push_back(listaE);
			listaAnimaciones.push_back(listaSE);
			listaAnimaciones.push_back(listaS);
			listaAnimaciones.push_back(listaSO);
			listaAnimaciones.push_back(listaO);
			listaAnimaciones.push_back(listaNO);

			posicionPersonaje.x = 0;
			posicionPersonaje.y = 0;

			ControladorEvento controladorEvento;
			ModeloLoop modeloLoop;
			ModeloNivel modeloNivel;
			ModeloEntidad modeloJugador(1, 1, 200, posicionPersonaje, true, ALTO_MATRIZ, ANCHO_MATRIZ, 15);
			ModeloScroll modeloScroll(ANCHO_PANTALLA, ALTO_PANTALLA, ANCHO_MATRIZ, ALTO_MATRIZ, 20, 1, 0, 0, modeloJugador.id());
			//VistaEntidadPrueba1 vistaJugador;
			VistaEntidadPrueba2 vistaJugador;
			//VistaEntidad vistaJugador(0, 0, 70, 50, 0, 0, 15, 1000, listaAnimaciones, true);
			//VistaScrollPrueba1 vistaScroll(pantalla, nivel);
			VistaScrollPrueba2 vistaScroll(&vistaJugador);

			vistaScroll.setPantalla(pantalla);
			vistaJugador.setPantalla(pantalla);
			
			controladorEvento.agregarObservador(modeloLoop.obtenerObservadorEvento());

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
			
			/*destinoPersonaje.h = ALTO_TILE;
			destinoPersonaje.w = ANCHO_TILE;*/

			/*for (xt = 0; xt < ANCHO_MATRIZ; xt++) {
				for (yt = 0; yt < ALTO_MATRIZ; yt++) {
					Posicion::convertirTileAPixel(ALTO_MATRIZ, xt, yt, xp, yp);
					destinoPersonaje.x = (Sint16)xp - (ANCHO_TILE / 2);
					destinoPersonaje.y = (Sint16)yp;
					SDL_BlitSurface(tile, NULL, nivel, &destinoPersonaje);
				}
			}*/

			//SDL_BlitSurface(nivel, NULL, pantalla, NULL);
			
			while (!salir) {
				if (SDL_PollEvent(&evento)) {
					if (evento.type == SDL_MOUSEMOTION)
						controladorEvento.setPosicionMouseXY(evento.motion.x, evento.motion.y);
					else if (evento.type == SDL_MOUSEBUTTONDOWN)
						controladorEvento.setClicMouseBotonDerecho(1);
					else if (evento.type == SDL_MOUSEBUTTONUP)
						controladorEvento.setClicMouseBotonDerecho(0);
				}
				
				modeloLoop.loop(modeloNivel);

				//vistaJugador.graficar();
				vistaScroll.graficar();

				salir = (evento.type == SDL_QUIT);
			}

			/*SDL_FreeSurface(tile);
			SDL_FreeSurface(nivel);*/
			SDL_Quit();
		}

		Servidor();
		
		virtual ~Servidor();

		// Inicia el Modelo Juego
		bool iniciar();
		
		void agregarObservadoresJugador(std::list<Observador*>listaObservadoresJugador);

		void agregarObservadoresScroll(std::list<Observador*>listaObservadoresScroll);
		
		void agregarObservadoresEntidad(std::list<Observador*>listaObservadoresEntidad);
		
		Observador* obtenerObservadorEvento();
		
		// Inicia el loop de Modelo Juego
		bool loop();

		void destruirEntidades();
};
