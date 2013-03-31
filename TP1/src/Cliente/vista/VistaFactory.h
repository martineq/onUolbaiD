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


// TODO: Tareas:
// + Agregar un ID a cada entidad y a cada scroll para la vinculaci�n a la hora del uso del patron observer