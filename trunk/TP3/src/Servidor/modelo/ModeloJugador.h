#pragma once

#include <list>
#include "Posicion.h"
#include "ModeloEntidad.h"

class ModeloJugador {
	private:
		ModeloEntidad* _modeloEntidad;
		std::list<ModeloJugador*>* _jugadores;
		Mutex* _mutexJugadores;

		ModeloJugador(const ModeloJugador &modeloJugador);

		ModeloJugador& operator=(const ModeloJugador &modeloJugador);
		
	public:
		ModeloJugador(int alto, int ancho, int velocidad, Posicion posicion, bool esJugador, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad, std::string nombreJugador);

		virtual ~ModeloJugador();

		ModeloEntidad* modeloEntidad();

		void asignarJugadores(Mutex* mutexJugadores, std::list<ModeloJugador*>* jugadores);

		void atacar();

		void defender();

		void mover(Posicion posicion);
};
