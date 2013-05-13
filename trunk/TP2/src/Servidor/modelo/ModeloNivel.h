#pragma once

#include "./ModeloEntidad.h"
#include "../../utils/Observador/Identificable.h"
#include "../../utils/Hilos/Mutex.h"

class ModeloNivel {
	private:
		int altoTiles;
		int anchoTiles;

		std::list<ModeloEntidad*> listaJugadores;
		Mutex mutexListaJugadores;

		std::list<ModeloEntidad*> listaEntidades;
		Mutex mutexListaEntidades;

		int jugadoresConectados;
		Mutex mutexJugadoresConectados;

		ModeloEntidad* obtenerJugador(int id);
		ModeloEntidad* obtenerEntidad(int id);
		
		void destruirListaJugadores();
		void destruirListaEntidades();

		void decrementarJugadores(void);

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
		
		void jugadorMover(int tileX, int tileY, int id);
		void jugadorAtacar(int id);
		void jugadorDefender(int id);
		void congelarJugador(int idJugador);

		bool actualizar();

		int cantidadJugadores(void);
		
		void incrementarJugadores(void);

		void destruirListas();
};
