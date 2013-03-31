#pragma once

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

// TODO: Agregar bool para saber si son datos actualizados por el patron observer