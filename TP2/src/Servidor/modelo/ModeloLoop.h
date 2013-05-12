#pragma once

#include "ModeloNivel.h"
#include "ModeloEvento.h"

class ModeloLoop {

	private:
		ModeloEvento _modeloEvento;

		void congelarJugadoresConError(ModeloNivel& modeloNivel);

	public:
		ModeloLoop();
		virtual ~ModeloLoop();
		void setProxyControladorEvento(ProxyControladorEvento* pProxyEvento);
		bool loop(ModeloNivel& modeloNivel);
};
