#pragma once
#include "utils\Pruebas\Pruebas.h"
#include "Servidor\modelo\ModeloEntidad.h"
#include "Cliente\controlador\ControladorJuego.h"
#include "Cliente\vista\VistaLoop.h"
class Administrador{
	private:
		VistaLoop vistaLoop;
		ControladorJuego controlador;
	public:
		Administrador(void);
		~Administrador(void);
		void loopPrincipal();

};
