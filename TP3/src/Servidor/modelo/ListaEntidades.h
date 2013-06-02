#pragma once

#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include "Posicion.h"
#include "ModeloEntidad.h"

class ListaEntidades {
	private:
		std::multimap<std::pair<int, int>, ModeloEntidad*> _entidades;
		Mutex _mutexEntidades;
		std::list<ModeloEntidad*> _entidadesMoviles;
		Mutex _mutexEntidadesMoviles;

	public:
		ListaEntidades();

		virtual ~ListaEntidades();

		void agregarEntidad(ModeloEntidad* entidad);

		void agregarEntidadMovil(ModeloEntidad* entidadMovil);

		ModeloEntidad* detectarColision(ModeloEntidad* entidad, Posicion posicion);

		bool posicionOcupada(Posicion posicion);

		void removerEntidad(ModeloEntidad* entidad);

		void removerEntidadMovil(ModeloEntidad* entidadMovil);
};
