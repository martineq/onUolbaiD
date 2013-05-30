#pragma once

#include "ModeloEntidad.h"
#include "ModeloJugador.h"

class ModeloJugador;

class ModeloItem {
	private:
		ModeloEntidad* _modeloEntidad;
		bool _disponible;
		Mutex _mutex;

		ModeloItem(const ModeloItem &modeloItem);

		ModeloItem& operator=(const ModeloItem &modeloItem);

	public:
		ModeloItem(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloItem();

		bool disponible();

		void disponible(bool disponible);

		ModeloEntidad* modeloEntidad();

		ProxyModeloEntidad::stEntidad stEntidad();

		virtual void aplicar(ModeloJugador* jugador) = 0;
};
