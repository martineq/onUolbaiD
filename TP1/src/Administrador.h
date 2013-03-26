#pragma once

#include "./Servidor/Servidor.h"
#include "./Cliente/Cliente.h"

// Include para las pruebas. Para agregar pruebas nuevas, agregarlas en esa clase.
#include "./utils/Pruebas/Pruebas.h"


#include "utils\Pruebas\Pruebas.h" // Dani
#include "Servidor\modelo\ModeloEntidad.h" // Dani
#include "Cliente\controlador\ControladorJuego.h" // Dani
#include "Cliente\vista\VistaLoop.h" // Dani

class Administrador{

	private:
		Servidor servidor;
		Cliente cliente;

		VistaLoop vistaLoop; // Dani
		ControladorJuego controlador; // Dani
	public:
		Administrador(void);
		~Administrador(void);
		void loopPrincipal(); // Dani

		// Solo para correr pruebas, no influye en el proyecto del juego
		void correrPruebas(void);

};
