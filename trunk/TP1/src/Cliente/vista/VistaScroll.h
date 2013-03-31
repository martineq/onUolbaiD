#pragma once

#include "../../Servidor/modelo/ModeloScroll.h"
#include <winsock.h>  // Para usar InterlockedIncrement()

class VistaScroll{

	private:
		int id;
		double x;
		double y;
		double alto;
		double ancho;
		bool esNecesarioRefrescar;

		static long contador; // Para generar ID's Automáticos

	public:
		VistaScroll(double x,double y,double alto,double ancho);
		~VistaScroll(void);

		void actualizar(class Observable* s);

		// Getters
		int getId(void);
		double getX(void);
		double getY(void);
		double getAlto(void);
		double getAncho(void);
		bool getEsNecesarioRefrescar(void);

		// Setters
		void setEsNecesarioRefrescar(bool boolRefrescar);

};