#pragma once

#include "../Sockets/SocketCliente.h"
#include "../Sockets/SocketServidor.h"

class ProxyControladorEvento{

	public:
		struct stEvento{
			// Info para el proxy
			int id;
			bool errorEnSocket; // No hace falta serializar este valor. Esta atributo lo setea el proxy cuando recibe datos (al hidratar). Si el socket me da errror seteo acá en true, sino lo dejo en false
			
			// Datos para actualizar en el evento
			int mouseX;
			int mouseY;
			bool teclaA;
			bool teclaS;
			bool mouseClickIzquierdo;
			bool mouseDentroPantalla;
			bool finalizoElJuego;
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
