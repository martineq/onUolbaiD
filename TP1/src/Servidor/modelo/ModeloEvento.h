#pragma once

#include <math.h>

#include "../../utils/Constantes/Constantes.h"
#include "../../utils/Observador/Observador.h"
#include "../../Cliente/controlador/ControladorEvento.h"
#include "ModeloNivel.h"

class ModeloEvento : public Observador {
	private:
		ModeloNivel* _modeloNivel;
		int mouseClickDerecho;
		int mousePosX;
		int mousePosY;

		void obtenerTile(int xp, int yp, int &xt, int &yt);

	public:
		ModeloEvento();
		
		~ModeloEvento();

		void actualizar(Observable*);

		// Asigna el nivel al que le va a pasar los eventos
		void asignarModeloNivel(ModeloNivel*);


		int getMouseClickDerecho();
		int getMousePosX();
		int getMousePosY();
};