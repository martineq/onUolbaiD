#pragma once

#include <list>
#include "ModeloNivel.h"
#include "ModeloEvento.h"
#include "../../utils/Proxy/ProxyControladorEvento.h"

class ModeloLoop {

	private:
		ModeloEvento _modeloEvento;
		ProxyControladorEvento proxyControlador;

	public:
		ModeloLoop();
		
		virtual ~ModeloLoop();

		bool loop(ModeloNivel& modeloNivel);
};

// TODO: Ver si se creará ModeloEvento conteniendo una lista de todos los eventos de todos los jugadores
//       O si se crea una std::list<ModeloEvento> con una cantidad igual a la de Clientes conectados