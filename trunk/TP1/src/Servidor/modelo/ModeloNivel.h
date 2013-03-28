#pragma once

#include "./ModeloEntidad.h"
#include "./ModeloScroll.h"

class ModeloNivel{

	private:
		std::list <ModeloEntidad> jugadores;
		std::list <ModeloEntidad> entidadesNivel;
		std::list <ModeloScroll> listaScroll;

	public:
		ModeloNivel();
		~ModeloNivel(void);

};

