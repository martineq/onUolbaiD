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
		double altoDePantallaEnPixel;
		double anchoDePantallaEnPixel;
		double altoNivelEnPixel;
		double anchoNivelEnPixel;
		int altoDeNivelEnTiles;
		int anchoDeNivelEnTiles;

		void destruirListaEntidades();
		void destruirScroll();

	public:
		static bool ordenadorEntidades(VistaEntidad* entidad1, VistaEntidad* entidad2);

		VistaNivel();
		~VistaNivel();

		// Getters
		Observador* obtenerObservadorJugador(void);
		Observador* obtenerObservadorScroll(void);
		std::list<Observador*> obtenerObservadoresEntidad(void);
		VistaScroll* getScroll(void);
		VistaEntidad* getJugador(void);
		std::list<VistaEntidad*> getListaEntidades(void);
		int getAltoDePantallaEnPixel(void);
		int getAnchoDePantallaEnPixel(void);
		double getAltoDeNivelEnPixel();
		double getAnchoDeNivelEnPixel();
		int getAltoDeNivelEnTiles();
		int getAnchoDeNivelEnTiles();

		// Setters
		void agregarJugador(VistaEntidad* pJugador);
		void agregarEntidad(VistaEntidad* pEntidad);
		void agregarScroll(VistaScroll* pScroll);
		void agregarTamanioNivel(double,double);
		void setAltoDePantallaEnPixel(int alto);
		void setAnchoDePantallaEnPixel(int ancho);
		void setAltoDeNivelEnTiles(int);
		void setAnchoDeNivelEnTiles(int);

		void destruirEntidadesYScroll();
};