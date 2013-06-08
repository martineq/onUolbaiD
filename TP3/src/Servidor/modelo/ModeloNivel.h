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
		ListaJugadores listaJugadores;
		ListaJugadores listaEnemigos;
		ListaJugadores listaGolems;
		ListaItems listaItems;

		int jugadoresConectados;
		Mutex mutexJugadoresConectados;

		void decrementarJugadores(void);

	public:
		ModeloNivel();
		virtual ~ModeloNivel();

		// Getters
		std::list<ModeloJugador*> getJugadores();
		std::list<ModeloJugador*> getEnemigos();
		std::multimap<std::pair<int, int>, ModeloItem*> getItems();

		int getAltoTiles();
		int getAnchoTiles();

		// Setters
		void setAltoTiles(int alto);
		void setAnchoTiles(int ancho);

		void agregarJugador(ModeloJugador* jugador);
		void agregarEnemigo(ModeloJugador* enemigo);
		void agregarItem(ModeloItem* item);
		void agregarEntidad(ModeloEntidad* entidad);
		
		void activarHechizoHielo(int id);
		void ejecutarAccionJugador(int tileX, int tileY, int id);
		void desconectarJugador(int id);

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
