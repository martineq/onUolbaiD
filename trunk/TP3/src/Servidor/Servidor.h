#pragma once

#include "./modelo/ModeloJuego.h"
#include "../utils/Sockets/SocketServidor.h"
#include "../utils/Temporizador/Temporizador.h"

class Servidor{

	private:
		ModeloJuego modeloJuego;
		SocketServidor socket;
		
		bool iniciar(bool singlePlayer);
		void loop();
		void loopSinglePlayer();

	public:

		Servidor();
		virtual ~Servidor();

		bool correrJuego(void);
		void correrJuegoSinglePlayer(void);
		bool iniciarSinglePlayer(void);
		void destruirEntidades();
};
