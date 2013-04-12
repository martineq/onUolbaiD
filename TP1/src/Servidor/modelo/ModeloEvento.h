#pragma once

#include <math.h>

#include "../../utils/Observador/Observador.h"
#include "../../Cliente/controlador/ControladorEvento.h"
#include "ModeloNivel.h"

class ModeloEvento : public Observador {
	private:
		ModeloNivel* _modeloNivel;
		int _mouseClickDerecho;
		int _mouseX;
		int _mouseY;
		bool _actualizado;

	public:
		ModeloEvento();
		
		virtual ~ModeloEvento();

		void actualizar(Observable* observable);

		// Asigna el nivel al que le va a pasar los eventos
		void asignarModeloNivel(ModeloNivel* modeloNivel);

		int getMouseClickDerecho();
		int getMousePosX();
		int getMousePosY();
		bool getActualizado();

		void setActualizado(bool actualizado);
};
