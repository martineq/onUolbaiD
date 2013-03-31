#pragma once

#include "./VistaNivel.h"
#include "../../utils/yaml/ParserYaml.h"

class VistaFactory{

	private:
		void crearJugadorConScroll(ParserYaml::stJuego juego, VistaNivel& vistaNivel);
		void crearEntidades(ParserYaml::stJuego juego, VistaNivel& vistaNivel);

	public:
		VistaFactory(void);
		~VistaFactory(void);

		bool crearVistaNivel(VistaNivel& vistaNivel);
};
