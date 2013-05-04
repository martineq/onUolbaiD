#pragma once

#include "./ModeloNivel.h"
#include "./ModeloEntidad.h"
#include "./ModeloLoop.h"
#include "../../utils/Constantes/Constantes.h"
#include "../../utils/yaml/ParserYaml.h"
#include "../../utils/Sockets/SocketServidor.h"

class ModeloFactory{

	private:
		struct stModeloJuegoElegido{
			std::list<ParserYaml::stEntidad> listaEntidades;
			ParserYaml::stEscenario escenario;
			ParserYaml::stProtagonista protagonista;
			ParserYaml::stConfiguracion configuracion;
			ParserYaml::stPantalla pantalla;
		};
		
		void crearEntidades(stModeloJuegoElegido& juego, ModeloNivel& modeloNivel,SocketServidor* pSocket);
		ParserYaml::stEscenario elegirEscenario(std::list<ParserYaml::stEscenario>& listaEscenarios,SocketServidor* pSocket);
		ParserYaml::stProtagonista elegirProtagonista(std::list<ParserYaml::stProtagonista>& listaProtagonistas,SocketServidor* pSocket);

	public:
		ModeloFactory(void);
		~ModeloFactory(void);

		bool crearNivel(ModeloNivel& modeloNivel,ModeloLoop& modeloLoop,SocketServidor* pSocket);
		void crearJugador(ModeloNivel& modeloNivel,SocketServidor* pSocket);
};
