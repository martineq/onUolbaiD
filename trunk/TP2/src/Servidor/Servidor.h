#pragma once

#include "./modelo/ModeloJuego.h"
#include "../utils/Sockets/SocketServidor.h"
#include "../utils/Temporizador/Temporizador.h"

class Servidor{

	private:
		ModeloJuego modeloJuego;
		SocketServidor socket;

		bool iniciar();
		void loop();

	public:
		Servidor();
		virtual ~Servidor();

		bool correrJuego(void);
		void destruirEntidades();
};
