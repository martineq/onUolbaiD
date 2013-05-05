#pragma once

#include "./VistaNivel.h"
#include "./VistaLoop.h"
#include "./ImageLoader.h"
#include "../../utils/yaml/ParserYaml.h"
#include "../Controlador/ControladorEvento.h"
#include "../../utils/Sockets/SocketCliente.h"
#include "../../utils/Log/Log.h"
#include "../../utils/Serializacion/Serializadora.h"

class VistaFactory{

	private:
		struct stVistaJuegoElegido{
			// Mi jugador
			int idJugador;													// Lo recibo desde el Servidor
			ParserYaml::stProtagonista protagonista;						// Lo recibo desde el Servidor
			// Otros Jugadores
			std::list<ParserYaml::stProtagonista> listaDeOtrosJugadores;	// Lo recibo desde el Servidor
			std::list<int> listaIdDeOtrosJugadores;							// Lo recibo desde el Servidor
			// Entidades del escenario que no son jugadores
			ParserYaml::stEscenario escenario;								// Lo recibo desde el Servidor
			std::list<int> listaIdEntidades;								// Lo recibo desde el Servidor
			// Otros atributos que se leen del yaml
			ParserYaml::stConfiguracion configuracion;
			ParserYaml::stPantalla pantalla;
			std::list<ParserYaml::stEntidad> listaEntidades;
		};

		// Recepción de todos los datos necesarios para crear la Vista y el Controlador
		bool conectarSocket(SocketCliente* pSocket);
		bool recibirArchivos(SocketCliente* pSocket);
		bool recibirListaDeArchivos(const char* directorioElegido,SocketCliente* pSocket);
		bool recibirEscenario(std::list<ParserYaml::stEscenario>& listaEscenarios,ParserYaml::stEscenario& escenario,std::list<int>& listaIdEntidades,SocketCliente* pSocket);
		bool recibirProtagonista(std::list<ParserYaml::stProtagonista>& listaProtagonistas,int& idJugador,ParserYaml::stProtagonista protagonista,SocketCliente* pSocket);
		bool recibirOtrosJugadores(std::list<ParserYaml::stProtagonista> listaDeOtrosJugadores,std::list<int>,SocketCliente* pSocket);
		void asignarEscenarioElegido(std::string nombreEscenario,std::list<ParserYaml::stEscenario>& listaEscenarios,ParserYaml::stEscenario& escenario);
		bool recibirCadenaSerializada(std::string& cadenaRecibida,SocketCliente* pSocket);
		
		// Creación de la Vista
		bool crearElementosVista(stVistaJuegoElegido& juego,VistaNivel& vistaNivel,VistaLoop& vistaLoop,SocketCliente* pSocket);
		void crearJugadorConScroll(stVistaJuegoElegido& juego,VistaNivel& vistaNivel,SDL_Surface* pantalla,SocketCliente* pSocket);
		void crearEntidades(stVistaJuegoElegido& juego, VistaNivel& vistaNivel);
		void crearJugadorSinScroll(stVistaJuegoElegido& juego, VistaNivel& vistaNivel,SDL_Surface* pantalla,SocketCliente* pSocket);

		// Creación del Controlador
		bool crearElementosControlador(stVistaJuegoElegido& juego,VistaNivel& vistaNivel,VistaLoop& vistaLoop,ControladorEvento* evento,SocketCliente* pSocket);
		void crearControladorScroll(stVistaJuegoElegido& juego,ControladorEvento* evento);		
		void crearProxyControladorEvento(ControladorEvento* evento,SocketCliente* pSocket);
		void vincularScroll(VistaNivel& vistaNivel,ControladorEvento* evento);

	public:
		VistaFactory(void);
		~VistaFactory(void);

		bool crearNivel(VistaNivel& vistaNivel,VistaLoop& vistaLoop,ControladorEvento* evento,SocketCliente* pSocket);
};
