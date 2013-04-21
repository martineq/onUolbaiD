#pragma once

#include <SDL.h>
#include "./modelo/ModeloJuego.h"
#include "../utils/Sockets/SocketServidor.h"

class Servidor{

	private:
		ModeloJuego modeloJuego;
		SocketServidor socket;

	public:
		Servidor();
		virtual ~Servidor();

		// Inicia el Modelo Juego
		bool iniciar();

		// Inicia el loop de Modelo Juego
		void loop();

		void destruirEntidades();
};
