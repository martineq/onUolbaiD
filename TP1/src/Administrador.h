#pragma once

#include "./Servidor/Servidor.h"
#include "./Cliente/Cliente.h"

// Include para las pruebas. Para agregar pruebas nuevas, agregarlas en esa clase.
#include "./utils/Pruebas/Pruebas.h"

class Administrador{

	private:
		Servidor servidor;
		Cliente cliente;

	public:
		Administrador(void);
		~Administrador(void);

		// Solo para correr pruebas, no influye en el proyecto del juego
		void correrPruebas(void);

};
