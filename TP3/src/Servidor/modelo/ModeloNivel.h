#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include "./ModeloEntidad.h"
#include "../../utils/Observador/Identificable.h"
#include "../../utils/Hilos/Mutex.h"

class ModeloNivel {
	private:
		int altoTiles;
		int anchoTiles;

		std::list<ModeloEntidad*> jugadores;
		Mutex mutexJugadores;

		std::multimap<std::pair<int, int>, ModeloEntidad*> entidades;
		Mutex mutexEntidades;

		int jugadoresConectados;
		Mutex mutexJugadoresConectados;

		ModeloEntidad* obtenerEntidad(int id);

		void destruirListaJugadores();
		void destruirListaEntidades();

		void decrementarJugadores(void);

	public:
		ModeloNivel();
		virtual ~ModeloNivel();

		// Getters
		std::list<ModeloEntidad*> getListaJugadores();

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
		void congelarJugador(int id);

		ModeloEntidad* obtenerJugador(int id);

		bool actualizar();

		bool posicionOcupada(Posicion);

		bool chequearConexion();

		int cantidadJugadores(void);
		
		void incrementarJugadores(void);

		void destruirListas();
};
