#pragma once

#include <math.h>
#include <iostream>
#include <Windows.h>
#include <WinSock.h>

#include "../../utils/Constantes/Constantes.h"
#include "../../utils/Observador/Observable.h"
#include "../../utils/Observador/Observador.h"
#include "../../utils/Hilos/Mutex.h"
#include "../../utils/Proxy/ProxyModeloEntidad.h"
#include "../../utils/Posicion/Posicion.h"
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
				std::list<ModeloEntidad*>* _listaJugadores;
				Mutex* _mutexListaJugadores;
				std::list<ModeloEntidad*>* _listaEntidades;
				Mutex* _mutexListaEntidades;
				Posicion _posicionDestino;
				Posicion _posicionDestinoDesvio;
				int _deltaX;
				int _deltaY;
				int _desplazamientoX;
				int _desplazamientoY;
				int _error;
				int _desplazamientoErrorX;
				int _desplazamientoErrorY;
				DWORD _instanteUltimoCambioEstado;

				bool calcularDesvio(ModeloEntidad* modeloEntidad);

				ModeloEntidad* detectarColision(Posicion posicion);

				int obtenerAlto(int y, ModeloEntidad* modeloEntidad);

				int obtenerAncho(int x, ModeloEntidad* modeloEntidad);

				Direccion obtenerDireccion(Posicion posicionOrigen, Posicion posicionDestino);

				Posicion obtenerPosicionSiguiente();

				int obtenerX(ModeloEntidad* modeloEntidad);

				int obtenerY(ModeloEntidad* modeloEntidad);

				bool resolviendoDesvio() const;

				ModeloMovimiento(const ModeloMovimiento &modeloMovimiento);

				ModeloMovimiento& operator=(const ModeloMovimiento &modeloMovimiento);

			public:
				ModeloMovimiento(int altoNivel, int anchoNivel, ModeloEntidad* modeloEntidad);

				virtual ~ModeloMovimiento();

				void actualizar(Posicion posicion);

				void asignarListaEntidades(Mutex* mutexListaEntidades, std::list<ModeloEntidad*>* listaEntidades);

				void asignarListaJugadores(Mutex* mutexListaJugadores, std::list<ModeloEntidad*>* listaJugadores);

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

	protected:
		void accion(Accion accion);
		
		void direccion(Direccion direccion);

		void esUltimoMovimiento(bool esUltimoMovimiento);

		void posicionActual(Posicion posicionActual);

		void posicionSiguiente(Posicion posicionSiguiente);

		void pixelActual(Posicion pixelActual);

		void pixelSiguiente(Posicion pixelSiguiente);
		
	public:
		ModeloEntidad(int alto, int ancho, int velocidad, Posicion posicion, bool esJugador, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad, std::string mote);

		virtual ~ModeloEntidad();

		Accion accion();

		int alto();

		int ancho();
		
		Direccion direccion();

		bool esJugador();

		bool estaCongelado();

		bool esUltimoMovimiento();

		int id();

		std::string nombreEntidad();

		std::string nombreJugador();

		Posicion posicionActual();

		Posicion posicionSiguiente();

		ProxyModeloEntidad::stEntidad stEntidad();
		
		int velocidad();

		void estaCongelado(bool estaCongelado);

		void asignarListaJugadores(Mutex* mutexListaJugadores, std::list<ModeloEntidad*>* listaJugadores);

		void asignarListaEntidades(Mutex* mutexListaJugadores, std::list<ModeloEntidad*>* listaEntidades);

		void atacar();

		void defender();

		void cambiarEstado();

		void mover(Posicion posicion);

		bool ocupaPosicion(Posicion posicion);

		Posicion pixelActual();

		Posicion pixelSiguiente();

		void notificar();
	
		void setNombreJugador(std::string nombre);

		bool operator==(const ModeloEntidad &modeloEntidad) const;
};
