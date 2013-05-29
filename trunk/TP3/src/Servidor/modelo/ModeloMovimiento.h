#pragma once

#include <math.h>
#include <iostream>
#include <map>

#include "../../utils/Constantes/Constantes.h"
#include "../../utils/Observador/Observable.h"
#include "../../utils/Observador/Observador.h"
#include "../../utils/Hilos/Mutex.h"
#include "Posicion.h"
#include "Tile.h"
#include "ModeloEntidad.h"

class ModeloMovimiento : public Observable {
	private:
		int _altoNivel;
		int _anchoNivel;
		ModeloEntidad* _modeloEntidad;
		std::list<ModeloEntidad*>* _entidadesMoviles;
		Mutex* _mutexEntidadesMoviles;
		std::multimap<std::pair<int, int>, ModeloEntidad*>* _entidades;
		Mutex* _mutexEntidades;
		std::list<Posicion> _posiciones;
		Posicion _posicionSiguiente;
		DWORD _instanteUltimoCambioEstado;

		bool agregarTile(char* mapaTilesCerrados, std::list<Tile>* tilesAbiertos, Posicion posicion, Posicion posicionDestino, Tile* padre, int distancia);

		Posicion calcularPosicionDestino(Posicion posicionDestino);

		ModeloEntidad* detectarColision(Posicion posicion);

		int obtenerAlto(int y, ModeloEntidad* modeloEntidad);

		int obtenerAncho(int x, ModeloEntidad* modeloEntidad);

		Posicion obtenerPosicionSiguiente();

		int obtenerX(ModeloEntidad* modeloEntidad);

		int obtenerY(ModeloEntidad* modeloEntidad);

		ModeloMovimiento(const ModeloMovimiento &modeloMovimiento);

		ModeloMovimiento& operator=(const ModeloMovimiento &modeloMovimiento);

	public:
		ModeloMovimiento(int altoNivel, int anchoNivel, ModeloEntidad* modeloEntidad);

		virtual ~ModeloMovimiento();

		Posicion posicionSiguiente();

		void actualizar(Posicion posicion);

		void asignarEntidades(Mutex* mutexEntidades, std::multimap<std::pair<int, int>, ModeloEntidad*>* entidades);

		void asignarEntidadesMoviles(Mutex* mutexEntidadesMoviles, std::list<ModeloEntidad*>* entidadesMoviles);

		void cambiarEstado();

		void detener();
};
