#pragma once

#include <math.h>
#include "ModeloNivel.h"
#include "../../utils/Observador/Observador.h"
#include "../../utils/Proxy/ProxyControladorEvento.h"


class ModeloEvento : public Observador {
	private:
		int _mouseX;
		int _mouseY;
		bool _mouseClickIzquierdo;
		bool _mouseDentroPantalla;
		bool _actualizado;

	public:
		ModeloEvento();
		
		virtual ~ModeloEvento();

		void actualizar(Observable* observable);

		int getMousePosX();
		int getMousePosY();
		bool getMouseClickIzquierdo();
		bool getMouseDentroPantalla();
		bool getActualizado();

		void setActualizado(bool actualizado);
};
