#pragma once

#include "../../Servidor/modelo/ModeloScroll.h"
#include <winsock.h>  // Para usar InterlockedIncrement()

class VistaScroll{

	private:
		long id;
		double x;
		double y;
		double alto;
		double ancho;

		static long contador; // Para generar ID's Autom�ticos

	public:
		VistaScroll(double x,double y,double alto,double ancho);
		~VistaScroll(void);

		int obtenerId(void);
		void actualizar(class Observable* s);

};

// TODO: Completar con geters y seters