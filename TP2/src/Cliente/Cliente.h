#pragma once

#include "./vista/VistaJuego.h"
#include "./controlador/ControladorJuego.h"
#include "../utils/Sockets/SocketCliente.h"
#include "../utils/Temporizador/Temporizador.h"

class Cliente{

	private:
		VistaJuego vistaJuego;
		ControladorJuego controladorJuego;
		SocketCliente socket;

		bool iniciar(std::string mote,std::string personaje);		// Inicia el VistaJuego y ControladorJuego
		void loop(void);
		
	public:
		Cliente(void);
		virtual ~Cliente(void);

		bool correrJuego(std::string mote,std::string personaje);
		void destruirEntidades();

};
