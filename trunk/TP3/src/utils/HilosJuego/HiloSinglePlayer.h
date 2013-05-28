#pragma once

#include "../Hilos/Hilo.h"
#include "../../Cliente/Cliente.h"
#include "../../Servidor/Servidor.h"

class HiloSinglePlayer: public Hilo{

	public:
		struct stParametrosSinglePlayer{
			bool esServidor;
			Cliente* pCliente;
			Servidor* pServidor;
			std::string mote;
			std::string personaje;
		};

	private:
		HiloSinglePlayer::stParametrosSinglePlayer parametrosRun;

		void* run(void* parametro); // Se invoca a "this->start" (heredada de la clase Hilo) para que se use el run con hilo

	public:
		HiloSinglePlayer(void);
		~HiloSinglePlayer(void);

		// Inicio de actividad
		void correrSinglePlayer(HiloSinglePlayer::stParametrosSinglePlayer parametrosRun);

};

