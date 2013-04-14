#pragma once

#include "../../Servidor/modelo/ModeloScroll.h"
#include "../../utils/Observador/Observador.h"
#include "../../utils/Observador/Identificable.h"
#include <winsock.h>  // Para usar InterlockedIncrement()

class VistaScroll: public Observador, public Identificable{

	private:
		//int id;
		int _id;
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
		int id() const;

		// Getters
		//int getId(void);
		double getX(void);
		double getY(void);
		double getAlto(void);
		double getAncho(void);
		bool getEsNecesarioRefrescar(void);

		// Setters
		void setEsNecesarioRefrescar(bool boolRefrescar);

};