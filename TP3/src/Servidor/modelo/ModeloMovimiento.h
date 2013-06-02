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
		ListaEntidades* _listaEntidades;
		std::list<Posicion> _posiciones;
		Posicion _posicionSiguiente;
		DWORD _instanteUltimoCambioEstado;

		bool agregarTile(char* mapaTilesCerrados, std::list<Tile>* tilesAbiertos, Posicion posicion, Posicion posicionDestino, Tile* padre, int distancia);

		Posicion calcularPosicionDestino(Posicion posicionDestino);

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

		void asignarListaEntidades(ListaEntidades* listaEntidades);

		void cambiarEstado();

		void detener();
};
