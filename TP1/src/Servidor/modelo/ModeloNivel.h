#pragma once

#include "./ModeloEntidad.h"
#include "./ModeloScroll.h"
#include "../../utils/Observador/Observador.h"
#include "../../utils/Observador/Identificable.h"

class ModeloNivel {
	private:
		int altoTiles;
		int anchoTiles;
		std::list<ModeloEntidad*> listaJugadores;
		std::list<ModeloScroll*> listaScroll;
		std::list<ModeloEntidad*> listaEntidades;

		ModeloEntidad* obtenerJugador(int id);
		ModeloScroll* obtenerScroll(int id);
		ModeloEntidad* obtenerEntidad(int id);

	public:
		ModeloNivel();
		virtual ~ModeloNivel();

		// Getters
		std::list<ModeloEntidad*> getListaJugadores();
		std::list<ModeloScroll*> getListaScroll();
		std::list<ModeloEntidad*> getListaEntidades();
		
		int getAltoTiles();
		int getAnchoTiles();

		// Setters
		void setAltoTiles(int alto);
		void setAnchoTiles(int ancho);

		void agregarObservadoresJugador(std::list<Observador*> listaObservadoresJugador);
		void agregarObservadoresEntidad(std::list<Observador*> listaObservadoresEntidad);
		void agregarObservadoresScroll(std::list<Observador*> listaObservadoresScroll);

		void agregarJugador(ModeloEntidad *jugador);
		void agregarEntidad(ModeloEntidad *entidad);
		void agregarScroll(ModeloScroll *scroll);

		void removerJugador(ModeloEntidad *jugador);
		void removerEntidad(ModeloEntidad *entidad);
		void removerScroll(ModeloScroll *scroll);

		void moverScroll(int mouseX, int mouseY, int id);
		void moverJugador(int tileX, int tileY, int id);

		bool actualizar(int id);
};

// TODO: Ver la forma de asegurar que el ID de ModeloEntidad y VistaEntidad coincidan. 