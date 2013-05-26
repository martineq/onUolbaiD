#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include "ModeloEntidad.h"
#include "ModeloJugador.h"
#include "../../utils/Observador/Identificable.h"
#include "../../utils/Hilos/Mutex.h"

class ModeloNivel {
	private:
		int altoTiles;
		int anchoTiles;

		std::list<ModeloJugador*> jugadores;
		Mutex mutexJugadores;

		std::list<ModeloEntidad*> entidadesMoviles;
		Mutex mutexEntidadesMoviles;

		std::multimap<std::pair<int, int>, ModeloEntidad*> entidades;
		Mutex mutexEntidades;

		int jugadoresConectados;
		Mutex mutexJugadoresConectados;

		void destruirListaJugadores();
		void destruirListaEntidades();

		void decrementarJugadores(void);

	public:
		ModeloNivel();
		virtual ~ModeloNivel();

		// Getters
		std::list<ModeloJugador*> getListaJugadores();
		std::list<ModeloEntidad*> getListaEntidadesMoviles();

		int getAltoTiles();
		int getAnchoTiles();

		// Setters
		void setAltoTiles(int alto);
		void setAnchoTiles(int ancho);

		void agregarJugador(ModeloJugador* jugador);
		void agregarEntidad(ModeloEntidad* entidad);
		
		void removerJugador(ModeloJugador* jugador);
		void removerEntidad(ModeloEntidad* entidad);
		
		void jugadorMover(int tileX, int tileY, int id);
		void jugadorAtacar(int id);
		void jugadorDefender(int id);
		void congelarJugador(int id);

		ModeloJugador* obtenerJugador(int id);
		ModeloEntidad* obtenerEntidadMovil(int id);

		bool actualizar();

		bool posicionOcupada(Posicion);

		bool chequearConexion();

		int cantidadJugadores(void);
		
		void incrementarJugadores(void);

		void destruirListas();
};
