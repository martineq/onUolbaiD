#pragma once

#include "../../Servidor/modelo/ModeloEntidad.h"

class VistaEntidad{

	private:
		int id;
		bool esJugador;
		double x;
		double y;
		double alto;
		double ancho;
		double posicionReferenciaX;
		double posicionReferenciaY;
		double fps;
		double delay;
		std::list<std::list<std::string>> listaAnimaciones;
		int codigoAnimacion;
		bool esNecesarioRefrescar;

		static long contador; // Para generar ID's Automáticos

	public:
		VistaEntidad(double x,double y,double alto,double ancho,double posicionReferenciaX,double posicionReferenciaY,double fps,double delay,std::list<std::list<std::string>> listaAnimaciones,bool esJugador);
		~VistaEntidad(void);

		void actualizar(class Observable* s);

		// Getters
		bool getEsJugador(void);
		int getId(void);
		double getX(void);
		double getY(void);
		double getAlto(void);
		double getAncho(void);
		double getPosRefX(void);
		double getPosRefY(void);
		double getFps(void);
		double getDelay(void);
		int getCodigoAnimacion(void);
		std::list<std::list<std::string>> getListaAnimaciones(void);
		bool getEsNecesarioRefrescar(void);

		// Setters
		void setEsNecesarioRefrescar(bool boolRefrescar);

};
