#pragma once

#include "./SocketServidor.h"
#include "./SocketCliente.h"
#include "../Serializacion/Serializadora.h"
#include "../LectorDirectorios/LectorDirectorios.h"

class MenuSocket{

	private:
		SocketServidor* serv;
		SocketCliente* cli;
		std::vector<long> ids;

		std::string menuVisual();

		void cicloConfigServidor(int cantClientes,bool clientesSonIndividuales);
		void cicloConfigCliente(bool clientesEsIndividual);

		void cicloJuegoServidor();
		void cicloJuegoCliente();

		void cicloArchivoServidor();
		void cicloArchivoCliente();
		bool cicloArchivoServidor2();
		bool cicloArchivoCliente2();
		bool cicloArchivoServidor3();
		bool cicloArchivoCliente3();

	public:
		MenuSocket(void);
		~MenuSocket(void);
		void prueba(void);
};

// Chequear si se están usando todos los métodos necesarios de Servidor y Cliente para cumplir con un caso real