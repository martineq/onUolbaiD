#pragma once

#include "./VistaNivel.h"
#include "./ImageLoader.h"
#include "./VistaMusica.h"
#include "../../utils/yaml/ParserYaml.h"
#include "../Controlador/ControladorEvento.h"
#include "../../utils/Sockets/SocketCliente.h"
#include "../../utils/Log/Log.h"
#include "../../utils/Serializacion/Serializadora.h"
#include "../../utils/Temporizador/Temporizador.h"

class VistaFactory{

	private:
		struct stVistaJuegoElegido{
			
			// Datos de mi jugador
			ProxyModeloEntidad::stEntidad entidadJugador;						// Lo recibo desde el Servidor
			
			// Datos de otros jugadores que no son el mio
			std::list<ProxyModeloEntidad::stEntidad> listaOtrosJugadores;		// Lo recibo desde el Servidor
			std::list<ProxyModeloEntidad::stEntidad> listaEnemigosAutomaticos;	// Lo recibo desde el Servidor
			std::list<ProxyModeloEntidad::stEntidad> listaItems;				// Lo recibo desde el Servidor
			
			// Entidades del escenario que no son jugadores
			ParserYaml::stEscenario escenario;									// Lo recibo desde el Servidor
			std::list<int> listaIdEntidades;									// Lo recibo desde el Servidor
			
			// Otros atributos que se leen del yaml
			ParserYaml::stConfiguracion configuracion;
			ParserYaml::stPantalla pantalla;
			std::list<ParserYaml::stEntidad> listaEntidades;
		};
		VistaFactory::stVistaJuegoElegido juegoElegido;

		// Recepción de todos los datos necesarios para crear la Vista y el Controlador
		bool conectarSocket(SocketCliente* pSocket,bool singlePlayer);
		bool recibirArchivos(SocketCliente* pSocket);
		bool recibirListaDeArchivos(const char* directorioElegido,SocketCliente* pSocket);
		bool recibirEscenario(std::list<ParserYaml::stEscenario>& listaEscenarios,SocketCliente* pSocket);
		bool recibirEnemigosAutomaticos(SocketCliente* pSocket);
		bool recibirItems(SocketCliente* pSocket);
		bool recibirProtagonista(SocketCliente* pSocket,std::string nombreUsuario,std::string nombrePersonaje);
		bool recibirOtrosJugadores(SocketCliente* pSocket);
		void asignarEscenarioElegido(std::string nombreEscenario,std::list<ParserYaml::stEscenario>& listaEscenarios);
		bool esperarComienzoDeJuego(SocketCliente* pSocket,bool singlePlayer);

		// Creación de la Vista
		bool crearElementosVista(SDL_Surface* pPantallaSDL, VistaNivel& vistaNivel,SocketCliente* pSocket,SDL_Surface** pPantallaDestino, ProxyModeloEntidad** pProxyDestino);
		void crearJugadorConScroll(VistaNivel& vistaNivel,SDL_Surface* pantalla);
		void crearOtrosJugadores(VistaNivel& vistaNivel);
		void crearEnemigosAutomaticos(VistaNivel& vistaNivel);
		void crearItems(VistaNivel& vistaNivel);
		void crearEntidadesNoJugadores(VistaNivel& vistaNivel);		

		// Creación del Controlador
		bool crearElementosControlador(VistaNivel& vistaNivel,ControladorEvento* evento,SocketCliente* pSocket);
		void crearControladorScroll(ControladorEvento* evento,VistaNivel& vistaNivel);		
		void crearProxyControladorEvento(ControladorEvento* evento,SocketCliente* pSocket);
		void vincularScroll(VistaNivel& vistaNivel,ControladorEvento* evento);		
		std::string matriz;
	public:
		VistaFactory(void);
		~VistaFactory(void);

		bool crearNivel(VistaNivel& vistaNivel,ControladorEvento* evento,SocketCliente* pSocket,SDL_Surface** pPantallaDestino, ProxyModeloEntidad** pProxyDestino,std::string mote,std::string personaje,bool singlePlayer);
		void crearJugadorSinScroll(VistaNivel& vistaNivel,ProxyModeloEntidad::stEntidad& entidad);
		std::string getMatriz();
};
