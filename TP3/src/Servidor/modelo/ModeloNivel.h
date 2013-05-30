#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include "ModeloEntidad.h"
#include "ModeloJugador.h"
#include "ModeloItem.h"
#include "../../utils/Observador/Identificable.h"
#include "../../utils/Hilos/Mutex.h"

class ModeloNivel {
	private:
		int altoTiles;
		int anchoTiles;

		std::list<ModeloEntidad*> entidadesMoviles;
		Mutex mutexEntidadesMoviles;

		std::multimap<std::pair<int, int>, ModeloEntidad*> entidades;
		Mutex mutexEntidades;

		std::list<ModeloJugador*> jugadores;
		Mutex mutexJugadores;

		std::multimap<std::pair<int, int>, ModeloItem*> items;
		Mutex mutexItems;

		int jugadoresConectados;
		Mutex mutexJugadoresConectados;

		void destruirListaJugadores();
		void destruirListaEntidades();

		void decrementarJugadores(void);

	public:
		ModeloNivel();
		virtual ~ModeloNivel();

		// Getters
		std::list<ModeloJugador*> getJugadores();
		std::list<ModeloEntidad*> getEntidadesMoviles();

		int getAltoTiles();
		int getAnchoTiles();

		// Setters
		void setAltoTiles(int alto);
		void setAnchoTiles(int ancho);

		void agregarJugador(ModeloJugador* jugador);
		void agregarItem(ModeloItem* item);
		void agregarEntidad(ModeloEntidad* entidad);
		
		void removerJugador(ModeloJugador* jugador);
		void removerItem(ModeloItem* item);
		void removerEntidad(ModeloEntidad* entidad);
		
		void ejecutarAccionJugador(int tileX, int tileY, int id);
		void congelarJugador(int id);

		ModeloJugador* obtenerJugador(int id);
		ModeloJugador* obtenerJugador(Posicion posicion);
		ModeloItem* obtenerItem(Posicion posicion);

		bool actualizar();

		bool posicionOcupada(Posicion);

		bool chequearConexion();

		int cantidadJugadores(void);
		
		void incrementarJugadores(void);

		void destruirListas();
};
