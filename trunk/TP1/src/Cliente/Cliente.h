#pragma once

#include "./vista/VistaJuego.h"
#include "./controlador/ControladorJuego.h"

class Cliente{

	private:
		VistaJuego vistajuego;
		ControladorJuego controladorJuego;
	
	public:
		Cliente(void);
		~Cliente(void);

};
