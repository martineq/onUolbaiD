#pragma once

#include "./ModeloNivel.h"
#include "./ModeloEntidad.h"
#include "./ModeloLoop.h"
#include "../../utils/Constantes/Constantes.h"
#include "../../utils/yaml/ParserYaml.h"
#include "../../utils/Sockets/SocketServidor.h"
#include "../../utils/Ticket/Ticket.h"
#include "../../utils/Serializacion/Serializadora.h"
#include "../../utils/LectorDirectorios/LectorDirectorios.h"
#include "../../utils/Serializacion/Serializadora.h"
#include "../../utils/Temporizador/Temporizador.h"

class ModeloFactory{

	private:
		struct stModeloJuegoElegido{
			// Atributos que se leen del yaml
			ParserYaml::stEscenario escenario;				// Se elige a partir de consola
			ParserYaml::stConfiguracion configuracion;
			ParserYaml::stPantalla pantalla;
			std::list<ParserYaml::stEntidad> listaEntidades;
			
			// Atributos que se llenan mientras de crean entidades
			std::string nombreEscenario;
			std::list<int> listaIdEntidades;
		};
		ModeloFactory::stModeloJuegoElegido juegoElegido;
		Mutex mutexJuegoElegido;

		// Métodos para ser usados por el factory mismo, el iniciar
		bool elegirEscenario(std::list<ParserYaml::stEscenario>& listaEscenarios);
		void crearEntidades(ModeloNivel& modeloNivel,SocketServidor* pSocket);
		void crearEnemigosAutomaticos(ModeloNivel& modeloNivel,SocketServidor* pSocket);

		// Métodos usados por el HiloConfiguracion
		bool enviarEscenario(SocketServidor* pSocket, int id);
		bool enviarEnemigosAutomaticos(ModeloNivel* modeloNivel,SocketServidor* pSocket, int id);
		bool enviarProtagonista(ModeloNivel* modeloNivel,SocketServidor* pSocket, int& id);
		bool enviarOtrosJugadores(ModeloNivel* modeloNivel,SocketServidor* pSocket,int idMiJugador);
		void crearJugador(ModeloNivel* modeloNivel,ProxyModeloEntidad::stEntidad& stEntidad,SocketServidor* pSocket,std::string nombreJugador,std::string mote, int id);
		bool enviarArchivosDeConfiguracion(SocketServidor* pServidor,int idSocketCliente);
		bool enviarListaDeArchivos(std::vector<std::string> lista,SocketServidor* pServidor,int idSocketCliente);
		ModeloFactory::stModeloJuegoElegido getCopiaJuegoElegido(void);
		ProxyModeloEntidad::stEntidad elegirProtagonista(ModeloNivel* modeloNivel,std::string& nombreUsuario,std::string& nombrePersonaje,SocketServidor* pSocket,int& id);
		std::string obtenerPersonajeLibre(std::list<std::string> listaEntidadesUsadas,std::string personajePedido);

		// Otros
		Posicion generarPosicionAlAzar(ModeloNivel* modeloNivel,ModeloFactory::stModeloJuegoElegido& juegoElegido);

	public:
		ModeloFactory(void);
		~ModeloFactory(void);

		bool crearNivel(ModeloNivel& modeloNivel,ModeloLoop& modeloLoop,SocketServidor* pSocket);
		bool rutinaAgregarNuevoCliente(void* modeloNivel,SocketServidor* pSocket,int id,bool singlePlayer);
};
