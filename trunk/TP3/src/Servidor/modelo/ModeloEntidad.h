#pragma once

#include <math.h>
#include <Windows.h>
#include <WinSock.h>
#include <iostream>
#include <map>

#include "../../utils/Constantes/Constantes.h"
#include "../../utils/Observador/Observable.h"
#include "../../utils/Observador/Observador.h"
#include "../../utils/Hilos/Mutex.h"
#include "../../utils/Proxy/ProxyModeloEntidad.h"
#include "Posicion.h"
#include "Tile.h"
#include "EstadoNivel.h"

typedef enum Direccion { NOROESTE, NORTE, NORESTE, ESTE, SUDESTE, SUR, SUDOESTE, OESTE };
typedef enum Accion { CAMINANDO, ATACANDO, DEFENDIENDO, QUIETO };

class ModeloEntidad {
	private:
		class ModeloMovimiento : public Observable {
			private:
				int _altoNivel;
				int _anchoNivel;
				ModeloEntidad* _modeloEntidad;
				std::list<ModeloEntidad*>* _entidadesMoviles;
				Mutex* _mutexEntidadesMoviles;
				std::multimap<std::pair<int, int>, ModeloEntidad*>* _entidades;
				Mutex* _mutexEntidades;
				std::list<Posicion> _posiciones;
				DWORD _instanteUltimoCambioEstado;

				bool agregarTile(char* mapaTilesCerrados, std::list<Tile>* tilesAbiertos, Posicion posicion, Posicion posicionDestino, Tile* padre, int distancia);

				Posicion calcularPosicionDestino(Posicion posicionDestino);

				ModeloEntidad* detectarColision(Posicion posicion);

				int obtenerAlto(int y, ModeloEntidad* modeloEntidad);

				int obtenerAncho(int x, ModeloEntidad* modeloEntidad);

				Direccion obtenerDireccion(Posicion posicionOrigen, Posicion posicionDestino);

				Posicion obtenerPosicionSiguiente();

				int obtenerX(ModeloEntidad* modeloEntidad);

				int obtenerY(ModeloEntidad* modeloEntidad);

				ModeloMovimiento(const ModeloMovimiento &modeloMovimiento);

				ModeloMovimiento& operator=(const ModeloMovimiento &modeloMovimiento);

			public:
				ModeloMovimiento(int altoNivel, int anchoNivel, ModeloEntidad* modeloEntidad);

				virtual ~ModeloMovimiento();

				void actualizar(Posicion posicion);

				void asignarEntidades(Mutex* mutexEntidades, std::multimap<std::pair<int, int>, ModeloEntidad*>* entidades);

				void asignarEntidadesMoviles(Mutex* mutexEntidadesMoviles, std::list<ModeloEntidad*>* entidadesMoviles);

				void cambiarEstado();

				void detener();
		};

		class VistaMovimiento : public Observador {
			private:
				ModeloEntidad* _modeloEntidad;
				Posicion _posicionOrigen;
				Posicion _posicionDestino;
				int _altoMapa;
				int _anchoMapa;
				int _cantidadCuadros;
				int _desplazamiento;
				DWORD _espera;
				int _cuadroActual;
				std::list<Posicion> _posiciones;
				DWORD _instanteUltimoCambioEstado;
				
				VistaMovimiento(const VistaMovimiento &vistaMovimiento);

				VistaMovimiento& operator=(const VistaMovimiento &vistaMovimiento);

			public:
				VistaMovimiento(ModeloEntidad* modeloEntidad, int altoMapa, int anchoMapa, int fps);

				virtual ~VistaMovimiento();
				
				void actualizar(Observable* observable);

				void cambiarEstado();

				bool terminado() const;
		};

		Accion _accion;
		int _alto;
		int _altoNivel;
		int _ancho;
		int _anchoNivel;
		Direccion _direccion;
		bool _esJugador;
		bool _estaCongelado;
		EstadoNivel* _estadoNivel;
		int _id;
		ModeloMovimiento* _modeloMovimiento;
		Mutex _mutex;
		std::string _nombreEntidad;
		std::string _nombreJugador;
		Posicion _posicionActual;
		Posicion _posicionSiguiente;
		ProxyModeloEntidad* _proxyEntidad;
		int _velocidad;
		
		bool _esUltimoMovimiento;
		Posicion _pixelActual;
		Posicion _pixelSiguiente;
		VistaMovimiento* _vistaMovimiento;

		ModeloEntidad(const ModeloEntidad &modeloEntidad);

		ModeloEntidad& operator=(const ModeloEntidad &modeloEntidad);
		
	public:
		ModeloEntidad(int alto, int ancho, int velocidad, Posicion posicion, bool esJugador, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad, std::string nombreJugador);

		virtual ~ModeloEntidad();

		Accion accion();

		void accion(Accion accion);

		int alto();

		void alto(int alto);

		int ancho();
		
		void ancho(int ancho);

		Direccion direccion();

		void direccion(Direccion direccion);

		bool esJugador();

		void esJugador(bool esJugador);

		bool estaCongelado();

		void estaCongelado(bool estaCongelado);

		bool esUltimoMovimiento();

		void esUltimoMovimiento(bool esUltimoMovimiento);

		int id();

		void id(int id);

		std::string nombreEntidad();

		void nombreEntidad(std::string nombreEntidad);

		std::string nombreJugador();

		void nombreJugador(std::string nombreJugador);

		Posicion posicionActual();

		void posicionActual(Posicion posicionActual);

		Posicion posicionSiguiente();

		void posicionSiguiente(Posicion posicionSiguiente);

		int velocidad();
		
		void velocidad(int velocidad);

		void asignarEntidadesMoviles(Mutex* mutexEntidadesMoviles, std::list<ModeloEntidad*>* entidadesMoviles);

		void asignarEntidades(Mutex* mutexEntidades, std::multimap<std::pair<int, int>, ModeloEntidad*>* entidades);

		void cambiarEstado();

		bool chequearConexion();

		void detener();

		void enviarMensaje(ModeloEntidad* remitente, std::string mensaje);

		void mover(Posicion posicion);

		void notificar();

		bool ocupaPosicion(Posicion posicion);

		bool operator==(const ModeloEntidad &modeloEntidad) const;

		ProxyModeloEntidad::stEntidad stEntidad();

		Posicion pixelActual();

		void pixelActual(Posicion pixelActual);

		Posicion pixelSiguiente();

		void pixelSiguiente(Posicion pixelSiguiente);

		void cargarMatriz(ProxyModeloEntidad::stEntidad& entidad);
};
