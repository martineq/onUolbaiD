#pragma once

#include "./VistaNivel.h"
#include "./VistaLoop.h"
#include "./ImageLoader.h"
#include "../../utils/yaml/ParserYaml.h"
#include "../Controlador/ControladorEvento.h"

class VistaFactory{

	private:
		void crearJugadorConScroll(ParserYaml::stJuego juego, VistaNivel& vistaNivel,SDL_Surface* pantalla);
		void crearEntidades(ParserYaml::stJuego juego, VistaNivel& vistaNivel);
		void crearControladorScroll(ParserYaml::stJuego juego, ControladorEvento* evento);

	public:
		VistaFactory(void);
		~VistaFactory(void);

		bool crearVistaNivel(VistaNivel& vistaNivel,VistaLoop& vistaLoop,ControladorEvento* evento);
};

// TODO: Ahora la creación de Proxys se realiza en el factory. Implementar