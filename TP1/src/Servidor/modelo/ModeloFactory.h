#pragma once

#include "./ModeloNivel.h"
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
// + Agregar un ID a cada entidad y a cada scroll para la vinculación a la hora del uso del patron observer