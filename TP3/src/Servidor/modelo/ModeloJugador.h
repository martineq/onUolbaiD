#pragma once

#include <stdlib.h>
#include <list>
#include "Posicion.h"
#include "ModeloEntidad.h"

class ModeloJugador {
	private:
		Posicion _posicionInicial;
		ModeloEntidad* _modeloEntidad;
		ModeloJugador* _enemigo;

		ModeloJugador(const ModeloJugador &modeloJugador);

		ModeloJugador& operator=(const ModeloJugador &modeloJugador);
		
	public:
		ModeloJugador(int alto, int ancho, int velocidad, Posicion posicion, bool esJugador, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad, std::string nombreJugador);

		virtual ~ModeloJugador();

		bool estaCongelado();

		void estaCongelado(bool estaCongelado);

		ModeloEntidad* modeloEntidad();

		void atacar(ModeloJugador* enemigo);

		void cambiarEstado();

		void lastimar(int danio);

		void mover(Posicion posicion);
};
