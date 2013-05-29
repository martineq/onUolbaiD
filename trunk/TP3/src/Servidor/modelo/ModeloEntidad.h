#pragma once

#include <math.h>
#include <Windows.h>
#include <WinSock.h>
#include <iostream>
#include <map>

#include "../../utils/Constantes/Constantes.h"
#include "../../utils/Hilos/Mutex.h"
#include "../../utils/Proxy/ProxyModeloEntidad.h"
#include "Posicion.h"

class ModeloEntidad {
	private:
		int _alto;
		int _altoNivel;
		int _ancho;
		int _anchoNivel;
		Direccion _direccion;
		int _id;
		Mutex _mutex;
		std::string _nombreEntidad;
		bool _notificar;
		Posicion _posicion;
		ProxyModeloEntidad* _proxyEntidad;
		int _velocidad;
		
		bool _esUltimoMovimiento;
		Posicion _pixelSiguiente;

		ModeloEntidad(const ModeloEntidad &modeloEntidad);

		ModeloEntidad& operator=(const ModeloEntidad &modeloEntidad);

	public:
		ModeloEntidad(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad);

		virtual ~ModeloEntidad();

		int alto();

		void alto(int alto);

		int ancho();
		
		void ancho(int ancho);

		Direccion direccion();

		void direccion(Direccion direccion);
		
		bool esUltimoMovimiento();

		void esUltimoMovimiento(bool esUltimoMovimiento);

		int id();

		void id(int id);

		std::string nombreEntidad();

		void nombreEntidad(std::string nombreEntidad);

		bool notificar();

		void notificar(bool notificar);

		Posicion posicion();

		void posicion(Posicion posicionActual);

		int velocidad();
		
		void velocidad(int velocidad);

		bool enviarEstado(ProxyModeloEntidad::stEntidad estado);

		bool ocupaPosicion(Posicion posicion);

		bool operator==(const ModeloEntidad &modeloEntidad) const;

		ProxyModeloEntidad::stEntidad stEntidad();

		Posicion pixel();

		void pixel(Posicion pixelSiguiente);
};
