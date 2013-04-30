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
#include "../Cliente/Cliente.h"

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

	public:
		//TODO: Borrar
		static void prueba() {
			Cliente cliente;
			Servidor servidor;

			cliente.iniciar();
			servidor.iniciar();

			cliente.loopVista();
			getchar();

			cliente.destruirEntidades();
			servidor.destruirEntidades();
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
