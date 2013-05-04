#pragma once

#include <SDL.h>
#include "./modelo/ModeloJuego.h"
#include "../utils/Sockets/SocketServidor.h"

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
