#pragma once

#include "./Servidor/Servidor.h"
#include "./Cliente/Cliente.h"
#include "./utils/Log/Log.h"
#include "./utils/HilosJuego/HiloSinglePlayer.h"


// Include para las pruebas. Para agregar pruebas nuevas, agregarlas en esa clase.
#include "./utils/Pruebas/Pruebas.h"

class Administrador{

	private:
		bool modoServidor;
		bool modoUnJugador;
		Servidor* servidor;
		Cliente* cliente;

		void menuLineaComandos(void);
		bool nuevoMenu1();
		bool nuevoMenu2(SDL_Surface *pantalla,TTF_Font * fuente);
		void correrSinglePlayer(std::string mote,std::string personaje);

	public:
		Administrador(void);
		~Administrador(void);
		void correrJuego(std::string mote,std::string personaje);						// Inicia el loop correspondiente

		// Solo para correr pruebas, no influye en el proyecto del juego
		void correrPruebas(void);

};
