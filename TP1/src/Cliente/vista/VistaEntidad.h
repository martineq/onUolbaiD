#pragma once

#include "../../Servidor/modelo/ModeloEntidad.h"

class VistaEntidad{

	private:
		long id;
		bool esJugador;
		double x;
		double y;
		double alto;
		double ancho;
		double posicionReferenciaX;
		double posicionReferenciaY;
		double fps;
		double delay;
		std::list<std::string> listaAnimaciones;

		static long contador; // Para generar ID's Automáticos

	public:
		VistaEntidad(double x,double y,double alto,double ancho,double posicionReferenciaX,double posicionReferenciaY,double fps,double delay,std::list<std::string> listaAnimaciones,bool esJugador);
		~VistaEntidad(void);

		int obtenerId(void);
		void actualizar(class Observable* s);
};

// TODO: Completar con geters y seters