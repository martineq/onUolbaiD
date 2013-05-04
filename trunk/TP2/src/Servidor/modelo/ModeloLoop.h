#pragma once

#include "ModeloNivel.h"
#include "ModeloEvento.h"

class ModeloLoop {

	private:
		ModeloEvento _modeloEvento;

		void procesarJugadoresEliminados(ModeloNivel& modeloNivel,int* jugadoresConectados,Mutex* mutexJugadoresConectados);

	public:
		ModeloLoop();
		virtual ~ModeloLoop();
		void setProxyControladorEvento(ProxyControladorEvento* pProxyEvento);
		bool loop(ModeloNivel& modeloNivel,int* jugadoresConectados,Mutex* mutexJugadoresConectados);
};
