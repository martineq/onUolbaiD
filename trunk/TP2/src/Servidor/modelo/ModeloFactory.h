#pragma once

#include "./ModeloNivel.h"
#include "./ModeloEntidad.h"
#include "../../utils/yaml/ParserYaml.h"

class ModeloFactory{

	private:
		void crearJugador(ParserYaml::stJuego juego, ModeloNivel& modeloNivel);
		void crearEntidades(ParserYaml::stJuego juego, ModeloNivel& modeloNivel);

	public:
		ModeloFactory(void);
		~ModeloFactory(void);

		bool crearModeloNivel(ModeloNivel& modeloNivel);
};

// TODO: Ahora la creación de ProxyModeloEntidad y ProxyControladorEvento se realiza en el factory. Implementar
// TODO: Ahora el agregarObservador... se realiza en el factory, a la par de la creación del ProxyModeloEntidad. Implementar
// TODO: crearJugadorConScroll tiene que recibir el ModeloLoop para agregar el observador