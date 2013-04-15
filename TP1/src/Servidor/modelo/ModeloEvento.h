#pragma once

#include <math.h>

#include "../../utils/Observador/Observador.h"
#include "../../Cliente/controlador/ControladorEvento.h"
#include "ModeloNivel.h"

class ModeloEvento : public Observador {
	private:
		int _mouseClickIzquierdo;
		int _mouseX;
		int _mouseY;
		bool _actualizado;

	public:
		ModeloEvento();
		
		virtual ~ModeloEvento();

		void actualizar(Observable* observable);

		int getMouseClickDerecho();
		int getMousePosX();
		int getMousePosY();
		bool getActualizado();

		void setActualizado(bool actualizado);
};
