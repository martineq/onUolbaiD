#pragma once

#include "./VistaFactory.h"
#include "./VistaNivel.h"
#include "./VistaLoop.h"
#include "../../utils/Sockets/SocketCliente.h"

class VistaJuego{

	private:
		VistaFactory vistaFactory;
		VistaNivel vistaNivel;
		VistaLoop vistaLoop;
		SDL_Surface *pantalla,*fondo,*textSurface;	

	public:
		VistaJuego(void);
		~VistaJuego(void);

		bool iniciar(SocketCliente* pSocket,ControladorEvento* evento,std::string mote,std::string personaje);	// Inicia el VistaFactory y el ControladorEvento
		bool loop(void);												// Inicia el VistaLoop y le pasa el VistaNivel
		
		void destruirEntidades();
};
