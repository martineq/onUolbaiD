#pragma once

#include "./ModeloEntidad.h"
#include "./ModeloScroll.h"
#include "../../utils/Observador/Observador.h"

class ModeloNivel{

	private:
		std::list <ModeloEntidad> jugadores;
		std::list <ModeloEntidad> entidadesNivel;
		std::list <ModeloScroll> listaScroll;

	public:
		ModeloNivel();
		~ModeloNivel(void);

		void agregarObservadoresScroll(std::list<Observador*>);
		void agregarObservadoresEntidad(std::list<Observador*>);


};

