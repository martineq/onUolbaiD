#pragma once

#include "../../Servidor/modelo/ModeloEntidad.h"
#include "VistaAnimacion.h"
#include "VistaAnimaciones.h"
#include "../../utils/Observador/Observador.h"
#include "../../utils/Observador/Identificable.h"
#include "VistaScroll.h"

class VistaEntidad: public Observador, public Identificable{

	private:
		//int id;
		int _id;
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
		VistaAnimacion* animacionActual;
		VistaAnimaciones* animaciones;
		int codigoAnimacion;
		bool esNecesarioRefrescar;
		SDL_Rect area;
		bool entraEnPantalla;
		/*double xEnPantalla;
		double yEnPantalla;*/
			
		static long contador; // Para generar ID's Automáticos
		vector<string> estados;		

	public:
		VistaEntidad(double x,double y,double alto,double ancho,double posicionReferenciaX,double posicionReferenciaY,double fps,double delay,std::list<std::list<std::string>> listaAnimaciones,bool esJugador);		
		~VistaEntidad(void);

		void actualizar(class Observable* s);
		void verificarBordePantalla(VistaScroll* scroll);
		int id() const;

		// Getters
		bool getEsJugador(void);
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
		/*void setXEnPantalla(double scrollX);
		void setYEnPantalla(double scrollY);*/
		void setEsNecesarioRefrescar(bool boolRefrescar);
		void setAnimacion(std::string estado);
		bool graficar();
		void setPantalla(SDL_Surface* screen);

};
