#pragma once

#include "../../utils/Sockets/SocketCliente.h"
#include "../vista/VistaNivel.h"
#include "../vista/VistaEntidad.h"
#include "ControladorLoop.h"

class ControladorJuego{
	private:
		ControladorLoop controladorLoop;	

	public:
		ControladorJuego(void);
		~ControladorJuego(void);
		bool loop(VistaNivel* nivel); // Inicia el ModeloLoop y le pasa el ModeloNivel
		ControladorLoop* getControladorLoop(void);
		void asignarChat(VistaChat* vistaChat);
};
