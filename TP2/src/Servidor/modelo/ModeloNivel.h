#pragma once

#include "./ModeloEntidad.h"
#include "../../utils/Observador/Identificable.h"

class ModeloNivel {
	private:
		int altoTiles;
		int anchoTiles;
		std::list<ModeloEntidad*> listaJugadores;
		std::list<ModeloEntidad*> listaEntidades;

		ModeloEntidad* obtenerJugador(int id);
		ModeloEntidad* obtenerEntidad(int id);
		
		void destruirListaJugadores();
		void destruirListaEntidades();
		void destruirListaScroll();

	public:
		ModeloNivel();
		virtual ~ModeloNivel();

		// Getters
		std::list<ModeloEntidad*> getListaJugadores();
		std::list<ModeloEntidad*> getListaEntidades();
		
		int getAltoTiles();
		int getAnchoTiles();

		// Setters
		void setAltoTiles(int alto);
		void setAnchoTiles(int ancho);

		void agregarJugador(ModeloEntidad *jugador);
		void agregarEntidad(ModeloEntidad *entidad);
		
		void removerJugador(ModeloEntidad *jugador);
		void removerEntidad(ModeloEntidad *entidad);
		
		void moverJugador(int tileX, int tileY, int id);

		bool actualizar(int id);

		void destruirListas();
};
