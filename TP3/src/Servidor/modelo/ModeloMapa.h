#pragma once

#include "ModeloItem.h"
#include "../../utils/Constantes/Constantes.h"

class ModeloMapa: public ModeloItem {
	public:
		ModeloMapa(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloMapa();
		
		void aplicar(ModeloJugador* jugador);
};
