#pragma once

#include "../Sockets/SocketCliente.h"
#include "../Sockets/SocketServidor.h"

class ProxyControladorEvento{

	public:
		struct stEvento{
			int id;
			int mouseX;
			int mouseY;
			bool mouseClickIzquierdo;
			bool mouseDentroPantalla;
	};

	private:
		SocketCliente* pCliente;
		SocketServidor* pServidor;
	
	public:
		ProxyControladorEvento(void);
		~ProxyControladorEvento(void);

		void setSocketCliente(SocketCliente* pCliente);
		void setSocketServidor(SocketServidor* pServidor);
		bool enviarEvento(ProxyControladorEvento::stEvento entidad);
		bool recibirEvento(ProxyControladorEvento::stEvento& evento);
		
};

// TODO: Implementar todos los métodos necesarios para la parte de cliente y servidor