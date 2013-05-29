#pragma once

#include <math.h>
#include <iostream>
#include <map>

#include "../../utils/Constantes/Constantes.h"
#include "../../utils/Observador/Observable.h"
#include "../../utils/Observador/Observador.h"
#include "Posicion.h"
#include "ModeloEntidad.h"

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
