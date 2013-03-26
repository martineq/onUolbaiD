#pragma once

#include <list>
#include "./ModeloEntidad.h"
#include "./ModeloScroll.h"

class ModeloNivel{

	private:
		std::list <ModeloEntidad> jugadores;
		std::list <ModeloEntidad> entidadesNivel;
		std::list <ModeloScroll> listaScroll;

		// Pendiente por si se agregan cosas que se muevan automáticamente
		//std::list <ModeloEntidad> entidadesAutomaticas;

	public:
		ModeloNivel();
		~ModeloNivel(void);

		

		int agregarJugador (ModeloEntidad jugador);
		int removerJugador (ModeloEntidad jugador);
		int agregarEntidadNivel (ModeloEntidad entidad);
		int removerEntidadNivel (ModeloEntidad entidad);

		// Pendiente por si se agregan cosas que se muevan automáticamente
		//void animarEntidadesAutomaticas ();

		void limpiarNivel();

};

