#pragma once

#include "../Sockets/SocketCliente.h"
#include "../Sockets/SocketServidor.h"
#include "../Serializacion/Serializadora.h"

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
			bool finalizoElJuego;

			// Datos para actualizar el chat
			int idReceptorChat;
			std::string mensajeChat;

	};

	private:
		SocketCliente* pCliente;
		SocketServidor* pServidor;
	
	public:
		ProxyControladorEvento(void);
		~ProxyControladorEvento(void);

		// Para setear al principio
		void setSocketCliente(SocketCliente* pCliente);
		void setSocketServidor(SocketServidor* pServidor);

		// Para usar en el momento de juego. Debe estar seteado el modo Masivo
		bool enviarEvento(ProxyControladorEvento::stEvento entidad);			// Lo usa el lado Cliente
		bool recibirEvento(ProxyControladorEvento::stEvento& evento);			// Lo usa el lado Servidor

		void serializar(Serializadora& s,ProxyControladorEvento::stEvento& evento);
		void hidratar(Serializadora& s,ProxyControladorEvento::stEvento& evento);

		std::list<int> getClientesConError(void);

		// Auxiliares
		static void cargarStEvento(ProxyControladorEvento::stEvento& evento,int id,bool errorEnSocket,int mouseX,int mouseY,
			bool teclaA,bool teclaS,bool mouseClickIzquierdo,bool finalizoElJuego,int idReceptorChat,std::string mensajeChat);
		
};
