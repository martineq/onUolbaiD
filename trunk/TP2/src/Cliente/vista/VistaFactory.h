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
			std::list<ParserYaml::stEntidad> listaEntidades;
			ParserYaml::stEscenario escenario;
			ParserYaml::stProtagonista protagonista;
			ParserYaml::stConfiguracion configuracion;
			ParserYaml::stPantalla pantalla;
		};

		bool conectarSocket(SocketCliente* pSocket);
		bool recibirArchivos(SocketCliente* pSocket);
		bool recibirListaDeArchivos(const char* directorioElegido,SocketCliente* pSocket);
		ParserYaml::stEscenario elegirEscenario(std::list<ParserYaml::stEscenario>& listaEscenarios,SocketCliente* pSocket);
		ParserYaml::stProtagonista elegirProtagonista(std::list<ParserYaml::stProtagonista>& listaProtagonistas,SocketCliente* pSocket);

		bool crearElementosVista(stVistaJuegoElegido& juego,VistaNivel& vistaNivel,VistaLoop& vistaLoop,SocketCliente* pSocket);
		void crearJugadorConScroll(stVistaJuegoElegido& juego,VistaNivel& vistaNivel,SDL_Surface* pantalla,SocketCliente* pSocket);
		void crearEntidades(stVistaJuegoElegido& juego, VistaNivel& vistaNivel);

		bool crearElementosControlador(stVistaJuegoElegido& juego,VistaNivel& vistaNivel,VistaLoop& vistaLoop,ControladorEvento* evento,SocketCliente* pSocket);
		void crearControladorScroll(stVistaJuegoElegido& juego,ControladorEvento* evento);		
		void crearProxyControladorEvento(ControladorEvento* evento,SocketCliente* pSocket);
		void vincularScroll(VistaNivel& vistaNivel,ControladorEvento* evento);

	public:
		VistaFactory(void);
		~VistaFactory(void);

		bool crearNivel(VistaNivel& vistaNivel,VistaLoop& vistaLoop,ControladorEvento* evento,SocketCliente* pSocket);
};

// TODO: Ver si conectarSocket() va a recibir el puerto y el IP desde consola o de un archivo de configuración