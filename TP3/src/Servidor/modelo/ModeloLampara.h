#pragma once

#include "ModeloItem.h"
#include "../../utils/Constantes/Constantes.h"

class ModeloLampara : public ModeloItem {
	public:
		ModeloLampara(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloLampara();
		
		void aplicar(ModeloJugador* jugador);
};
