#pragma once

#include "./VistaNivel.h"
#include "./VistaLoop.h"
#include "./ImageLoader.h"
#include "../../utils/yaml/ParserYaml.h"

class VistaFactory{

	private:
		void crearJugadorConScroll(ParserYaml::stJuego juego, VistaNivel& vistaNivel,SDL_Surface* pantalla);
		void crearEntidades(ParserYaml::stJuego juego, VistaNivel& vistaNivel);

	public:
		VistaFactory(void);
		~VistaFactory(void);

		bool crearVistaNivel(VistaNivel& vistaNivel,VistaLoop& vistaLoop);
};

// TODO: Ahora la creación de Proxys se realiza en el factory. Implementar