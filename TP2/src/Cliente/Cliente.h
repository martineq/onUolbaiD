#pragma once

#include "./vista/VistaJuego.h"
#include "./controlador/ControladorJuego.h"
#include "../utils/Sockets/SocketCliente.h"

class Cliente{

	private:
		VistaJuego vistaJuego;
		ControladorJuego controladorJuego;
		SocketCliente socket;

	public:
		Cliente(void);
		~Cliente(void);
		bool iniciar(void);		// Inicia el VistaJuego y ControladorJuego
		void loop(void);
		void destruirEntidades();

};
