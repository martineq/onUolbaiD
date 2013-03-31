#pragma once

#include <math.h>	// Lo agregué porque me tiraba: modeloevento.cpp(10) : error C3861: 'floor': no se encontró el identificador
#include "../../utils/Constantes/Constantes.h"
#include "../../utils/Observador/Observador.h"
#include "../../Cliente/controlador/ControladorEvento.h"
#include "ModeloNivel.h"

class ModeloEvento : public Observador {
	private:
		ModeloNivel* _modeloNivel;

		void obtenerTile(int xp, int yp, int &xt, int &yt);

	public:
		ModeloEvento();
		
		~ModeloEvento();

		void actualizar(Observable*);

		// Asigna el nivel al que le va a pasar los eventos
		void asignarModeloNivel(ModeloNivel*);
};