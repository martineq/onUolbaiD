#pragma once

#include <math.h>

#include "../../utils/Observador/Observador.h"
#include "../../Cliente/controlador/ControladorEvento.h"
#include "ModeloNivel.h"

class ModeloEvento : public Observador {
	private:
		int _mouseX;
		int _mouseY;
		bool _mouseClickIzquierdo;
		bool teclaA;
		bool teclaS;
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
		bool getTeclaA();
		bool getTeclaS();

		void setActualizado(bool actualizado);
};
