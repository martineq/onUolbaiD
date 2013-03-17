#pragma once

#include <fstream>
#include <list>
#include <yaml.h>
#include "../Constantes.h"
#include "../Log/Log.h"

class ParserYaml{

	private:

		bool chequeoArchivo(std::string ruta);
		int leerYamlInt(const YAML::Node& nodo);
		std::string leerYamlString(const YAML::Node& nodo);

	public:

		ParserYaml(void);
		~ParserYaml(void);
		int cargaJuego(void);


};

