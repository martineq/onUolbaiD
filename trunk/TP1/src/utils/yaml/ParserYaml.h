#pragma once

#include <fstream>
#include <list>
#include <yaml-cpp/yaml.h>
#include "../Constantes.h"
#include "../Log/Log.h"

class ParserYaml{

	public:
		
		///////////////////////
		// Structs del juego //
		///////////////////////

		struct stPantalla{
			int ancho;
			int alto;
		};

		struct stConfiguracion{
			int velocidadPersonaje;
			int margenScroll;
		};

		struct stEntidad{
			std::string nombre;
			std::string imagen;
			int anchoBase;
			int altoBase;
			int pixelReferenciaX;
			int pixelReferenciaY;
			int fps;
			int delay;
		};

		struct stEntidadDefinida{
			int x;
			int y;
			std::string entidad;
		};

		struct stProtagonista{
			int x;
			int y;
			std::string entidad;
		};

		struct stEscenario{
			std::string nombre;
			int tamanioX;
			int tamanioY;
			std::list <stEntidadDefinida> entidadesDefinidas;
			stProtagonista protagonista; // TODO: Ver si simpre es un solo protagonista o hay que poner una lista
		};

		struct stJuego{
			stPantalla pantalla;
			stConfiguracion configuracion;
			std::list <stEntidad> entidades;
			std::list <stEscenario> escenarios;
			bool juegoValido;
		};

	private:

		// Estructura para guardar todos los datos parseados
		stJuego juego;

		// Funciones privadas para la carga de datos parseados
		void cargaStJuego(YAML::Node& nodoRaiz, ParserYaml::stJuego& juego);
		void cargaStPantalla(const YAML::Node& nodo, stPantalla& pantalla);
		void cargaStConfiguracion(const YAML::Node& nodo, ParserYaml::stConfiguracion& configuracion);
		void cargaListaEntidades(const YAML::Node& nodo, std::list <ParserYaml::stEntidad>& entidades);
		void cargaListaEscenarios(const YAML::Node& nodo, std::list <ParserYaml::stEscenario>& escenarios);
		void cargaStProtagonista(const YAML::Node& nodo, ParserYaml::stProtagonista& protagonista);
		void cargaListaEntidadesDefinidas(const YAML::Node& nodo, std::list <ParserYaml::stEntidadDefinida>& entidadesDefinidas);
		void cargaStEntidad(const YAML::Node& nodo, ParserYaml::stEntidad& entidad);
		void cargaDefaultStEntidad(ParserYaml::stEntidad& entidad);
		void cargaStEscenario(const YAML::Node& nodo, ParserYaml::stEscenario& escenario);
		void cargaStEntidadDefinida(const YAML::Node& nodo, ParserYaml::stEntidadDefinida& entidadDefinida);

		// Funciones privadas auxiliares
		int leerNodoYamlInt(const YAML::Node& nodo);
		std::string leerNodoYamlString(const YAML::Node& nodo);
		bool chequeoArchivo(std::string ruta);
		void notificarErrorLectura(std::string tipoDato,std::string archivo, int linea, std::string msgError, bool& lecturaOk);

	public:

		ParserYaml(void);
		~ParserYaml(void);
		ParserYaml::stJuego cargarConfiguracionDeJuego(void);

};

