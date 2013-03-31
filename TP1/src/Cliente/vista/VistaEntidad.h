#pragma once

#include "./VistaAnimaciones.h"
#include "../../Servidor/modelo/ModeloEntidad.h"

class VistaEntidad{

	private:
		long id;
		bool esPersonaje;
		double x;
		double y;
		double alto;
		double ancho;
		double posicionReferenciaX;
		double posicionReferenciaY;
		double fps;
		double delay;

		static long contador; // Para generar ID's Automáticos

		VistaAnimaciones vistaAnimaciones;

	public:
		VistaEntidad(double x,double y,double alto,double ancho,double posicionReferenciaX,double posicionReferenciaY,double fps,double delay,bool esPersonaje);
		~VistaEntidad(void);

		int obtenerId(void);
		void actualizar(class Observable* s);
};

// TODO: Completar con geters y seters
// TODO: Completar el uso de la clase VistaAnimaciones