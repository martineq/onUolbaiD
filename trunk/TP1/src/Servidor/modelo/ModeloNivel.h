#pragma once

#include "./ModeloEntidad.h"
#include "./ModeloScroll.h"
#include "../../utils/Observador/Observador.h"
#include "../../Cliente/vista/VistaEntidad.h"
#include "../../Cliente/vista/VistaScroll.h"

class ModeloNivel{

	private:

		int altoNivel;
		int anchoNivel;
		std::list <ModeloEntidad*> listaJugadores;
		std::list <ModeloScroll*> listaScroll;
		std::list <ModeloEntidad*> listaEntidades;


	public:
		ModeloNivel();
		~ModeloNivel(void);

		// Getters
		std::list<ModeloEntidad*> getListaJugadores(void);
		std::list<ModeloScroll*> getListaScroll(void);
		std::list<ModeloEntidad*> getListaEntidades(void);
		int getAltoNivel(void);
		int getAnchoNivel(void);

		// Setters
		void agregarObservadoresScroll(std::list<Observador*> listaObservadoresScroll);
		void agregarObservadoresEntidad(std::list<Observador*> listaObservadoresEntidad);

		void agregarJugador(ModeloEntidad *jugador);
		void agregarEntidad(ModeloEntidad *entidad);
		void agregarScroll(ModeloScroll *);
		void setAltoNivel(int alto);
		void setAnchoNivel(int ancho);


		void removerJugador(ModeloEntidad *jugador);
		void removerEntidad(ModeloEntidad *entidad);
		void removerScroll(ModeloScroll *scroll);

		void moverScroll (int mouseX, int mouseY, int id);
};

// TODO: Ver la forma de asegurar que el ID de ModeloEntidad y VistaEntidad coincidan. 