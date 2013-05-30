#pragma once

#include "ModeloItem.h"
#include "../../utils/Constantes/Constantes.h"

class ModeloBotella : public ModeloItem {
	public:
		ModeloBotella(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloBotella();
		
		void aplicar(ModeloJugador* jugador);
};
