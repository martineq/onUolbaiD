#pragma once

#include <iostream>
#include <string>
#include <list>
#include "./VistaScroll.h"
#include "./VistaEntidad.h"
#include "../../utils/Constantes/Constantes.h"

class VistaNivel{

	private:
		VistaScroll* scroll;
		VistaEntidad* jugador;
		std::list<VistaEntidad*> listaEntidades;

		double alto;
		double ancho;
		double altoNivel;
		double anchoNivel;

		void destruirListaEntidades();
		void destruirScroll();

	public:
		VistaNivel();
		~VistaNivel();

		// Getters
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