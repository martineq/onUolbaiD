#pragma once

#include "./vista/VistaJuego.h"
#include "./controlador/ControladorJuego.h"
#include "../utils/Sockets/SocketCliente.h"

class Cliente{

	private:
		VistaJuego vistaJuego;
		ControladorJuego controladorJuego;
		SocketCliente socket;

		bool iniciar(void);		// Inicia el VistaJuego y ControladorJuego
		void loop(void);
		
	public:
		Cliente(void);
		virtual ~Cliente(void);

		bool correrJuego(void);
		void destruirEntidades();

};

// TODO: Implementar iniciar() y loop() con todo lo de sockets