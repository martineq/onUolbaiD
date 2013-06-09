#pragma once

#include "ModeloJugador.h"

class ModeloMision {
	private:
		ModeloJugador* _ganador;

	protected:
		void asignarGanador(ModeloJugador* ganador);

	public:
		ModeloMision();

		virtual ~ModeloMision();

		ModeloJugador* ganador();

		virtual void agregarJugador(ModeloJugador* jugador) = 0;

		virtual void agregarEnemigo(ModeloJugador* enemigo) = 0;

		virtual void agregarItem(ModeloItem* item) = 0;

		virtual void calcularGanador(ModeloJugador* jugador) = 0;
};

class ModeloMisionCarnicero {
	public:
		void agregarJugador(ModeloJugador* jugador);

		void agregarEnemigo(ModeloJugador* enemigo);

		void agregarItem(ModeloItem* item);

		void calcularGanador(ModeloJugador* jugador);
};

class ModeloMisionBanderas {
	public:
		void agregarJugador(ModeloJugador* jugador);

		void agregarEnemigo(ModeloJugador* enemigo);

		void agregarItem(ModeloItem* item);

		void calcularGanador(ModeloJugador* jugador);
};
