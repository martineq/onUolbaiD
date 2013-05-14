#pragma once

#include <list>
#include <math.h>
#include "ModeloNivel.h"
#include "../../utils/Observador/Observador.h"
#include "../../utils/Proxy/ProxyControladorEvento.h"

class ModeloEvento{
	private:
		std::list<ProxyControladorEvento::stEvento> listaEventos;
		ProxyControladorEvento* pProxyEvento; // Al ProxyEvento lo uso para tomar eventos de a uno hasta que se repita un ID
		ProxyControladorEvento::stEvento eventoEnEspera;
		bool hayEventoEnEspera;

	public:
		ModeloEvento();
		
		virtual ~ModeloEvento();

		int getIdJugador();
		int getMousePosX();
		int getMousePosY();
		bool getMouseClickIzquierdo();
		bool getKeyA();
		bool getKeyS();
		bool errorEnSocket();
		bool finalizoElJuego();
		bool getActualizado();
		int getIdDestinatarioChat();
		std::string getMensajeChat();

		void setProxyControladorEvento(ProxyControladorEvento* pProxyEvento);
		void cargarProximoEvento(void); 
		std::list<int> getClientesConError(void);
};
