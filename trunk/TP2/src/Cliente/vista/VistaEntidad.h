#pragma once

#include "VistaAnimacion.h"
#include "VistaAnimaciones.h"
#include "VistaScroll.h"
#include "../../utils/Observador/Identificable.h"
#include "../../utils/Proxy/ProxyModeloEntidad.h"	// Para usar el ProxyModeloEntidad::stEntidad

class VistaEntidad: public Identificable{

	private:
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
		double xEnPantalla;
		double yEnPantalla;
		vector<string> estados;		

	public:
		VistaEntidad(double x,double y,double alto,double ancho,double posicionReferenciaX,double posicionReferenciaY,double fps,double delay,std::list<std::list<std::string>> listaAnimaciones,bool esJugador,int altoNivel,int anchoNivel,int id);
		~VistaEntidad(void);

		void actualizar(ProxyModeloEntidad::stEntidad& entidad);
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
		void setXEnPantalla(double scrollX);
		void setYEnPantalla(double scrollY);
		void setEsNecesarioRefrescar(bool boolRefrescar);
		void setAnimacion(std::string estado);
		bool graficar();
		void setPantalla(SDL_Surface* screen);


};
