#pragma once

#include "./ModeloDrop.h"
#include "./ModeloNivel.h"
#include "./ModeloEntidad.h"
#include "./ModeloLoop.h"
#include "./ModeloItem.h"
#include "../../utils/Constantes/Constantes.h"
#include "../../utils/yaml/ParserYaml.h"
#include "../../utils/Sockets/SocketServidor.h"
#include "../../utils/Ticket/Ticket.h"
#include "../../utils/Serializacion/Serializadora.h"
#include "../../utils/LectorDirectorios/LectorDirectorios.h"
#include "../../utils/Serializacion/Serializadora.h"
#include "../../utils/Temporizador/Temporizador.h"

#include <sdl.h>
#include <SDL_ttf.h>
#include "../../utils/SDLgfx/SDL_gfxPrimitives.h"
#include "../../Cliente/vista/ImageLoader.h"

class ModeloFactory{

	private:
		struct stModeloJuegoElegido{
			// Atributos que se leen del yaml
			ParserYaml::stEscenario escenario;				// Se elige a partir de consola
			ParserYaml::stConfiguracion configuracion;
			ParserYaml::stPantalla pantalla;
			std::list<ParserYaml::stEntidad> listaEntidades;
			ModeloDrop::stDatosDrop datosDrop;

			// Atributos que se llenan mientras de crean entidades
			std::string nombreEscenario;
			std::list<int> listaIdEntidades;
		};

		// Atributos para uso del factory
		SocketServidor* pSocket;
		ModeloFactory::stModeloJuegoElegido juegoElegido;
		Mutex mutexJuegoElegido;

		// Métodos para ser usados por el factory mismo, el iniciar
		bool elegirEscenario(std::list<ParserYaml::stEscenario>& listaEscenarios);
		bool nuevoElegirEscenario (std::list<ParserYaml::stEscenario>& listaEscenarios);
		void crearEntidades(ModeloNivel& modeloNivel);
		void crearEnemigosAutomaticos(ModeloNivel& modeloNivel);
		void crearItems(ModeloNivel& modeloNivel);

		// Métodos usados por el HiloConfiguracion
		bool enviarEscenario(int id);
		bool enviarEnemigosAutomaticos(ModeloNivel* modeloNivel, int id);
		bool enviarItems(ModeloNivel* modeloNivel, int id);
		bool enviarProtagonista(ModeloNivel* modeloNivel, int& id);
		bool enviarOtrosJugadores(ModeloNivel* modeloNivel,int idMiJugador);
		void crearJugador(ModeloNivel* modeloNivel,ProxyModeloEntidad::stEntidad& stEntidad,std::string nombreJugador,std::string mote, int id);
		bool enviarArchivosDeConfiguracion(int idSocketCliente);
		bool enviarListaDeArchivos(std::vector<std::string> lista,int idSocketCliente);
		ModeloFactory::stModeloJuegoElegido getCopiaJuegoElegido(void);
		ProxyModeloEntidad::stEntidad elegirProtagonista(ModeloNivel* modeloNivel,std::string& nombreUsuario,std::string& nombrePersonaje,int& id);
		std::string obtenerPersonajeLibre(std::list<std::string> listaEntidadesUsadas,std::string personajePedido);

		// Otros
		Posicion generarPosicionAlAzar(ModeloNivel* modeloNivel,ModeloFactory::stModeloJuegoElegido& juegoElegido);
		ModeloItem* instanciarItem(int alto, int ancho, int velocidad, Posicion pos, int altoEscenario, int anchoEscenario, int fps, ProxyModeloEntidad* pProxyEntidad, int nuevoID, std::string nombreEntidad);
		void cargarDatosGolem(ModeloItem* pItem);
		void cargarDatosGolem(int& alto, int& ancho, int& fps, int& anchoEscenario, int& altoEscenario);
		void recolectarDatosItems();
		bool estaDatoItemEnLista(std::string nombreItem);

	public:
		ModeloFactory(void);
		~ModeloFactory(void);

		bool crearNivel(ModeloNivel& modeloNivel, ModeloLoop& modeloLoop, SocketServidor* pSocket, bool primeraVez);
		bool rutinaAgregarNuevoCliente(void* modeloNivel,SocketServidor* pSocket,int id,bool singlePlayer);
};
