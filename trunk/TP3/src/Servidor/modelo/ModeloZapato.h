#pragma once

#include "ModeloItem.h"
#include "../../utils/Constantes/Constantes.h"

class ModeloZapato : public ModeloItem {
	public:
		ModeloZapato(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloZapato();
		
		void aplicar(ModeloJugador* jugador);
};
