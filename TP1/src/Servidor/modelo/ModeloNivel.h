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

		// Getters
		std::list <ModeloEntidad*> getListaJugadores(void);
		std::list <ModeloScroll*> getListaScroll(void);
		std::list <ModeloEntidad*> getListaEntidades(void);

		// Setters
		void agregarObservadoresScroll(std::list<Observador*>);
		void agregarObservadoresEntidad(std::list<Observador*>);
		void agregarJugador(ModeloEntidad* pJugador);
		void agregarEntidad(ModeloEntidad* pJugador);
		void agregarScroll(ModeloScroll* pScroll);

};

