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
		VistaEntidad* jugador;
		std::list<VistaEntidad*> listaEntidades;
		double alto;
		double ancho;
		double altoNivel;
		double anchoNivel;

		static bool ordenadorEntidades(VistaEntidad* entidad1, VistaEntidad* entidad2);

		void destruirListaEntidades();
		void destruirScroll();

	public:
		VistaNivel();
		~VistaNivel();

		// Getters
		Observador* obtenerObservadorJugador(void);
		Observador* obtenerObservadorScroll(void);
		std::list<Observador*> obtenerObservadoresEntidad(void);
		VistaScroll* getScroll(void);
		VistaEntidad* getJugador(void);
		std::list<VistaEntidad*> getListaEntidades(void);
		int getAltoPantalla(void);
		int getAnchoPantalla(void);
		double getAltoNivel();
		double getAnchoNivel();

		// Setters
		void agregarJugador(VistaEntidad* pJugador);
		void agregarEntidad(VistaEntidad* pEntidad);
		void agregarScroll(VistaScroll* pScroll);
		void agregarTamanioNivel(double,double);
		void setAltoPantalla(int alto);
		void setAnchoPantalla(int ancho);

		void destruirEntidadesYScroll();
};