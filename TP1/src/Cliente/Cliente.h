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
		Observador* obtenerObservadorJugador(void);
		Observador* obtenerObservadorScroll(void);
		std::list<Observador*> obtenerObservadoresEntidad(void);
		void agregarObservadorEventos(Observador* observador);
		bool loopControl(void);
		bool loopVista(void);

		void destruirEntidades();

};
