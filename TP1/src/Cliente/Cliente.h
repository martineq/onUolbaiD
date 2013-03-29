#pragma once

#include "./vista/VistaJuego.h"
#include "./controlador/ControladorJuego.h"
#include "../utils/Observador/Observador.h"

class Cliente{

	private:
		VistaJuego vistaJuego;
		ControladorJuego controladorJuego;

	public:
		Cliente(void);
		~Cliente(void);
		bool iniciar(void);		// Inicia el VistaJuego y ControladorJuego
		Observador* obtenerObservadorScroll(void);
		std::list<Observador*> obtenerObservadoresEntidad(void);
		void agregarObservadorEventos(Observador*);
		bool loop(void);		// Inicia el VistaLoop y ControladorLoop

};
