#pragma once

#include "./ModeloEntidad.h"
#include "./ModeloScroll.h"
#include "../../utils/Observador/Observador.h"

class ModeloNivel{

	private:
		std::list <ModeloEntidad*> listaJugadores;
		std::list <ModeloScroll*> listaScroll;
		std::list <ModeloEntidad*> listaEntidades;

	public:
		ModeloNivel();
		~ModeloNivel(void);

		void agregarObservadoresScroll(std::list<Observador*>);
		void agregarObservadoresEntidad(std::list<Observador*>);
		void agregarJugador(double x, double y, double alto, double ancho, double velocidad);
		void agregarEntidad(double x, double y, double alto, double ancho, double velocidad);
		void agregarScroll(double x, double y, double alto, double ancho, double velocidad, double margen);

};

// TODO: Pasar todos las coordenadas pertenecientes a <ModeloScroll> y <ModeloEntidad> de int a double.