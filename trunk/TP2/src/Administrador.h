#pragma once

#include "./Servidor/Servidor.h"
#include "./Cliente/Cliente.h"
#include "./utils/Observador/Observador.h"
#include "./utils/Log/Log.h"

// Include para las pruebas. Para agregar pruebas nuevas, agregarlas en esa clase.
#include "./utils/Pruebas/Pruebas.h"

class Administrador{

	private:
		bool modoServidor;
		Servidor* servidor;
		Cliente* cliente;

	public:
		Administrador(void);
		~Administrador(void);
		void setModoServidor(bool modoServidor);	// Seteo el modo en que va a correr el adminstrador (Servidor o Cliente)
		bool iniciar(void);							// Inicia el servidor o cliente, según corresponda
		void loop(void);							// Inicia el loop correspondiente

		// Solo para correr pruebas, no influye en el proyecto del juego
		void correrPruebas(void);

};
