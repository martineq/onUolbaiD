#pragma once

#include <math.h>
#include <iostream>
#include <Windows.h>
#include <WinSock.h>

#include "../../utils/Constantes/Constantes.h"
#include "../../utils/Observador/Observable.h"
#include "../../utils/Observador/Identificable.h"
#include "../../utils/Posicion/Posicion.h"

typedef enum Direccion { NORTE, NORESTE, ESTE, SUDESTE, SUR, SUDOESTE, OESTE, NOROESTE };

class ModeloEntidad : public Observable, public Identificable {
	private:
		static long _ultimoId;
		
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
				
				Direccion obtenerDireccion(Posicion posicionOrigen, Posicion posicionDestino);

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
				
				VistaMovimiento(const VistaMovimiento &vistaMovimiento);

				VistaMovimiento& operator=(const VistaMovimiento &vistaMovimiento);

			public:
				VistaMovimiento(ModeloEntidad* modeloEntidad, int altoMapa, int anchoMapa, int fps);

				virtual ~VistaMovimiento();
				
				void actualizar(Observable* observable);

				void cambiarEstado();
		};

		int _id;
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

		ModeloEntidad(const ModeloEntidad &modeloEntidad);

		ModeloEntidad& operator=(const ModeloEntidad &modeloEntidad);

	protected:
		void posicionActual(Posicion posicionActual);

		void posicionSiguiente(Posicion posicionSiguiente);

		void pixelActual(Posicion pixelActual);

		void pixelSiguiente(Posicion pixelSiguiente);

		void esUltimoMovimiento(bool esUltimoMovimiento);

		void direccion(Direccion direccion);

	public:
		ModeloEntidad(int alto, int ancho, int velocidad, Posicion posicion, int altoMapa, int anchoMapa, int fps);

		virtual ~ModeloEntidad();

		void cambiarEstado();

		int id() const;

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
