#pragma once

#include <SDL.h>
//#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <list>
#include "./VistaScroll.h"
#include "./VistaEntidad.h"
#include "../../utils/Constantes/Constantes.h"
#include "../../utils/Observador/Observador.h"

class VistaNivel{

	private:
		VistaScroll* scroll;
		std::list<VistaEntidad*> listaEntidades;
		double alto;
		double ancho;

	public:
		VistaNivel();
		~VistaNivel();

		// Getters
		Observador* obtenerObservadorJugador(void);
		Observador* obtenerObservadorScroll(void);
		std::list<Observador*> obtenerObservadoresEntidad(void);
		VistaScroll* getScroll(void);
		std::list<VistaEntidad*> getListaEntidades(void);
		int getAltoPantalla(void);
		int getAnchoPantalla(void);

		// Setters
		void agregarJugador(VistaEntidad* pJugador);
		void agregarEntidad(VistaEntidad* pEntidad);
		void agregarScroll(VistaScroll* pScroll);
		void setAltoPantalla(int alto);
		void setAnchoPantalla(int ancho);
};