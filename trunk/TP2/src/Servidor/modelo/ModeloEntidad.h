#pragma once

#include <math.h>
#include <iostream>
#include "../../utils/Constantes/Constantes.h"
#include "../../utils/Observador/Observable.h"
#include "../../utils/Observador/Identificable.h"
#include "../../utils/Posicion/Posicion.h"
#include "../../utils/Hilos/Hilo.h"
#include "../../utils/Proxy/ProxyModeloEntidad.h"

typedef enum Direccion { NORTE, NORESTE, ESTE, SUDESTE, SUR, SUDOESTE, OESTE, NOROESTE };

class ModeloEntidad: public Identificable {
	private:
		class ModeloMovimiento : public Observable {
			private:
				ModeloEntidad* _modeloEntidad;
				Posicion _posicionDestino;
				int _deltaX;
				int _deltaY;
				int _desplazamientoX;
				int _desplazamientoY;
				int _error;
				int _desplazamientoErrorX;
				int _desplazamientoErrorY;
				DWORD _instanteUltimoCambioEstado;
				
				ModeloMovimiento(const ModeloMovimiento &modeloMovimiento);

				ModeloMovimiento& operator=(const ModeloMovimiento &modeloMovimiento);

			public:
				ModeloMovimiento(ModeloEntidad* modeloEntidad);

				virtual ~ModeloMovimiento();

				void actualizar(Posicion posicion);

				void cambiarEstado();
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
				
				Direccion obtenerDireccion(Posicion posicionOrigen, Posicion posicionDestino);

				VistaMovimiento(const VistaMovimiento &vistaMovimiento);

				VistaMovimiento& operator=(const VistaMovimiento &vistaMovimiento);

			public:
				VistaMovimiento(ModeloEntidad* modeloEntidad, int altoMapa, int anchoMapa, int fps);

				virtual ~VistaMovimiento();
				
				void actualizar(Observable* observable);

				void cambiarEstado();
		};

		int _id;
		std::string _nombreEntidad;
		bool _esJugador;
		int _alto;
		int _ancho;
		int _velocidad;
		Posicion _posicionActual;
		Posicion _posicionSiguiente;
		Posicion _pixelActual;
		Posicion _pixelSiguiente;
		Direccion _direccion;
		ModeloMovimiento* _modeloMovimiento;
		VistaMovimiento* _vistaMovimiento;
		bool _esUltimoMovimiento;
		int _altoMapa;
		int _anchoMapa;
		ProxyModeloEntidad* _pProxyEntidad;

		ModeloEntidad(const ModeloEntidad &modeloEntidad);

		ModeloEntidad& operator=(const ModeloEntidad &modeloEntidad);

	public:
		ModeloEntidad(int alto, int ancho, int velocidad, Posicion posicion, bool esJugador, int altoMapa, int anchoMapa, int fps, ProxyModeloEntidad* pProxyEntidad,int id,std::string nombreEntidad);

		virtual ~ModeloEntidad();

		void cambiarEstado();	// Este cambiarEstado() no corresponde mas al patrón Observer

		void notificarAlProxy(void);

		int id() const;

		std::string nombreEntidad() const;

		bool esJugador() const;

		int alto() const;

		int ancho() const;
		
		int velocidad() const;

		Posicion posicionActual() const;

		Posicion posicionSiguiente() const;

		Posicion pixelActual() const;

		Posicion pixelSiguiente() const;

		Direccion direccion() const;

		bool esUltimoMovimiento() const;

		void mover(Posicion posicion);

		bool operator==(const ModeloEntidad &modeloEntidad) const;
};

// TODO: Hay que agregar mutex para todos los atributos de ModeloEntidad ya que puede ser leido por varios hilos a la vez