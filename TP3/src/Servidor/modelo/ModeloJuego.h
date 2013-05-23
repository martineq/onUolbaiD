#pragma once

#include "./ModeloFactory.h"
#include "./ModeloNivel.h"
#include "./ModeloLoop.h"
#include "../../utils/HilosJuego/HiloReceptor.h"
#include "../../utils/Hilos/Mutex.h"
#include "../../utils/Sockets/SocketServidor.h"

class ModeloJuego {

	private:
		ModeloFactory _modeloFactory;
		ModeloNivel _modeloNivel;
		ModeloLoop _modeloLoop;
		HiloReceptor* pHiloReceptor;

	public:
		ModeloJuego();
		
		virtual ~ModeloJuego();

		bool iniciarEscenario(SocketServidor* pSocket);
		bool iniciarRecepcion(SocketServidor* pSocket);

		bool loop();

		void finalizarRecepcion(void);

		int cantidadJugadores(void);

		void destruirEntidades();
};
