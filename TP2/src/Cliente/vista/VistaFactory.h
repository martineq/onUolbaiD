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
			// Datos de mi jugador
			ProxyModeloEntidad::stEntidad entidadJugador;					// Lo recibo desde el Servidor
			// Entidades del escenario que no son jugadores
			ParserYaml::stEscenario escenario;								// Lo recibo desde el Servidor
			std::list<int> listaIdEntidades;								// Lo recibo desde el Servidor
			// Otros atributos que se leen del yaml
			ParserYaml::stConfiguracion configuracion;
			ParserYaml::stPantalla pantalla;
			std::list<ParserYaml::stEntidad> listaEntidades;
		};
		VistaFactory::stVistaJuegoElegido juegoElegido;

		// Recepción de todos los datos necesarios para crear la Vista y el Controlador
		bool conectarSocket(SocketCliente* pSocket);
		bool recibirArchivos(SocketCliente* pSocket);
		bool recibirListaDeArchivos(const char* directorioElegido,SocketCliente* pSocket);
		bool recibirEscenario(std::list<ParserYaml::stEscenario>& listaEscenarios,SocketCliente* pSocket);
		bool recibirProtagonista(SocketCliente* pSocket,std::string nombreUsuario,std::string nombrePersonaje);
		bool recibirOtrosJugadores(VistaNivel& vistaNivel,SocketCliente* pSocket);
		void asignarEscenarioElegido(std::string nombreEscenario,std::list<ParserYaml::stEscenario>& listaEscenarios);
		void menuSeleccionUsuarioPersonaje(std::string& nombreUsuario,std::string& nombrePersonaje);

		// Creación de la Vista
		bool crearElementosVista(VistaNivel& vistaNivel,VistaLoop& vistaLoop,SocketCliente* pSocket);
		void crearJugadorConScroll(VistaNivel& vistaNivel,SDL_Surface* pantalla,SocketCliente* pSocket);
		void crearEntidadesNoJugadores(VistaNivel& vistaNivel);
		void crearJugadorSinScroll(VistaNivel& vistaNivel,ProxyModeloEntidad::stEntidad& entidad,SocketCliente* pSocket);

		// Creación del Controlador
		bool crearElementosControlador(VistaNivel& vistaNivel,VistaLoop& vistaLoop,ControladorEvento* evento,SocketCliente* pSocket);
		void crearControladorScroll(ControladorEvento* evento);		
		void crearProxyControladorEvento(ControladorEvento* evento,SocketCliente* pSocket);
		void vincularScroll(VistaNivel& vistaNivel,ControladorEvento* evento);

	public:
		VistaFactory(void);
		~VistaFactory(void);

		bool crearNivel(VistaNivel& vistaNivel,VistaLoop& vistaLoop,ControladorEvento* evento,SocketCliente* pSocket);
};
