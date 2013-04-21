#pragma once

#include "./vista/VistaJuego.h"
#include "./controlador/ControladorJuego.h"

class Cliente{

	private:
		VistaJuego vistaJuego;
		ControladorJuego controladorJuego;

	public:
		Cliente(void);
		~Cliente(void);
		bool iniciar(void);		// Inicia el VistaJuego y ControladorJuego
		void loop(void);
		void destruirEntidades();

};

// TODO: hacer el this->vincularObservadores(); para el scroll
