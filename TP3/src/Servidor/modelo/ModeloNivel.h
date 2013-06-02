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

		ListaEntidades listaEntidades;
		ListaItems listaItems;

		std::list<ModeloJugador*> jugadores;
		Mutex mutexJugadores;

		std::list<ModeloJugador*> enemigos;
		Mutex mutexEnemigos;

		int jugadoresConectados;
		Mutex mutexJugadoresConectados;

		void destruirListaJugadores();
		void destruirListaEnemigos();

		void decrementarJugadores(void);

	public:
		ModeloNivel();
		virtual ~ModeloNivel();

		// Getters
		std::list<ModeloJugador*> getJugadores();
		std::list<ModeloJugador*> getEnemigos();

		int getAltoTiles();
		int getAnchoTiles();

		// Setters
		void setAltoTiles(int alto);
		void setAnchoTiles(int ancho);

		void agregarJugador(ModeloJugador* jugador);
		void agregarEnemigo(ModeloJugador* enemigo);
		void agregarItem(ModeloItem* item);
		void agregarEntidad(ModeloEntidad* entidad);
		
		void ejecutarAccionJugador(int tileX, int tileY, int id);
		void congelarJugador(int id);

		ModeloJugador* obtenerJugador(int id);
		ModeloJugador* obtenerJugador(Posicion posicion);
		ModeloJugador* obtenerEnemigo(Posicion posicion);
		ModeloItem* obtenerItem(Posicion posicion);

		bool actualizar();

		bool posicionOcupada(Posicion);

		bool chequearConexion();

		int cantidadJugadores(void);
		
		void incrementarJugadores(void);

		void iniciarNuevosJugadores(void);

		void destruirListas();
};
