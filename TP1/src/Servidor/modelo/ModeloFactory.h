#pragma once

#include "./ModeloNivel.h"
#include "../../utils/yaml/ParserYaml.h"

class ModeloFactory{

	public:
		ModeloFactory(void);
		~ModeloFactory(void);

		bool crearModeloNivel(ModeloNivel& modeloNivel);

};
