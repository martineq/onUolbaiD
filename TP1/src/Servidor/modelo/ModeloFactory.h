#pragma once

#include "./ModeloNivel.h"
#include "./ModeloEntidad.h"
#include "./ModeloScroll.h"
#include "../../utils/yaml/ParserYaml.h"

class ModeloFactory{

	private:
		void crearJugadorConScroll(ParserYaml::stJuego juego, ModeloNivel& modeloNivel);
		void crearEntidades(ParserYaml::stJuego juego, ModeloNivel& modeloNivel);

	public:
		ModeloFactory(void);
		~ModeloFactory(void);

		bool crearModeloNivel(ModeloNivel& modeloNivel);
};

// TODO: Tareas:
// 