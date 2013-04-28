#pragma once

#include "./ConexionCliente.h"
#include "./SocketApp.h"

class ConexionServidor{

	private:
		SocketApp socketApp;

	public:
		ConexionServidor(void);
		~ConexionServidor(void);

		// Inicialización y cierre de conexión
		bool iniciarAplicacion(void);
		bool finalizarAplicacion(void);
		bool abrir(void);
		bool cerrar(void);

		// Funciones propias del servidor
		bool enlazarConexion(int puerto);
		bool escuchar(void);
		bool aceptarCliente(ConexionCliente* cliente);
		bool selectLectura(void);
		bool selectEscritura(void);

};
