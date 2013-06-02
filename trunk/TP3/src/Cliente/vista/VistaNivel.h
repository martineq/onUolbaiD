#pragma once

#include <iostream>
#include <string>
#include <list>
#include "./VistaScroll.h"
#include "./VistaEntidad.h"
#include "../Controlador/ControladorScroll.h"
#include "../../utils/Constantes/Constantes.h"

class VistaNivel{

	private:
		VistaScroll* scroll;
		VistaEntidad* jugador;
		ControladorScroll* pControladorScroll;
		std::list<VistaEntidad*> listaOtrosJugadores;
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
		VistaNivel();
		~VistaNivel();
		
		static bool ordenadorEntidades(VistaEntidad* entidad1, VistaEntidad* entidad2);

		// Getters
		VistaScroll* getScroll(void);
		VistaEntidad* getJugador(void);
		std::list<VistaEntidad*> getListaOtrosJugadores(void);
		std::list<VistaEntidad*> getListaEntidades(void);
		int getAltoDePantallaEnPixel(void);
		int getAnchoDePantallaEnPixel(void);
		double getAltoDeNivelEnPixel();
		double getAnchoDeNivelEnPixel();
		int getAltoDeNivelEnTiles();
		int getAnchoDeNivelEnTiles();

		// Setters
		void agregarJugador(VistaEntidad* pJugador);
		void agregarOtroJugador(VistaEntidad* pJugador);
		void agregarEntidad(VistaEntidad* pEntidad);
		void agregarScroll(VistaScroll* pScroll);
		void setControladorScroll(ControladorScroll* pControladorScroll);
		void agregarTamanioNivel(double,double);
		void setAltoDePantallaEnPixel(int alto);
		void setAnchoDePantallaEnPixel(int ancho);
		void setAltoDeNivelEnTiles(int);
		void setAnchoDeNivelEnTiles(int);

		void ordenarJugadores();
		void destruirEntidadesYScroll();
		void reiniciarPosicionScroll();
};