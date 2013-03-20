#pragma once

#include <fstream>
#include <list>
#include <yaml-cpp/yaml.h>
#include "../Constantes.h"
#include "../Log/Log.h"

class ParserYaml{

	private:

		bool chequeoArchivo(std::string ruta);
		int leerNodoYamlInt(const YAML::Node& nodo);
		std::string leerNodoYamlString(const YAML::Node& nodo);
		void notificarErrorLectura(std::string tipoDato, std::string msgError, bool& lecturaOk);

	public:

		ParserYaml(void);
		~ParserYaml(void);
		int cargaJuego(void);


};

