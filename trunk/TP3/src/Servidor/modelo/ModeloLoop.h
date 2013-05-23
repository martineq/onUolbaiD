#pragma once

#include "ModeloNivel.h"
#include "ModeloEvento.h"
#include "../../utils/Temporizador/Temporizador.h"

class ModeloLoop {

	private:
		ModeloEvento _modeloEvento;
		unsigned long tiempoUltimoChequeo;

		void congelarJugadoresConError(ModeloNivel& modeloNivel);
		void chequearConexion(ModeloNivel& modeloNivel);

	public:
		ModeloLoop();
		virtual ~ModeloLoop();
		void setProxyControladorEvento(ProxyControladorEvento* pProxyEvento);
		bool loop(ModeloNivel& modeloNivel);
};
