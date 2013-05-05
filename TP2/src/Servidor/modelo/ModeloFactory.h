#pragma once

#include "./ModeloNivel.h"
#include "./ModeloEntidad.h"
#include "./ModeloLoop.h"
#include "../../utils/Constantes/Constantes.h"
#include "../../utils/yaml/ParserYaml.h"
#include "../../utils/Sockets/SocketServidor.h"
#include "../../utils/Ticket/Ticket.h"
#include "../../utils/Serializacion/Serializadora.h"

class ModeloFactory{

	private:
		struct stModeloJuegoElegido{
			// Atributos que se leen del yaml
			ParserYaml::stEscenario escenario;				// Se elige a partir de consola o de un archivo de configuracion
			ParserYaml::stConfiguracion configuracion;
			ParserYaml::stPantalla pantalla;
			std::list<ParserYaml::stEntidad> listaEntidades;
			// Atributos que se llenan mientras de crean entidades
			std::string escenarioElegido;
			std::list<int> listaIdEntidades;
		};
		ModeloFactory::stModeloJuegoElegido juegoElegido;

		// Métodos para ser usados por el factory mismo, el iniciar
		bool elegirEscenario(std::list<ParserYaml::stEscenario>& listaEscenarios);
		void crearEntidades(ModeloNivel& modeloNivel,SocketServidor* pSocket);

		// Métodos usados por el HiloConfiguracion
		bool enviarEscenario(SocketServidor* pSocket, int id);
		bool elegirProtagonista(ModeloNivel* modeloNivel,SocketServidor* pSocket, int id);
		bool enviarOtrosJugadores(ModeloNivel* modeloNivel,SocketServidor* pSocket,int idMiJugador);
		void crearJugador(ModeloNivel* modeloNivel,SocketServidor* pSocket, int id);
		
	public:
		ModeloFactory(void);
		~ModeloFactory(void);

		bool crearNivel(ModeloNivel& modeloNivel,ModeloLoop& modeloLoop,SocketServidor* pSocket);
		bool rutinaAgregarNuevoCliente(ModeloNivel* modeloNivel,SocketServidor* pSocket, int id);
};
