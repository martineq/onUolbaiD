#pragma once

#include "ModeloItem.h"
#include "../../utils/Constantes/Constantes.h"

class ModeloEscudo : public ModeloItem {
	public:
		ModeloEscudo(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloEscudo();
		
		void aplicar(ModeloJugador* jugador);
};
